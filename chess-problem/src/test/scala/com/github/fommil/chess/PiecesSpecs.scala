package com.github.fommil.chess

import org.specs2.execute.Success

/** @author Sam Halliday */
class PiecesSpecs extends Specs {

  def takeSpec(piece: Piece, from: (Int, Int), e: List[(Int, Int)]) = {
    val expected = e.map { p => Position(p._1, p._2) }
    Board(9, 9).positions.filterNot(p => p.x == p.y).map { p =>
      val take = piece.canTake(Position(from._1, from._2), p)
      if (expected.contains(p)) take must beTrue
      else take must beFalse
    }.toList
  }

  "king" should {
    "have eight moves" in {
      val expected = (3, 3) ::(3, 4) ::(4, 3) ::(3, 5) ::(5, 3) ::(4, 5) ::(5, 4) ::(5, 5) :: Nil
      takeSpec(King(), (4, 4), expected)
    }
  }

  "bishop" should {
    "move in four directions" in {
      val expected = (0, 0) ::(1, 1) ::(2, 2) ::(3, 3) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) ::
        (3, 5) ::(2, 6) ::(1, 7) ::(0, 8) ::
        (5, 3) ::(6, 2) ::(7, 1) ::(8, 0) :: Nil
      takeSpec(Bishop(), (4, 4), expected)
    }
  }

  "rook" should {
    "move in four directions" in {
      val expected = (4, 0) ::(4, 1) ::(4, 2) ::(4, 3) ::(4, 5) ::(4, 6) ::(4, 7) ::(4, 8) ::
        (0, 4) ::(1, 4) ::(2, 4) ::(3, 4) ::(5, 4) ::(6, 4) ::(7, 4) ::(8, 4) :: Nil
      takeSpec(Rook(), (4, 4), expected)
    }
  }

  "queen" should {
    "move in eight directions" in {
      val expected = (0, 0) ::(1, 1) ::(2, 2) ::(3, 3) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) ::
        (3, 5) ::(2, 6) ::(1, 7) ::(0, 8) ::
        (5, 3) ::(6, 2) ::(7, 1) ::(8, 0) ::
        (4, 0) ::(4, 1) ::(4, 2) ::(4, 3) ::(4, 5) ::(4, 6) ::(4, 7) ::(4, 8) ::
        (0, 4) ::(1, 4) ::(2, 4) ::(3, 4) ::(5, 4) ::(6, 4) ::(7, 4) ::(8, 4) :: Nil
      takeSpec(Queen(), (4, 4), expected)
    }
  }

  "horsey" should {
    "have 8 moves" in {
      val expected = (6, 3) ::(6, 5) ::(2, 3) ::(2, 5) ::(3, 6) ::(5, 6) ::(3, 2) ::(5, 2) :: Nil
      takeSpec(Horsey(), (4, 4), expected)
    }
  }

  "wookie" should {
    "always win" in {
      Success("or he'll rip your arms off")
    }
  }

}
