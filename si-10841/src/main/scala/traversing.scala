package foo

import cats._, implicits._
import cats.effect.Effect

object RedSquiggles {
  def red[F[_]: Effect](ss: List[String]): F[List[String]] =
    ss.traverse(b => bar(b))

  def bar[F[_]: Effect](b: String): F[String] = ???
}
