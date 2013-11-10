package com.github.fommil.chess

import akka.actor._
import akka.pattern.ask
import akka.util.Timeout
import java.util.concurrent.TimeUnit.DAYS
import scala.concurrent.Await
import scala.concurrent.duration.Duration
import akka.routing.FromConfig
import com.google.common.base.Stopwatch
import com.typesafe.config.Config
import ActorSystem.Settings
import akka.dispatch.{PriorityGenerator, UnboundedPriorityMailbox}

/** This solver uses Akka to allow distribution and parallel processing.
  *
  * Note that this implementation would need to be significantly hardened
  * for a production solution: it currently has no support for lost messages.
  * Distribution would be faster if we didn't have to aggregate `Invalid` messages.
  *
  * Thoughts:
  *
  * 1. A possible solution to the `Invalid` network problem is to batch.
  *
  * 2. A possible solution to the lost messages problem would be to represent
  * the search space as a BitSet: even a Trie requires too much space.
  *
  * @author Sam Halliday
  */
object AkkaSolverApp extends App {
  //  val board = Board(3, 3)
  //  val pieces = King() :: King() :: Rook() :: Nil
//      val board = Board(4, 4)
//      val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil
//      val board = Board(6, 6)
//      val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil
  val board = Board(6, 9)
  val pieces = King() :: King() :: Queen() :: Bishop() :: Rook() :: Horsey() :: Nil

  private val system = ActorSystem("ChessSolver")
  system.actorOf(
    Props[ChessSearch].withRouter(FromConfig()).withMailbox("prio-mailbox"),
    "chess"
  )
  val solver = new AkkaSolver(system)

  val watch = Stopwatch.createStarted()
  val solutions = solver.solve(board, pieces)
  println(s"calculating the ${solutions} solutions took ${watch.stop()} for $board $pieces")

  system.shutdown()
}

trait OrderedPieces {
  implicit protected val OrderedPieces = new Ordering[Piece] {
    def compare(x: Piece, y: Piece) = ordinal(x) - ordinal(y)
  }

  private def ordinal(piece: Piece) = piece match {
    case Queen() => 0
    case Rook() => 1
    case Bishop() => 2
    case Horsey() => 3
    case King() => 4
  }
}


class AkkaSolver(system: ActorSystem) extends ChessSolver with OrderedPieces {

  implicit private val timeout = Timeout(1, DAYS)

  def solve(board: Board, pieces: List[Piece]) = {
    val actor = system.actorOf(Props[Aggregator])
    val ordered = pieces.sorted
    val start = init(board, ordered.head)
    val problem = Problem(start, ordered.tail)
    val calc = (actor ? problem).mapTo[Int]
    Await.result(calc, Duration.Inf)
  }

  def init(board: Board, piece: Piece): List[PreCompMoves] = board.positions.map { p =>
    PreCompMoves(board).withMove(p, piece)
  }.toList

}

case class Problem(start: List[PreCompMoves], pieces: List[Piece])

case class Solution(state: GameState)

case class Invalid(state: GameState)

case class Created(count: Int)

class Aggregator extends Actor with ActorLogging {

  val searchers = context.system.actorSelection("/user/chess")

  var solutions = 0
  var outstanding = 0
  var total = 0
  var lastLogged = 0
  var caller: ActorRef = _

  def receive = {
    case Problem(start, pieces) =>
      caller = sender
      start foreach { s =>
        outstanding += 1
        total += 1
        searchers ! Search(self, s, pieces)
      }

    case Created(count) =>
      // parent is already counted
      outstanding += (count - 1)
      total += count

    case Solution(state) =>
      solutions += 1
      outstanding -= 1
      if (outstanding == 0 || (solutions > lastLogged && solutions % 10000 == 0)) {
        lastLogged = solutions
        log.info(s"$outstanding outstanding of $total with $solutions solutions gathered")
      }
      checkComplete()

    case Invalid(state) =>
      outstanding -= 1
      checkComplete()
  }

  private def checkComplete() {
    if (outstanding == 0)
      caller ! solutions
  }
}

case class Search(agg: ActorRef, game: PreCompMoves, pieces: List[Piece])

class ChessSearch extends Actor with ActorLogging {

  val searchers = context.system.actorSelection("/user/chess")

  def receive = {
    case Search(agg, cache, Nil) =>
      agg ! Solution(cache.state)

    case Search(agg, cache, piece :: tail) =>
      val next = for {
        p <- cache.available
        if !piece.canTakeAny(p, cache.state.pieces.keys)
        if cache.state.first(piece).map { f => f > p }.getOrElse(true)
      } yield cache.withMove(p, piece)

      if (next.isEmpty)
        agg ! Invalid(cache.state)
      else {
        agg ! Created(next.size)
        next foreach { n =>
          if (tail == Nil)
            agg ! Solution(n.state)
          else
            searchers ! Search(agg, n, tail)
        }
      }
  }
}

class DeepSearchMailbox(settings: Settings, config: Config)
  extends UnboundedPriorityMailbox(
    PriorityGenerator {
      case Search(_, _, pieces) => pieces.size
      case otherwise => 0
    }
  )