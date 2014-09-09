package com.github.fommil

import spray.json._

object SprayJsonOptionSeqs extends App {

  case class Thing(
    a: Seq[String],
    b: Seq[String]
  )

  val thing = Thing(Nil, List("hello"))

  import DefaultJsonProtocol._
  import SomeThing._

  // proxy marshalled form of Thing
  case class SomeThing(
    a: Option[Seq[String]],
    b: Option[Seq[String]]
  ) {
    private def pull[T](os: Option[Seq[T]]): Seq[T] = os match {
      case None => Nil
      case Some(ts) => ts
    }
    def thing: Thing = Thing(pull(a), pull(b))
  }
  object SomeThing {
    private def push[T](ts: Seq[T]): Option[Seq[T]] =
      if (ts.isEmpty) None
      else Some(ts)
    def from(thing: Thing) = SomeThing(
      push(thing.a),
      push(thing.b)
    )
  }

  // this is what you'd get with out-of-the-box formatting
  val ThingFormat = jsonFormat2(Thing)
  println(ThingFormat.write(thing)) // {"a":[],"b":["hello"]}

  // .apply needed because we have a custom companion
  implicit val SomeThingFormat = jsonFormat2(SomeThing.apply) 

  implicit object ThingProxyFormat extends JsonFormat[Thing] {
    def write(o: Thing): JsValue =
      SomeThingFormat.write(SomeThing.from(o))

    def read(j: JsValue): Thing =
      SomeThingFormat.read(j).thing
  }

  println(thing.toJson) // {"b":["hello"]}

}
