package com.github.fommil.chess

import math.abs

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
      {
        pieces.get((x, y)) match {
          case None => "."
          case Some(s) => s.toString.substring(0, 1)
        }
      } + (if (x + 1 == board.width) "\n" else "")
    }
  }.mkString("\n", "", "")
}

case class Board(width: Int, height: Int) {
  def positions = for {
    x <- 0 until width
    y <- 0 until height
  } yield (x, y)
}

sealed trait Piece {
  def canTakeAny(from: Position, ps: Iterable[Position]) =
    ps.find(canTake(from, _)).isDefined

  def canTake(from: Position, to: Position): Boolean =
    canTake((to._1 - from._1, to._2 - from._2))

  protected def canTake(p: Position): Boolean

  protected def diag(p: Position) = abs(p._1) == abs(p._2)

  protected def xy(p: Position) = p._1 == 0 || p._2 == 0
}

case class King() extends Piece {
  protected def canTake(p: Position) = abs(p._1) <= 1 && abs(p._2) <= 1
}

case class Queen() extends Piece {
  protected def canTake(p: Position) = diag(p._1, p._2) || xy(p._1, p._2)
}

case class Rook() extends Piece {
  protected def canTake(p: Position) = xy(p._1, p._2)
}

case class Bishop() extends Piece {
  protected def canTake(p: Position) = diag(p._1, p._2)
}

case class Horsey() extends Piece {
  protected def canTake(p: Position) = (abs(p._1), abs(p._2)) match {
    case (1, 2) => true
    case (2, 1) => true
    case _ => false
  }
}
