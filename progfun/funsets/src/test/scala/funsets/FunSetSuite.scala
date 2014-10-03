package funsets

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

/**
 * This class is a test suite for the methods in object FunSets. To run
 * the test suite, you can either:
 *  - run the "test" command in the SBT console
 *  - right-click the file in eclipse and chose "Run As" - "JUnit Test"
 */
@RunWith(classOf[JUnitRunner])
class FunSetSuite extends FunSuite {


  /**
   * Link to the scaladoc - very clear and detailed tutorial of FunSuite
   *
   * http://doc.scalatest.org/1.8/index.html#org.scalatest.FunSuite
   *
   * Operators
   *  - test
   *  - ignore
   *  - pending
   */

  /**
   * Tests are written using the "test" operator and the "assert" method.
   */
  test("string take") {
    val message = "hello, world"
    assert(message.take(5) == "hello")
  }

  /**
   * For ScalaTest tests, there exists a special equality operator "===" that
   * can be used inside "assert". If the assertion fails, the two values will
   * be printed in the error message. Otherwise, when using "==", the test
   * error message will only say "assertion failed", without showing the values.
   *
   * Try it out! Change the values so that the assertion fails, and look at the
   * error message.
   */
  test("adding ints") {
    assert(1 + 2 === 3)
  }

  
  import FunSets._

  test("contains is implemented") {
    assert(contains(x => true, 100))
  }
  
  /**
   * When writing tests, one would often like to re-use certain values for multiple
   * tests. For instance, we would like to create an Int-set and have multiple test
   * about it.
   * 
   * Instead of copy-pasting the code for creating the set into every test, we can
   * store it in the test class using a val:
   * 
   *   val s1 = singletonSet(1)
   * 
   * However, what happens if the method "singletonSet" has a bug and crashes? Then
   * the test methods are not even executed, because creating an instance of the
   * test class fails!
   * 
   * Therefore, we put the shared values into a separate trait (traits are like
   * abstract classes), and create an instance inside each test method.
   * 
   */

  trait TestSets {
    val s1 = singletonSet(1)
    val s2 = singletonSet(2)
    val s3 = singletonSet(3)
  }

  /**
   * This test is currently disabled (by using "ignore") because the method
   * "singletonSet" is not yet implemented and the test would fail.
   * 
   * Once you finish your implementation of "singletonSet", exchange the
   * function "ignore" by "test".
   */
  test("singletonSet(1) contains 1") {
    
    /**
     * We create a new instance of the "TestSets" trait, this gives us access
     * to the values "s1" to "s3". 
     */
    new TestSets {
      /**
       * The string argument of "assert" is a message that is printed in case
       * the test fails. This helps identifying which assertion failed.
       */
      assert(contains(s1, 1), "Singleton")
    }
  }

  test("union contains all elements") {
    new TestSets {
      val s = union(s1, s2)
      assert(contains(s, 1), "Union 1")
      assert(contains(s, 2), "Union 2")
      assert(!contains(s, 3), "Union 3")
    }
  }

  test("intersect ...") {
    new TestSets {
      assert(!contains(intersect(s1, s2), 1), "Intersect 1")
      assert(!contains(intersect(s1, s2), 2), "Intersect 2")
      assert(!contains(intersect(s1, s2), 3), "Intersect 3")
      assert(contains(intersect(s1, s1), 1), "Intersect 4")
    }
  }

  test("diff ...") {
    new TestSets {
      assert(!contains(diff(s1, s1), 1), "Diff 1")
      assert(!contains(diff(x => true, s1), 1), "Diff 2")
      assert(contains(diff(x => true, s2), 1), "Diff 3")
    }
  }

  test("filter ...") {
    new TestSets {
      assert(contains(filter(s1, s1), 1), "Filter 1")
      assert(!contains(filter(s1, s2), 1), "Filter 2")
      assert(contains(filter(x => true, s1), 1), "Filter 3")
      assert(!contains(filter(x => true, s1), 2), "Filter 3a")
      assert(contains(filter(s1, x => true), 1), "Filter 4")
      assert(!contains(filter(x => false, s1), 1), "Filter 5")
      assert(!contains(filter(s1, x => false), 1), "Filter 6")
    }
  }

  object TestFunctions {
    def dirac(i : Int) = (j: Int) => i == j

    val odd = (i: Int) => (i & 1) == 1

    val even = (i: Int) => (i & 1) != 1

    val trues = (_ : Int) => true

    val falses = (_ : Int) => false

    val isPrime = (i : Int) => {
      if (i <= 1) false
      else if (i == 2) true
      else !(2 until i).exists(x => (i % x) == 0)
    }

    val mine = (i : Int) => odd(i) && isPrime(i)

    def add(i: Int) = (j: Int) => i + j

    def mult(i: Int) = (j: Int) => i * j
  }

  test("forall") {
    import TestFunctions._

    assert(forall(dirac(0), dirac(0)))
    assert(! (forall(dirac(1), dirac(0))))
    assert(! (forall(odd, dirac(0))))
    assert(forall(dirac(1), odd))
    assert(forall(mine, odd))
    assert(!forall(trues, falses))
    assert(forall(trues, trues))
    assert(forall(falses, falses))
    assert(forall(falses, trues))
  }

  test("exists") {
    import TestFunctions._

    assert(exists(dirac(0), dirac(0)))
    assert(! (exists(dirac(1), dirac(0))))
    assert(! (exists(odd, dirac(0))))
    assert(exists(dirac(1), odd))
    assert(exists(mine, odd))
    assert(!exists(trues, falses))
    assert(exists(trues, trues))
    assert(!exists(falses, falses))
    assert(!exists(falses, trues))
  }

  test("map") {
    import TestFunctions._

    assert(forall(map(dirac(0), add(1)), dirac(1)))

    assert(forall(map(dirac(0), mult(10)), dirac(0)))
    assert(forall(map(dirac(1), mult(10)), dirac(10)))

    val mult2 = map(trues, mult(2))
    assert(forall(mult2, even), printSet(mult2))
  }
}
