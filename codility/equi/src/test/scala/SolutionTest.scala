import org.scalatest.FunSpec
import org.scalatest.matchers.ShouldMatchers

class SolutionTest extends FunSpec with ShouldMatchers {
  import Solution.solution

  describe("Solution") {
    it("should pass the example") {
      val result = solution(Array(-1, 3, -4, 5, 1, -6, 2, 1))
      assert(result === 1 || result === 3 || result === 7)
    }

    it("should pass a basic positive only example") {
      assert(solution(Array(0, 1, 2, 0, 2, 1, 0)) === 3)
    }

    it("should pass a basic negative only example") {
      assert(solution(Array(0, -1, -2, 0, -2, -1, 0)) === 3)
    }

    it("should quickly find no-solution case") {
      assert(solution(Array(0, 1, 2, 3, 1, 0)) === -1)
    }

    it("should quickly solve the trivial case") {
      assert(solution(Array.ofDim(10)) === 0)
    }

    it("should handle integer overflow") {
      assert(solution(Array.fill(5)(Int.MaxValue)) === 2)
    }
  }
}
