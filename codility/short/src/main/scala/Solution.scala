object Solution {
  // self-contained alternative to
  // import pimpathon.list._
  implicit class RichTupleList[K, V](a: List[(K, V)]) {
    def asSetMultiMap: Map[K, Set[V]] = a.groupBy(_._1).map {
      case (k, e) => (k, e.map(_._2).toSet)
    }
  }

  type City = Int
  type Road = (Int, Int)

  def solution(a: Array[Int]): Array[Int] = {
    require(a.nonEmpty, "no data")
    val (capital, roads) = (0 until a.length).foldLeft(
      (-1: Int, Nil: List[Road]) // non-sensical defaults
    ) {
      case ((_, r), i) if i == a(i) => (i, r)
      case ((c, r), i) => (c, (a(i), i) :: (i, a(i)) :: r)
    }
    require(capital != -1, "no capital")
    require(roads != Nil, "no roads")
    val neighbours = roads.asSetMultiMap

    // NOTE: if we could generate neighbours such that
    //       it was directed away from the capital, then
    //       we wouldn't need to pass the ignore list
    def distances(start: Set[City], ignore: Set[City]): List[Int] =
      (start.flatMap(neighbours) -- ignore) match {
        case cities if cities.isEmpty => Nil
        case cities => cities.size :: distances(cities, ignore ++ cities)
    }

    distances(Set(capital), Set(capital)).padTo(a.length - 1, 0).toArray
  }
}
