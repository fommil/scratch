package com.github.fommil.trafigura

import org.specs2.mutable.Specification
import akka.contrib.jul.JavaLogging
import org.specs2.control.StackTraceFilter

/** Uses the J2SE Logging framework for specs2 stack traces.
  *
  * To enable, put the following in the Specification
  * {{{
  *     args.report(traceFilter=LoggedStackTraceFilter)
  * }}}
  *
  * @see https://groups.google.com/d/topic/specs2-users/3cCUf-kUsaU/discussion
  */
object LoggedStackTraceFilter extends StackTraceFilter with JavaLogging {
  def apply(e: Seq[StackTraceElement]) = Nil
  override def apply[T <: Throwable](e: T): T = {
    log.error(e, "Specs2")
    // this only works because log.error will construct the LogRecord instantly
    e.setStackTrace(new Array[StackTraceElement](0))
    e
  }
}

abstract class Specs extends Specification with JavaLogging {
  args.report(traceFilter = LoggedStackTraceFilter)
}
