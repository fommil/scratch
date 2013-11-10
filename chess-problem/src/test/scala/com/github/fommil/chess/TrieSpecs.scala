package com.github.fommil.chess

import TrieNode._

class TrieSpecs extends Specs {

  val hello = "hello".toList
  val hector = "hector".toList

  "single word trie" should {
    val trie = branch(hello)
    "have the correct starting branch" in {
      trie.children.keys.toList must beLike {
        case 'h' :: Nil => ok
      }
    }

    "contain a single entry" in {
      trie.contains(hello) must beTrue
    }

    "contain sub lists" in {
      trie.contains(hello take 2) must beTrue
    }

    "not contain other things" in {
      trie.contains(hector) must beFalse
    }

    "have 1 leaf" in {
      trie.size == 1
    }
  }

  "two word trie" should {
    val trie = branch(hello).add(hector)
    "contain both words" in {
      {trie.contains(hello) must beTrue} and
        {trie.contains(hector) must beTrue}
    }

    "have 2 leafs" in {
      trie.size == 2
    }

    "contain the prefix" in {
      trie.contains("hell".toList) must beTrue
    }
  }

  "adding" should {
    "work for two tries" in {
      branch(hello) ++ branch(hector) === branch(hello).add(hector)
    }
  }
}
