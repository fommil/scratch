package patmat

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

import patmat.Huffman._
import patmat.Huffman.Leaf
import patmat.Huffman.Fork

@RunWith(classOf[JUnitRunner])
class HuffmanSuite extends FunSuite {

  trait TestTrees {
    val t1 = Fork(Leaf('a', 2), Leaf('b', 3), List('a', 'b'), 5)
    val t2 = Fork(Fork(Leaf('a', 2), Leaf('b', 3), List('a', 'b'), 5), Leaf('d', 4), List('a', 'b', 'd'), 9)
  }

  test("weight of a larger tree") {
    new TestTrees {
      assert(weight(t1) === 5)
    }
  }

  test("chars of a larger tree") {
    new TestTrees {
      assert(chars(t2) === List('a', 'b', 'd'))
    }
  }

  test("string2chars(\"hello, world\")") {
    assert(string2Chars("hello, world") === List('h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'))
  }

  test("makeOrderedLeafList for some frequency table") {
    assert(makeOrderedLeafList(List(('t', 2), ('e', 1), ('x', 3))) === List(Leaf('e', 1), Leaf('t', 2), Leaf('x', 3)))
  }

  test("combine of some leaf list") {
    val leaflist = List(Leaf('e', 1), Leaf('t', 2), Leaf('x', 4))
    assert(combine(leaflist) === List(Fork(Leaf('e', 1), Leaf('t', 2), List('e', 't'), 3), Leaf('x', 4)))
  }

  test("decode a very short text") {
    new TestTrees {
      assert(decode(t1, List(0, 1)) === "ab".toList)
    }
  }

  test("encode a very short text") {
    new TestTrees {
      assert(encode(t1)("ab".toList) === List(0, 1))
    }
  }

  test("decode and encode a very short text should be identity") {
    new TestTrees {
      assert(decode(t1, encode(t1)("ab".toList)) === "ab".toList)
    }
  }

  test("the secret") {
    assert(decodedSecret === string2Chars("huffmanestcool"))
  }

  test("building a CodeTable") {
    new TestTrees {
      assert(convert(t1) === List(('a', List(0)), ('b', List(1))))
      assert(convert(t2) === List(('a', List(0, 0)), ('b', List(0, 1)), ('d', List(1))))
    }
  }

  test("quickEncode") {
    assert(quickEncode(frenchCode)(string2Chars("huffmanestcool")) === secret)
  }

  test("createCodeTree on Assignment example") {
    // the example in the assignment, note that left/rights is the wrong way round in their diagram
    val tree = createCodeTree(("a" * 8 + "b" * 3 + "cdefgh").toList)

    assert(decode(tree, 0 :: Nil) == 'a' :: Nil)
  }

  test("createCodeTree using Wikipedia example") {
    val text = """this is an example of a huffman tree"""
    // http://en.wikipedia.org/wiki/Huffman_coding
    println(makeOrderedLeafList(times(string2Chars(text))).reverse)

    val tree = createCodeTree(string2Chars(text))
    printCodeTree(tree)

    assert(decode(tree, 1 :: 1 :: 1 :: Nil) == ' ' :: Nil)
    assert(decode(tree, 0 :: 0 :: 0 :: Nil) == 'e' :: Nil)
//    assert(decode(tree, 1 :: 0 :: 0 :: 1 :: 0 :: Nil) == 'x' :: Nil)
  }

  def printCodeTree(tree: CodeTree) {
    def printCodeTree(tree: CodeTree, prepend: String): List[String] = {
      tree match {
        case leaf: Leaf => List(prepend + "(" + leaf.char + "," + leaf.weight + ")")
        case fork: Fork => printCodeTree(fork.left, prepend + "/") ::: printCodeTree(fork.right, prepend + "\\")
      }
    }
    println(printCodeTree(tree, "").reverse.foldLeft("")(_ + "\n" + _))
  }

}
