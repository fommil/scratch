package com.github.fommil.trafigura

import akka.actor.{Props, ActorSystem}

class AkkaSolverSpecs extends ChessSolverSpecs {
  val system = ActorSystem()
  system.actorOf(Props[ChessSearch], "chess")
  val solver = new AkkaSolver(system) with ChessOptimisations
}
