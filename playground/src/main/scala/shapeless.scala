package fommil.polys

import shapeless._

sealed trait Trait
case class Foo() extends Trait
case class Bar() extends Trait

trait Thing[T] { def thingy: String }

// https://github.com/milessabin/shapeless/issues/361
object Shapeless extends App {
  implicit def foo: Thing[Foo] = new Thing[Foo] { def thingy = "foo" }
  implicit def bar: Thing[Bar] = new Thing[Bar] { def thingy = "bar" }

  // this is the bit I'd like to simplify...
  // def thing(t: Trait): String = t match {
  //   case Foo() => implicitly[Thing[Foo]].thingy
  //   case Bar() => implicitly[Thing[Bar]].thingy
  // }

  // with this!
  object thing extends Poly1 {
    implicit def thingAt[T <: Trait: Thing] = at[T](
      a => implicitly[Thing[T]].thingy
    )
  }

  val blah = thing(Foo())
  println(blah)

}
