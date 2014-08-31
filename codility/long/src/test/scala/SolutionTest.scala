import org.scalatest.FunSpec
import org.scalatest.matchers.ShouldMatchers
import Solution.solution

class SolutionTest extends FunSpec with ShouldMatchers {

  val ex1 = Array(10, 2, 5, 1, 8, 20)
  val ex2 = Array(5, 10, 18, 7, 8, 3)
  val ex3 = Array(10, 20, 30)

  describe("Solution") {
    it("should pass the first example") {
      assert(solution(ex1) === 23)
    }
    it("should pass the second example") {
      assert(solution(ex2) === 15)
    }
    it("should pass the third example") {
      assert(solution(ex3) === -1)
    }

    it("should pass variations of the first example") {
      ex1.permutations foreach { ex =>
        assert(solution(ex) === 23)
      }
    }
    it("should pass variations of the second example") {
      ex2.permutations foreach { ex =>
        assert(solution(ex) === 15)
      }
    }
    it("should pass variations of the third example") {
      ex3.permutations foreach { ex =>
        assert(solution(ex) === -1)
      }
    }
  }
}
