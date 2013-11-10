package com.github.fommil.chess

import math.abs
import scala.collection.immutable.TreeMap

object `package` {
  type Move = (Position, Piece)
}

case class Position(x: Int, y: Int) extends Ordered[Position] {
  def compare(that: Position) =
    if (y < that.y) -1
    else if (y == that.y) x - that.x
    else 1

  def -(that: Position) = Position(x - that.x, y - that.y)
}

trait ChessSolver {
  def solve(board: Board, pieces: List[Piece]): Int
}

case class GameState(board: Board, pieces: Map[Position, Piece] = TreeMap()) {
  def withMove(m: Move) = copy(pieces = pieces + m)

  def first(p: Piece) = pieces.filter(_._2 == p).headOption.map { _._1 }

  override def toString = {
    board.positions.map { p => {
      pieces.getOrElse(p, ".") match {
        case None => "."
        case Some(s) => s.toString.substring(0, 1)
      }
    } + (if (p.x + 1 == board.width) "\n" else "")
    }
  }.mkString("\n", "", "")
}

case class Board(width: Int, height: Int) {
  def positions = {
    for {
      y <- 0 until height
      x <- 0 until width
    } yield Position(x, y)
  }.toIterator
}

sealed trait Piece {
  def canTakeAny(from: Position, ps: Iterable[Position]) =
    ps.find(canTake(from, _)).isDefined

  def canTake(from: Position, to: Position): Boolean =
    canTake(to - from)

  protected def canTake(p: Position): Boolean

  protected def diag(p: Position) = abs(p.x) == abs(p.y)

  protected def xy(p: Position) = p.x == 0 || p.y == 0
}

case class King() extends Piece {
  protected def canTake(p: Position) = abs(p.x) <= 1 && abs(p.y) <= 1
}

case class Queen() extends Piece {
  protected def canTake(p: Position) = diag(p) || xy(p)
}

case class Rook() extends Piece {
  protected def canTake(p: Position) = xy(p)
}

case class Bishop() extends Piece {
  protected def canTake(p: Position) = diag(p)
}

case class Horsey() extends Piece {
  protected def canTake(p: Position) = (abs(p.x), abs(p.y)) match {
    case (1, 2) => true
    case (2, 1) => true
    case _ => false
  }
}


case class PreCompMoves(state: GameState, available: List[Position]) {
  def withMove(m: Move) = {
    val gone = Set(m._1) ++ available.filter(m._2.canTake(m._1, _))
    val nowAvail = available.toSet.diff(gone).toList
    PreCompMoves(state.withMove(m), nowAvail)
  }
}

object PreCompMoves {
  def apply(board: Board): PreCompMoves = PreCompMoves(GameState(board), board.positions.toList)
}
