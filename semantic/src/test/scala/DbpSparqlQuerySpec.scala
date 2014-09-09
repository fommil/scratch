package com.github.fommil.semantic

import org.scalatest._

class DbpSparqlQuerySpec extends FunSpec with Matchers with Inside {
  val Tony_Blair = Entity("http://dbpedia.org/resource/Tony_Blair")
  val David_Cameron = Entity("http://dbpedia.org/resource/David_Cameron")

  describe ("DateOfBirthQuery") {
    it("should return Tony Blair's date of birth") {
      assert(DateOfBirthQuery.askT(Tony_Blair) ===
        Some(DateOfBirth(-525664800000L)))
    }
  }

  describe ("AgeQuery") {
    // this is temporal
    it("should return Tony Blair's age") {
      assert(AgeQuery.askT(Tony_Blair) ===
        Some(Age(61)))
    }
  }

  describe ("BirthPlaceQuery") {
    it("should return David Cameron's birth place") {
      assert(BirthPlaceQuery.askT(David_Cameron) ===
        Some(BirthPlace("London", "the United Kingdom")))
    }
  }

}
