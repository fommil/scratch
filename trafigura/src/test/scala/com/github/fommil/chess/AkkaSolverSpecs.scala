package com.github.fommil.chess

import akka.actor.{Props, ActorSystem}
import org.specs2.specification.{Fragments, Step}

class AkkaSolverSpecs extends ChessSolverSpecs {
  val system = ActorSystem()
  system.actorOf(Props[ChessSearch], "chess")
  val solver = new AkkaSolver(system) with ChessOptimisations

  // https://groups.google.com/d/topic/specs2-users/PdCeX4zxc0A/discussion
  override def map(fs: => Fragments) = super.map(fs) ^ Step(system.shutdown())
}
