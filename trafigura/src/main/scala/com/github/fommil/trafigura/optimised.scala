package com.github.fommil.trafigura

/** This solver addressing bottlenecks discovered during profiling of SimpleSolver
  * (which clearly showed that the CPU spent most of its time in `Piece.moves`).
  *
  * 1. Organising the placement of pieces to minimise the search space.
  *
  * 2. By noting that the board displays symmetry in the horizontal and vertical,
  *    the search space is reduced by an order of 2^2^=4 (2^3^=8 for a square
  *    board, which also displays rotational symmetry).
  *    The code is increased in complexity in two parts:
  *    first the search space must be modified in an unintuitive manner,
  *    second a post-processing stage must be applied to recover the symmetries.
  *
  * 3. All entries in the search space may be checked simultaneously as this is an
  *    [[http://en.wikipedia.org/wiki/Embarrassingly_parallel embarrassingly parallel problem]].
  *    We use Akka to send the validity checking to an actor system,
  *    which may live on a distributed computing cluster. So long as the network
  *    time is lower than the computational cost, there will be an advantage.
  *
  * @author Sam Halliday
  */
class AkkaSolver extends ChessSolver {

  def solve(board: Board, pieces: List[Piece]) = ???

}