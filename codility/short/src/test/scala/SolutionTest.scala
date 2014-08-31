import org.scalatest.FunSpec
import org.scalatest.matchers.ShouldMatchers
import Solution.solution

class SolutionTest extends FunSpec with ShouldMatchers {
  describe("Solution") {
    it("should pass the example") {
      val res = solution(Array(9, 1, 4, 9, 0, 4, 8, 9, 0, 1))
      assert(res === Array(1, 3, 2, 3, 0, 0, 0, 0, 0))
    }
  }
}
