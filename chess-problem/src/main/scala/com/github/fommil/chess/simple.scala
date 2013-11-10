package com.github.fommil.chess

import com.google.common.base.Stopwatch

/** Uses selective search, with no memory of solutions, demonstrating algorithmic simplicity.
  *
  * Duplicates are excluded from search by not allowing any piece to overtake another of the same.
  */
object SimpleSolverApp extends SimpleSolver with App {
  //  val board = Board(3, 3)
  //  val pieces = King() :: King() :: Rook() :: Nil
  //  val board = Board(4, 4)
  //  val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil
  //  val board = Board(6, 6)
  //  val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil
  val board = Board(6, 9)
  val pieces = King() :: King() :: Queen() :: Bishop() :: Rook() :: Horsey() :: Nil

  val watch = Stopwatch.createStarted()
  val solutions = solve(board, pieces)
  println(s"calculating the ${solutions} solutions took ${watch.stop()} for $board $pieces")
}

class SimpleSolver extends ChessSolver {
  def solve(board: Board, pieces: List[Piece]) = {
    require(pieces.size > 0)
    count(PreCompMoves(board), pieces)
  }

  private def count(cache: PreCompMoves, pieces: List[Piece]): Int = pieces match {
    case Nil => 1
    case piece :: tail => {
      for {
        p <- cache.available
        if !piece.canTakeAny(p, cache.state.pieces.keys)
        if cache.state.first(piece).map { f => f > p }.getOrElse(true)
        c = count(cache.withMove(p, piece), tail)
      } yield c
    }.fold(0) { _ + _ }
  }
}
