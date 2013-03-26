package recfun
import common._
import scala.annotation.tailrec

object Main {
  def main(args: Array[String]) {
    println("Pascal's Triangle")
    for (row <- 0 to 10) {
      for (col <- 0 to row)
        print(pascal(col, row) + " ")
      println()
    }
  }

  /**
   * Exercise 1
   */
  def pascal(c: Int, r: Int): Int = {
    require(r >= 0 && c >= 0 && c <= r)
    if (c == 0 || c == r || r <= 1)
      1
    else
      pascal(c - 1, r - 1) + pascal(c, r - 1)
  }

  /**
   * Exercise 2
   */
  def balance(chars: List[Char]): Boolean = {
    @tailrec
    def balance(chars: List[Char], count: Int): Boolean = {
      if (chars.isEmpty) count == 0
      else {
        val c = chars.head match {
          case '(' => count + 1
          case ')' => count - 1
          case _ => count
        }
        if (c < 0) false
        else balance(chars.tail, c)
      }
    }
    balance(chars, 0)
  }

  /**
   * Exercise 3
   */
  def countChange(money: Int, coins: List[Int]): Int = {
    // I hate the traditional approach to this problem,
    // so I've gone for iterating all combinations then passing an
    // exclusion function. Unfortunately has a jump up recursion.

    def countsUsingAllCoins(money: Int, coins: List[Int]): Int = {
      val sum = (0 /: coins)(_ + _)
      if (sum > money) 0
      else if (sum == money) 1
      else countChange(money - sum, coins) // ouch
    }

    def combinations[T](list: List[T]) = (1 to list.length).flatMap(list combinations _)
    (0 /: combinations(coins))(_ + countsUsingAllCoins(money, _))
  }
}
