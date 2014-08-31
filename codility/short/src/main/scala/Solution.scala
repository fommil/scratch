import scala.collection.JavaConversions._

// NOTE: I lost internet connection and quite a bit of time
//       from working on this, so it is hastily
//       constructed and missing review / refinement.
object Solution {
  def solution(a: Array[Int]): Array[Int] = {
    type City = Int
    type Road = (Int, Int)

    // I'm ridiculously sorry for the amount of mutable
    // state in this solution. If I had time I'd refactor
    // to be entirely immutable. I may as well have written
    // this in fortran

    // TODO: foldLeft and don't be mutable
    var capital: City = -1
    var roads: List[Road] = Nil
    (0 until a.length) foreach {
      case i if i == a(i) => capital = i
      case i =>
        roads = (a(i), i) :: (i, a(i)) :: roads
    }

    // 3rd party libs make .toMultiMap easy
    // and never use mapValues, it is lazy
    val lookup = roads.groupBy(_._1).map {
      case (k, e) => (k, e.map(v => v._2).toSet)
    }

    var visited = Set.empty[City]
    var distances = Array.fill[Set[City]](a.length - 1)(Set.empty)

    // yuck, really I'm sorry you have to see this
    distances(0) = lookup(capital)
    visited ++= distances(0) + capital
    (1 until distances.length) foreach { i =>
      val last = distances(i - 1)
      val now = last.flatMap(lookup) -- visited
      distances(i) = now
      visited ++= now
    }

    distances.map(_.size)
  }
}
