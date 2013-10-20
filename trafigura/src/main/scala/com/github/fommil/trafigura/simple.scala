package com.github.fommil.trafigura

import scala.collection.GenIterable

/** Uses brute-force search demonstrating algorithmic simplicity.
  * The search space is explored in parallel.
  *
  * @author Sam Halliday
  */
object SimpleSolverApp extends App {
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
        if !piece.canTake(p, state)
        s = state.withPiece(p, piece)
        n <- arrangements(s, tail)
      } yield n
  }
}
