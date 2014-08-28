object Solution {
  // Long avoids overflow on sum and 2*
  def solution(a: Array[Int]): Int = {
    val sum = a.foldLeft(0: Long)(_ + _) // O(n)
    def rec(i: Int, acc: Long): Int = {
      if (i >= a.length) -1
      else if (2 * acc + a(i) == sum) i
      else rec(i + 1, acc + a(i))
    }
    rec(0, 0)
  }
}
