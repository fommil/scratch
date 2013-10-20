package com.github.fommil.trafigura

import org.specs2.execute.Success

/** @author Sam Halliday */
class PiecesSpecs extends Specs {

  "king" should {
    "have three moves from a corner" in {
      King().moves((0, 0), Board(9, 9)) must containTheSameElementsAs {
        (0, 1) ::(1, 0) ::(1, 1) :: Nil
      }
    }

    "have eight moves from the middle" in {
      King().moves((4, 4), Board(9, 9)) must containTheSameElementsAs {
        (3, 3) ::(3, 4) ::(4, 3) ::(3, 5) ::(5, 3) ::(4, 5) ::(5, 4) ::(5, 5) :: Nil
      }
    }
  }

  "bishop" should {
    "move one direction from a corner" in {
      Bishop().moves((0, 0), Board(9, 9)) must containTheSameElementsAs {
        (1, 1) ::(2, 2) ::(3, 3) ::(4, 4) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) :: Nil
      }
    }

    "move four directions from the middle" in {
      Bishop().moves((4, 4), Board(9, 9)) must containTheSameElementsAs {
        (0, 0) ::(1, 1) ::(2, 2) ::(3, 3) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) ::
          (3, 5) ::(2, 6) ::(1, 7) ::(0, 8) ::
          (5, 3) ::(6, 2) ::(7, 1) ::(8, 0) :: Nil
      }
    }
  }

  "rook" should {
    "move two directions from a corner" in {
      Rook().moves((0, 0), Board(9, 9)) must containTheSameElementsAs {
        (0, 1) ::(0, 2) ::(0, 3) ::(0, 4) ::(0, 5) ::(0, 6) ::(0, 7) ::(0, 8) ::
          (1, 0) ::(2, 0) ::(3, 0) ::(4, 0) ::(5, 0) ::(6, 0) ::(7, 0) ::(8, 0) :: Nil
      }
    }

    "move four directions from the middle" in {
      Rook().moves((4, 4), Board(9, 9)) must containTheSameElementsAs {
        (4, 0) ::(4, 1) ::(4, 2) ::(4, 3) ::(4, 5) ::(4, 6) ::(4, 7) ::(4, 8) ::
          (0, 4) ::(1, 4) ::(2, 4) ::(3, 4) ::(5, 4) ::(6, 4) ::(7, 4) ::(8, 4) :: Nil
      }
    }
  }

  "queen" should {
    "move three directions from a corner" in {
      Queen().moves((0, 0), Board(9, 9)) must containTheSameElementsAs {
        (0, 1) ::(0, 2) ::(0, 3) ::(0, 4) ::(0, 5) ::(0, 6) ::(0, 7) ::(0, 8) ::
          (1, 0) ::(2, 0) ::(3, 0) ::(4, 0) ::(5, 0) ::(6, 0) ::(7, 0) ::(8, 0) ::
          (1, 1) ::(2, 2) ::(3, 3) ::(4, 4) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) :: Nil
      }
    }

    "move eight directions from the middle" in {
      Queen().moves((4, 4), Board(9, 9)) must containTheSameElementsAs {
        (0, 0) ::(1, 1) ::(2, 2) ::(3, 3) ::(5, 5) ::(6, 6) ::(7, 7) ::(8, 8) ::
          (3, 5) ::(2, 6) ::(1, 7) ::(0, 8) ::
          (5, 3) ::(6, 2) ::(7, 1) ::(8, 0) ::
          (4, 0) ::(4, 1) ::(4, 2) ::(4, 3) ::(4, 5) ::(4, 6) ::(4, 7) ::(4, 8) ::
          (0, 4) ::(1, 4) ::(2, 4) ::(3, 4) ::(5, 4) ::(6, 4) ::(7, 4) ::(8, 4) :: Nil
      }
    }
  }

  "horsey" should {
    "have two moves from a corner" in {
      Horsey().moves((0, 0), Board(9, 9)) must containTheSameElementsAs {
        (2, 1) ::(1, 2) :: Nil
      }
    }

    "have 8 moves from the centre" in {
      Horsey().moves((4, 4), Board(9, 9)) must containTheSameElementsAs {
        (6, 3) ::(6, 5) ::
          (2, 3) ::(2, 5) ::
          (3, 6) ::(5, 6) ::
          (3, 2) ::(5, 2) :: Nil
      }
    }

    "have four moves in a restricted board" in {
      Horsey().moves((2, 2), Board(4, 4)) must containTheSameElementsAs {
        (1, 0) ::(3, 0) ::(0, 1) ::(0, 3) :: Nil
      }
    }
  }

  "available" should {
    "produce one result" in {
      GameState(Board(4, 4),
        Map(
          (0, 0) -> Rook(),
          (2, 2) -> Rook(),
          (1, 1) -> Horsey(),
          (3, 1) -> Horsey()
        )
      ).available.size must beGreaterThan(0)
    }
  }



  "wookie" should {
    "always win" in {
      Success("or he'll rip your arms off")
    }
  }

}
