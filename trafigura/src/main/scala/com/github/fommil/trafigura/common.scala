package com.github.fommil.trafigura

object `package` {
  // zero-indexed (x, y)
  type Position = (Int, Int)
}

case class GameState(board: Board, pieces: Map[Position, Piece] = Map()) {
  def withPiece(pos: Position, piece: Piece) = {
    require(board.isValid(pos))
    copy(pieces = pieces + (pos -> piece))
  }

  def available: Seq[Position] = for {
    x <- 0 until board.width
    y <- 0 until board.height
    if !pieces.contains((x, y))
    p = (x, y)
    if !canBeTaken(p)
  } yield p

  private def canBeTaken(p: Position) = ! {
    pieces.map { case (position, piece) =>
      piece.canTake(position, p, board)
    } filter (identity)
  }.isEmpty

  def canBeTakenBy(p: Position, piece: Piece) =
    !piece.moves(p, board).toSet.intersect(pieces.keySet).isEmpty

  override def toString = {
    for {
      y <- 0 until board.height
      x <- 0 until board.width
    } yield {
      (if (x == 0) "\n" else "") + {
        pieces.get((x, y)) match {
          case None => "."
          case Some(s) => s match {
            case King() => "K"
            case Queen() => "Q"
            case Rook() => "R"
            case Bishop() => "B"
            case Horsey() => "N"
          }
        }
      }
    }
  }.mkString("")

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

  def canTake(from: Position, to: Position, board: Board) =
    moves(from, board).contains(to)

  // all valid diagonal moves to a range.
  // could be optimised (code complexity)
  // to avoid the filter: benefits negligible
  protected def diag(p: Position, range: Int, board: Board) = {
    assert(range > 0)
    for {
      x <- 1 to range
      m <- (p._1 - x, p._2 - x) ::
        (p._1 + x, p._2 - x) ::
        (p._1 - x, p._2 + x) ::
        (p._1 + x, p._2 + x) :: Nil
    } yield m
  } filter board.isValid

  protected def xy(p: Position, range: Int, board: Board) = {
    assert(range > 0)
    for {x <- 1 to range
         m <- (p._1, p._2 - x) ::
           (p._1, p._2 + x) ::
           (p._1 - x, p._2) ::
           (p._1 + x, p._2) :: Nil
    } yield m
  } filter board.isValid

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
