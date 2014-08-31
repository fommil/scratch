import org.scalatest.FunSpec
import org.scalatest.matchers.ShouldMatchers
import Solution.solution

class SolutionTest extends FunSpec with ShouldMatchers {
  describe("Solution") {
    it("should pass the first example") {
      val res = solution(Array(10, 2, 5, 1, 8, 20))
      assert(res === 23)
    }
    it("should pass the second example") {
      val res = solution(Array(5, 10, 18, 7, 8, 3))
      assert(res === 15)
    }
    it("should pass the third example") {
      val res = solution(Array(10, 20, 30))
      assert(res === -1)
    }
  }
}
