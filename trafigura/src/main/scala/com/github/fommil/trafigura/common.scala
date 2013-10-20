package com.github.fommil.trafigura

import akka.contrib.jul.JavaLogging

object `package` {
  // zero-indexed (x, y)
  type Position = (Int, Int)
}

/** Find all unique configurations of chess pieces on a board of dimension `M × N`,
  * where none of the pieces can capture any of the others, ignoring colour.
  *
  * @author Sam Halliday
  */
trait ChessSolver

case class GameState(board: Board, pieces: Map[Position, Piece] = Map()) {
  def withPiece(pos: Position, piece: Piece) = {
    require(board.isValid(pos))
    copy(pieces = pieces + (pos -> piece))
  }
}


case class Board(width: Int, height: Int) {
  require(width > 0 && height > 0)

  def isValid(p: Position) = {
    p._1 >= 0 && p._2 >= 0 && p._1 < width && p._2 < height
  }
}

sealed trait Piece {
  def canTake(from: Position, board: Board)(to: Position) = moves(from, board).contains(to)

  def moves(from: Position, board: Board): Seq[Position]

  // all valid diagonal moves to a range.
  // could be optimised (code complexity)
  // to avoid the filter: benefits negligible
  protected def diag(p: Position, range: Int, board: Board) = {
    assert(range > 0)
    for (x <- 1 to range) yield
      (p._1 - x, p._2 - x) ::
        (p._1 + x, p._2 - x) ::
        (p._1 - x, p._2 + x) ::
        (p._1 + x, p._2 + x) :: Nil
  }.flatten filter board.isValid

  protected def xy(p: Position, range: Int, board: Board) = {
    assert(range > 0)
    for (x <- 1 to range) yield
      (p._1, p._2 - x) ::
        (p._1, p._2 + x) ::
        (p._1 - x, p._2) ::
        (p._1 + x, p._2) :: Nil
  }.flatten filter board.isValid

  // largest distance to any side of the board
  protected def toSide(p: Position, board: Board) =
    (p._1 :: board.width - p._1 :: p._2 :: board.height - p._2 :: Nil).max

}

case class King() extends Piece {
  def moves(p: Position, board: Board) = xy(p, 1, board) ++ diag(p, 1, board)
}

case class Queen() extends Piece {
  def moves(p: Position, board: Board) = {
    val range = toSide(p, board)
    xy(p, range, board) ++ diag(p, range, board)
  }
}

case class Rook() extends Piece {
  def moves(p: Position, board: Board) = xy(p, toSide(p, board), board)
}

case class Bishop() extends Piece {
  def moves(p: Position, board: Board) = diag(p, toSide(p, board), board)
}

case class Horsey() extends Piece {
  def moves(p: Position, board: Board) = {
    (p._1 + 2, p._2 + 1) ::(p._1 + 2, p._2 - 1) ::
      (p._1 - 2, p._2 + 1) ::(p._1 - 2, p._2 - 1) ::
      (p._1 - 1, p._2 + 2) ::(p._1 + 1, p._2 + 2) ::
      (p._1 - 1, p._2 - 2) ::(p._1 + 1, p._2 - 2) :: Nil
  } filter board.isValid
}


object Chess extends App with JavaLogging {
  log.info("hello world")
}
