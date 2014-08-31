// NOTE: I lost internet connection and quite a bit of time
//       from working on this, so it is hastily
//       constructed and missing review / refinement.
object Solution {
    def solution(a: Array[Int]): Int = {
      // brute force goodness... probably doesn't pass
      // but I have 10 minutes left thanks to a drop
      // in the internet connection.

      // Int is ok, doesn't look like we have a Long overflow
      def isTriangle(p: Int, q: Int, r: Int) = {
        a(p) + a(q) > a(r) &&
        a(q) + a(r) > a(p) &&
        a(r) + a(p) > a(q)
      }

      def perim(p: Int, q: Int, r: Int) =
        a(p) + a(q) + a(r)

      val perims = for {
        i <- 0 until a.length
        j <- (i + 1) until a.length
        k <- (j + 1) until a.length
        if isTriangle(i, j, k)
      } yield perim(i, j, k)

      if (perims.isEmpty) -1
      else perims.min
    }
}
