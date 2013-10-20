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
  * 2. All entries in the search space may be checked simultaneously as this is an
  * [[http://en.wikipedia.org/wiki/Embarrassingly_parallel embarrassingly parallel problem]].
  * We use Akka to send the validity checking to an actor system,
  * which may live on a distributed computing cluster. So long as the network
  * time is lower than the computational cost, there will be an advantage.
  *
  * Note that this Akka implementation would need to be significantly hardened
  * for a network distributed solution, and also for large search spaces, as
  * it currently has no support for lost messages and doesn't care about
  * the memory build-up in queues.
  *
  * @author Sam Halliday
  */
class AkkaSolver extends ChessSolver {

  private val system = ActorSystem("ChessSolver")
  implicit private val timeout = Timeout(1, DAYS)

  def solve(board: Board, pieces: List[Piece]) = {
    val actor = system.actorOf(Props[ChessSearchActor])
    val solutions = (actor ?(board, pieces)).mapTo[List[GameState]]
    Await.result(solutions, Duration.Inf)
  }
}


case class Solution(state: GameState)

case class Invalid(state: GameState)

class ChessSearchActor extends Actor with ActorLogging {

  var solutions = Set[GameState]()
  var created = 0
  var received = 0
  var caller: ActorRef = _

  def receive = {
    case (board: Board, pieces: List[Piece]) =>
      caller = sender
      caller ! List()

    case Solution(state) => ???

    case Invalid(state) => ???
  }
}

class ChessValidatorActor extends Actor with ActorLogging {
  def receive = ???
}
