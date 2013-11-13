package simulations

import math.random

class EpidemySimulator extends Simulator {

  def randomBelow(i: Int) = (random * i).toInt

  protected[simulations] object SimConfig {
    val population: Int = 300
    val roomRows: Int = 8
    val roomColumns: Int = 8

    val transmissibility = 0.4
    val prevalence = 0.01
    val deathRate = 0.25

    // extensions
    val airTravel = 0
    val chosenFew = 0
    val reducedMobility = false
  }

  import SimConfig._

  val persons: List[Person] = (0 until population).map {
    new Person(_)
  }.toList

  persons foreach {
    _.mode
  }

  def inRoom(r: (Int, Int)) = persons.filter { p =>
      p.row == r._1 && p.col == r._2
  }

  def isInfected(room: (Int, Int)) = inRoom(room).count(_.infected) > 0

  class Person(val id: Int) {
    var infected = false
    var sick = false
    var immune = random < chosenFew
    var dead = false
    var row: Int = randomBelow(roomRows)
    var col: Int = randomBelow(roomColumns)

    override def toString() = s"#$id@($row, $col)"

    // init
    if (id < population * prevalence) {
      lurgy
    }

    def mode {
      if (dead) return
      val wait = randomBelow(5)
      afterDelay(wait) {
        chooseRoom match {
          case _ if reducedMobility & sick =>
          case Some(room) => move(room)
          case _ =>
        }
        mode
      }
    }

    private def move(room: (Int, Int)) {
      if (dead) return
      row = room._1
      col = room._2
      if (!immune && isInfected(room) && random < transmissibility)
        lurgy
    }

    private def lurgy {
      infected = true
      afterDelay(6) {
        sick = true
        afterDelay(8) {
          if (random < deathRate)
            dead = true
          else afterDelay(2) {
            immune = true
            afterDelay(2) {
              infected = false
              sick = false
              immune = false
            }
          }
        }
      }
    }

    private def chooseRoom = {
      if (random < airTravel)
        Some(randomBelow(roomRows), randomBelow(roomColumns))
      else {
        val ns = neighbours.toList
        if (ns.isEmpty) None
        else Some(ns(randomBelow(ns.size)))
      }
    }

    private def neighbours = for {
      move <- (-1, 0) ::(1, 0) ::(0, -1) ::(0, 1) :: Nil
      room = (
        (roomRows + move._1 + row) % roomRows,
        (roomColumns + move._2 + col) % roomColumns
        )
      if inRoom(room).count(_.sick) == 0
    } yield room
  }

}
