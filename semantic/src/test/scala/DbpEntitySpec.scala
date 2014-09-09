package com.github.fommil.semantic

import org.scalatest._

class DbpEntitySpec extends FunSpec with Matchers with Inside {

  def resolve(query: String, expect: String): Unit = {
    inside(DbpEntity.unapply("Tony Blair")) {
      case Some(Entity(uri)) =>
        uri should be ("http://dbpedia.org/resource/Tony_Blair")
    }
  }

  describe ("com.github.fommil.semantic.DbpEntity") {
    it("should resolve Tony Blair") {
      resolve("Tony Blair", "http://dbpedia.org/resource/Tony_Blair")
    }

    it("should resolve David Cameron") {
      resolve("David Cameron", "http://dbpedia.org/resource/David_Cameron")
    }

    it("should not resolve Scary Biscuits") {
      assert(DbpEntity.unapply("Scary Biscuits") === None)
    }
  }
}
