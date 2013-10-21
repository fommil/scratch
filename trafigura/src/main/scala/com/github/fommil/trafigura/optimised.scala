package com.github.fommil.trafigura

import akka.actor._
import akka.pattern.ask
import akka.util.Timeout
import java.util.concurrent.TimeUnit.DAYS
import scala.concurrent.Await
import scala.concurrent.duration.Duration

/** This solver addressing bottlenecks discovered by profiling SimpleSolver.
  *
  * 1. By noting that the board displays symmetry in the horizontal and vertical,
  * the search space is reduced by an order of 2^2^=4 (2^3^=8 for a square
  * board, which also displays rotational symmetry).
  * The code is increased in complexity in two parts:
  * first the search space must be modified in an unintuitive manner,
  * second a post-processing stage must be applied to recover the symmetries.
  *
  * 2. We hit the CPU bounds of a single machine in SimpleSolver, but this problem
  * is appropriate for distributed computing. We use Akka, which refactors
  * concurrency, parallel strategies and distribution to runtime
  * configuration.
  *
  * Note that this implementation would need to be significantly hardened
  * for a production solution: it currently has no support for lost messages
  * and doesn't care about the memory build-up in queues.
  *
  * @author Sam Halliday
  */
class AkkaSolver extends ChessSolver {

  private val system = ActorSystem("ChessSolver")
  implicit private val timeout = Timeout(1, DAYS)

  def solve(board: Board, pieces: List[Piece]) = {
    val actor = system.actorOf(Props[ChessSearch])
    val solutions = (actor ?(board, pieces)).mapTo[List[GameState]]
    Await.result(solutions, Duration.Inf)
  }
}


case class Solution(state: GameState)

case class Invalid(state: GameState)

// these must arrive first or we can exit early
case class Created(count: Int)

class Aggregator(searchers: ActorRef) extends Actor with ActorLogging with ChessOptimisations {

  var solutions = Set[GameState]()
  var outstanding = 0
  var caller: ActorRef = _

  def receive = {
    case (board: Board, pieces: List[Piece]) =>
      require(!pieces.isEmpty)
      caller = sender

      val ordered = order(pieces)
      init(board, ordered.head) foreach {s =>
        outstanding += 1
        searchers ! Search(self, s, ordered.tail)
      }

    case Created(count) =>
      // parent is already counted
      outstanding += (count - 1)

    case Solution(state) =>
      solutions = solutions + state
      outstanding -= 1
      checkComplete()

    case Invalid(state) =>
      outstanding -= 1
      checkComplete()
  }

  private def checkComplete() {
    if (outstanding == 0)
      caller ! symm(solutions.toList)
  }
}

case class Search(agg: ActorRef, game: CachedGameState, pieces: List[Piece])

class ChessSearch(searchers: ActorRef) extends Actor with ActorLogging {

  def receive = {
    case Search(agg, cache, Nil) =>
      agg ! Solution(cache.state)

    case Search(agg, cache, piece :: tail) =>
      val next = for {
        p <- cache.available
        if !piece.canTakeAny(p, cache.state.pieces.keys)
      } yield CachedGameState(cache, p, piece)

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

trait ChessOptimisations {
  // starting with the highest coverage piece reduces the search space
  def order(pieces: List[Piece]) = pieces.sortBy {
    case Queen() => 0
    case Rook() | Bishop() => 1
    case Horsey() => 2
    case King() => 3
  }

  def init(board: Board, piece: Piece): List[CachedGameState] = ???

  def symm(states: List[GameState]): List[GameState] = ???
}