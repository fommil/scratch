package com.github.fommil.chess

import akka.actor._
import akka.pattern.ask
import akka.util.Timeout
import java.util.concurrent.TimeUnit.DAYS
import scala.concurrent.Await
import scala.concurrent.duration.Duration
import akka.routing.FromConfig
import com.google.common.base.Stopwatch

/** This solver addressing bottlenecks discovered by profiling SimpleSolver.
  *
  * In comparison: SimpleSolver solves 6x6 RRNNNN in 1 minute (seq) and
  * 33 seconds (par). AkkaSolver solves the same problem in 13 seconds
  * on the same machine and (most importantly) can be distributed
  * by following the [[http://doc.akka.io/docs/akka/snapshot/java/cluster-usage.html cluster tutorial]].
  *
  * The board displays symmetry in the horizontal and vertical,
  * the search space is reduced by an order of 2^2^=4 (2^3^=8 for a square
  * board, which also displays rotational symmetry).
  * We also reorder the placement of pieces to minimise the search space: these
  * optimisations are implemented in ChessOptimisations.
  *
  * Note that this implementation would need to be significantly hardened
  * for a production solution: it currently has no support for lost messages
  * and doesn't care about the memory build-up in queues. Also, distribution
  * would be faster if we didn't have to send `Invalid` messages back to
  * the aggregator: but without knowing the size of the search space in
  * advance we are scuppered.
  *
  * Thoughts:
  *
  * 1. A possible solution to the `Invalid` network problem is to batch.
  *
  * 2. A possible solution to the lost messages problem would be to represent
  * the search space as a BitSet, and every time a `Created` is produced,
  * the `BitSet` for all the excluded states is included in the message.
  * A scheduler could then check - when idle - outstanding states and then
  * send a message to recalculate them: the worst that can happen is
  * duplicated work.
  *
  * 3. There doesn't seem to be an abvious solution to the memory limit problem
  * in this approach without introducing a system-wide pipe that limits the
  * number of `Search` instances in existence and prioritising the most
  * recent `Created` messages... i.e. depth first.
  *
  * @author Sam Halliday
  */
object AkkaSolverApp extends App {

  val board = Board(6, 6)
  val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil


  private val system = ActorSystem("ChessSolver")
  system.actorOf(
    Props[ChessSearch].withRouter(FromConfig()),
    "chess"
  )
  val solver = new AkkaSolver(system) with ChessOptimisations

  val watch = Stopwatch.createStarted()
  val solutions = solver.solve(board, pieces)
  //  println(solutions.mkString("\n\n"))
  println(s"calculating the ${solutions.size} solutions took ${watch.stop()} for $board $pieces")

  system.shutdown()
}

abstract class AkkaSolver(system: ActorSystem) extends ChessSolver {
  this: ChessOptimisations =>

  implicit private val timeout = Timeout(1, DAYS)

  def solve(board: Board, pieces: List[Piece]) = {
    val actor = system.actorOf(Props[Aggregator])
    val ordered = order(pieces)
    val start = init(board, ordered.head)
    val problem = Problem(start, ordered.tail)
    val calc = (actor ? problem).mapTo[List[GameState]]
    val solutions = Await.result(calc, Duration.Inf)
    symm(solutions)
  }
}

case class Problem(start: List[CachedGameState], pieces: List[Piece])

case class Solution(state: GameState)

case class Invalid(state: GameState)

case class Created(count: Int)

class Aggregator extends Actor with ActorLogging {

  val searchers = context.actorSelection("/user/chess")

  var solutions = Set[GameState]()
  var outstanding = 0
  var total = 0
  var lastLogged = 0
  var caller: ActorRef = _

  def receive = {
    case Problem(start, pieces) =>
      caller = sender

      start foreach {
        s =>
          outstanding += 1
          total += 1
          searchers ! Search(self, s, pieces)
      }

    case Created(count) =>
      // parent is already counted
      outstanding += (count - 1)
      total += count

    case Solution(state) =>
      solutions = solutions + state
      outstanding -= 1
      if (solutions.size > lastLogged && solutions.size % 1000 == 0) {
        lastLogged = solutions.size
        log.info(s"$outstanding outstanding of $total with ${solutions.size} solutions gathered")
      }
      checkComplete()

    case Invalid(state) =>
      outstanding -= 1
      checkComplete()
  }

  private def checkComplete() {
    if (outstanding == 0)
      caller ! solutions.toList
  }
}

case class Search(agg: ActorRef, game: CachedGameState, pieces: List[Piece])

class ChessSearch extends Actor with ActorLogging {

  val searchers = context.actorSelection("/user/chess")

  def receive = {
    case Search(agg, cache, Nil) =>
      agg ! Solution(cache.state)

    case Search(agg, cache, piece :: tail) =>
      val next = for {
        p <- cache.available
        if !piece.canTakeAny(p, cache.state.pieces.keys)
      } yield cache.withPiece(p, piece)

      if (next.isEmpty)
        agg ! Invalid(cache.state)
      else {
        agg ! Created(next.size)
        next foreach {
          n =>
            if (tail == Nil)
              agg ! Solution(n.state)
            else
              searchers ! Search(agg, n, tail)
        }
      }
  }
}

trait ChessOptimisations {
  def order(pieces: List[Piece]) = pieces.sortBy {
    case Queen() => 0
    case Rook() | Bishop() => 1
    case Horsey() => 2
    case King() => 3
  }

  def init(board: Board, piece: Piece): List[CachedGameState] =
    board.positions.filter { p =>
      p._1 < (board.width + 1) / 2 && p._2 < (board.height + 1) / 2 &&
        (board.width != board.height || p._1 <= p._2)
    }.map { p =>
      CachedGameState(board).withPiece(p, piece)
    }.toList

  def symm(states: List[GameState]): List[GameState] = {
    for {
      s <- states
      h = flipH(s)
      xy <- s :: h :: flipV(s) :: flipV(h) :: Nil
      r <- xy :: flipD(xy)
    } yield r
  }.distinct

  private def flipH(state: GameState) = {
    val flipped = state.pieces.map {
      case ((x, y), piece) => ((state.board.width - x - 1, y), piece)
    }
    state.copy(pieces = flipped)
  }

  private def flipV(state: GameState) = {
    val flipped = state.pieces.map {
      case ((x, y), piece) => ((x, state.board.height - y - 1), piece)
    }
    state.copy(pieces = flipped)
  }

  private def flipD(state: GameState): List[GameState] =
    if (state.board.width != state.board.height)
      Nil
    else {
      val flipped = state.pieces.map {
        case ((x, y), piece) => ((y, x), piece)
      }
      state.copy(pieces = flipped) :: Nil
    }

}

trait NoChessOptimisations extends ChessOptimisations {
  override def order(pieces: List[Piece]) = pieces

  override def init(board: Board, piece: Piece): List[CachedGameState] = board.positions.map { p =>
    CachedGameState(board).withPiece(p, piece)
  }.toList

  override def symm(states: List[GameState]): List[GameState] = states
}