package com.github.fommil.trafigura

import scala.collection.GenIterable
import scala.Predef._
import com.google.common.base.Stopwatch

/** Uses brute-force search demonstrating algorithmic simplicity.
  *
  * @author Sam Halliday
  */
object SimpleSolverApp extends SimpleSolver with App {
  val board = Board(6, 6)
  val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil

  val watch = Stopwatch.createStarted()
  val solutions = solve(board, pieces)
  println(solutions.mkString("\n\n"))
  println(s"calculating the ${solutions.size} solutions took ${watch.stop()} for $board $pieces")
}

class SimpleSolver extends ChessSolver with BruteForceArrangements {
  def solve(board: Board, pieces: List[Piece]): List[GameState] = {
    arrangements(GameState(board), pieces).toList.distinct
  }
}

trait BruteForceArrangements extends PrefilteredPositions {
  protected def arrangements(state: GameState, pieces: List[Piece]): GenIterable[GameState] = pieces match {
    case Nil => state :: Nil
    case piece :: tail =>
      for {
        p <- available(state)
        if !piece.canTakeAny(p, state.pieces.keys)
        s = state.withPiece(p, piece)
        n <- arrangements(s, tail)
      } yield n
  }
}

trait PrefilteredPositions {
  protected def available(state: GameState): Seq[Position] = for {
    x <- 0 until state.board.width
    y <- 0 until state.board.height
    p = (x, y)
    if !state.pieces.contains(p)
    if !canBeTaken(state, p)
  } yield p

  private def canBeTaken(state: GameState, to: Position) = {
    state.pieces.map {
      case (from, piece) => piece.canTake(from, to)
    } find (identity)
  }.isDefined

}