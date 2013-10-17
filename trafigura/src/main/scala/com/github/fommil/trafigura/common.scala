package com.github.fommil.trafigura

/** Find all unique configurations of chess pieces on a board of dimension `M × N`,
  * where none of the pieces can capture any of the others, ignoring colour.
  *
  * @author Sam Halliday
  */
trait ChessSolver

sealed trait Piece

case class King() extends Piece
case class Queen() extends Piece
case class Rook() extends Piece
case class Bishop() extends Piece
case class Horsey() extends Piece

object ChessSolver extends App {


}