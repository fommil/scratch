package com.github.fommil.trafigura

import scala.collection.GenIterable
import scala.Predef._
import com.google.common.base.Stopwatch

/** Uses brute-force search demonstrating algorithmic simplicity.
  *
  * @author Sam Halliday
  */
object SimpleSolverApp extends SimpleSolver with App {
  val board = Board(4, 4)
  val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil

  val watch = Stopwatch.createStarted()
  val solutions = solve(board, pieces)
  println(solutions.mkString("\n\n"))
  println(s"calculating the ${solutions.size} solutions took ${watch.stop()} for $board $pieces")
}

class SimpleSolver extends BruteForceArrangements {
  def solve(board: Board, pieces: List[Piece]): List[GameState] = {
    arrangements(GameState(board), pieces).toList.distinct
  }
}

trait BruteForceArrangements {
  protected def arrangements(state: GameState, pieces: List[Piece]): GenIterable[GameState] = pieces match {
    case Nil => state :: Nil
    case piece :: tail =>
      for {
        p <- state.available.par
        // 6x6 RRNNNN serial took 2.265 min
        // 6x6 RRNNNN parallel took 1.411 min
        if !state.canBeTakenBy(p, piece)
        s = state.withPiece(p, piece)
        n <- arrangements(s, tail)
      } yield n
  }
}
