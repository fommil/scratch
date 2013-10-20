package com.github.fommil.trafigura

object `package` {
  // zero-indexed (x, y)
  type Position = (Int, Int)
}

trait ChessSolver {
  def solve(board: Board, pieces: List[Piece]): List[GameState]
}

case class GameState(board: Board, pieces: Map[Position, Piece] = Map()) {
  def withPiece(pos: Position, piece: Piece) =
    copy(pieces = pieces + (pos -> piece))

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

case class Board(width: Int, height: Int)

sealed trait Piece {
  def canTakeAny(from: Position, ps: Iterable[Position]) =
    ps.find(canTake(from, _)).isDefined

  def canTake(from: Position, to: Position): Boolean =
    canTake(to._1 - from._1, to._2 - from._2)

  protected def canTake(x: Int, y: Int): Boolean

  protected def diag(x: Int, y: Int) = math.abs(x) == math.abs(y)

  protected def xy(x: Int, y: Int) = x == 0 || y == 0
}

case class King() extends Piece {
  protected def canTake(x: Int, y: Int) = math.abs(x) <= 1 && math.abs(y) <= 1
}

case class Queen() extends Piece {
  protected def canTake(x: Int, y: Int) = diag(x, y) || xy(x, y)
}

case class Rook() extends Piece {
  protected def canTake(x: Int, y: Int) = xy(x, y)
}

case class Bishop() extends Piece {
  protected def canTake(x: Int, y: Int) = diag(x, y)
}

case class Horsey() extends Piece {
  protected def canTake(x: Int, y: Int) = (math.abs(x), math.abs(y)) match {
    case (1, 2) => true
    case (2, 1) => true
    case _ => false
  }
}
