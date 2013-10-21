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
    arrangements(board, pieces).toList.distinct
  }
}


// avoids recomputing available spaces for derived states
case class CachedGameState(state: GameState, available: List[Position])

object CachedGameState {
  def apply(cached: CachedGameState, position: Position, piece: Piece): CachedGameState = {
    val gone = Set(position) ++ cached.available.filter(piece.canTake(position, _))
    val nowAvail = cached.available.toSet.diff(gone).toList
    CachedGameState(cached.state.withPiece(position, piece), nowAvail)
  }
}

trait BruteForceArrangements {
  protected def arrangements(board: Board, pieces: List[Piece]) = {
    val start = CachedGameState(GameState(board), board.positions.toList)
    arrangements(start, pieces).map { _.state }
  }

  protected def arrangements(cache: CachedGameState, pieces: List[Piece]): GenIterable[CachedGameState] = pieces match {
    case Nil => cache :: Nil
    case piece :: tail =>
      for {
        p <- cache.available.par
        // serial 6x6 RRHHHH takes 1 min
        // parallel 6x6 RRHHHH takes 33 secs
        if !piece.canTakeAny(p, cache.state.pieces.keys)
        n <- arrangements(CachedGameState(cache, p, piece), tail)
      } yield n
  }
}
