package com.github.fommil.trafigura

/** This solver employs two optimisations:
  *
  * 1. By noting that the board displays symmetry in the horizontal and vertical,
  *    the search space is reduced by an order of 2^2^=4 (2^3^=8 for a square
  *    board, which also displays rotational symmetry).
  *    The code is increased in complexity in two parts:
  *    first the search space must be modified in an unintuitive manner,
  *    second a post-processing stage must be applied to recover the symmetries.
  *
  * 2. All entries in the search space may be checked simultaneously as this is an
  *    [[http://en.wikipedia.org/wiki/Embarrassingly_parallel embarrassingly parallel problem]].
  *    Scala has no general mechanism for parallel mappings to [[scala.collection.Iterable]],
  *    without retaining the entire data structure (which would result in an
  *    explosion of memory usage), so we use Akka to perform pull-based
  *    generation of trials, and distribute the checking to an actor system
  *    that may live on a distributed computing cluster.
  *
  * @author Sam Halliday
  */
class OptimisedSolver extends ChessSolver {

}