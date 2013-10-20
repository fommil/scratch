package com.github.fommil.trafigura

abstract class ChessSolverSpecs extends Specs {

  val solver: ChessSolver

  "3x3, 2 kings, 1 rook" should {
    "produce the simple example output" in {
      val board = Board(3, 3)
      val pieces = King() :: King() :: Rook() :: Nil

      solver.solve(board, pieces) must containTheSameElementsAs {
        GameState(board, Map(
          (0, 0) -> King(),
          (1, 2) -> Rook(),
          (2, 0) -> King()
        )) :: GameState(board, Map(
          (0, 2) -> King(),
          (1, 0) -> Rook(),
          (2, 2) -> King()
        )) :: GameState(board, Map(
          (0, 0) -> King(),
          (2, 1) -> Rook(),
          (0, 2) -> King()
        )) :: GameState(board, Map(
          (2, 0) -> King(),
          (0, 1) -> Rook(),
          (2, 2) -> King()
        )) :: Nil
      }
    }
  }

  "4x4, 2 rooks, 4 horseys" should {
    "produce the correct example output size" in {
      val board = Board(4, 4)
      val pieces = Rook() :: Rook() :: Horsey() :: Horsey() :: Horsey() :: Horsey() :: Nil

      solver.solve(board, pieces).size === 8
    }
  }

}
