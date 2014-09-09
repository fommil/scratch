package com.github.fommil.semantic

import org.scalatest.FunSuite

class SemanticTest extends FunSuite {
  test("How old is Tony Blair") {
    val answer = Question.ask("How old is Tony Blair?")
    assert("61" === answer)
  }
  test("What is the birth place of David Cameron") {
    val answer = Question.ask("What is the birth place of David Cameron?")
    assert("London, United Kingdom" === answer)
  }
}
