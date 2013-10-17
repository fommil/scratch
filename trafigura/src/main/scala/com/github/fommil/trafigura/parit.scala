package com.github.fommil.trafigura

import scala.concurrent.{Await, Future, ExecutionContext}
import scala.collection.mutable
import scala.concurrent.duration.Duration

/** @author Sam Halliday */
class ParMapIterator[T](it: Iterator[T], buffered: Int = 100)
                       (implicit context: ExecutionContext) extends Iterator[T] {

  def hasNext = it.hasNext

  def next() = it.next()

  override def map[B](f: T => B) = {
    val buffer = new mutable.Queue[Future[B]]()
    def push() = if (it.hasNext) buffer.enqueue {
      val n = it.next()
      Future {
        f(n)
      }
    }

    for (i <- 0 until buffered) push()

    new Iterator[B] {
      def hasNext = !buffer.isEmpty

      def next() = {
        val n = buffer.dequeue()
        push()
        Await.result(n, Duration.Inf)
      }
    }
  }
}

object ParMapIterator {

  implicit class ParPimpedIterator[T](it: Iterator[T]) {
    def par(buffered: Int)(implicit context: ExecutionContext) = new ParMapIterator[T](it, buffered)

    def par(implicit context: ExecutionContext) = new ParMapIterator[T](it)
  }

}