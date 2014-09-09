package com.github.fommil.semantic

import org.scalatest._

class QuestionParserSpec extends FunSpec with Matchers with Inside {
  import QuestionParser.parse
  describe ("com.github.fommil.semantic.QuestionParser") {
    it("should detect questions about age") {
      inside(parse("how old is bob?")) {
        case Some((AgeQuery, e)) =>
          e should be("bob")
      }
    }

    it("should detect questions about birth places") {
      inside(parse("what is the birth place of bob?")) {
        case Some((BirthPlaceQuery, e)) =>
          e should be("bob")
      }
    }


  }
}
