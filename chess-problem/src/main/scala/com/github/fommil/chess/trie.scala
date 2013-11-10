package com.github.fommil.chess

import TrieNode._

case class TrieNode[T](children: Map[T, TrieNode[T]]) {

  def +(element: List[T]): TrieNode[T] = add(element)

  def ++(other: TrieNode[T]): TrieNode[T] = add(other)

  //  def +(el: T) = add(el :: Nil)
  //
  //  def +(k: T, branch: TrieNode[T]) = add(k, branch)

  def add(other: TrieNode[T]): TrieNode[T] = {
    val common = children.keySet.intersect(other.children.keySet)
    val mine = children -- common
    val theirs = other.children -- common
    val merged = common.map { k =>
      (k, children(k).add(other.children(k)))
    }.toMap
    TrieNode(mine ++ theirs ++ merged)
  }

  def add(element: List[T]): TrieNode[T] = element match {
    case Nil => this
    case head :: Nil if children.contains(head) => this
    case head :: Nil =>
      TrieNode(children + (head -> leaf))
    case head :: tail if children.contains(head) =>
      TrieNode(children + (head -> children(head).add(tail)))
    case head :: tail =>
      TrieNode(children + (head -> branch(tail)))
  }

  //  def add(k: T, branch: TrieNode[T]) = this ++ TrieNode(Map(k -> branch))

  def contains(element: List[T]): Boolean = element match {
    case Nil => false
    case head :: Nil => children.contains(head)
    case head :: tail if children.contains(head) => children(head).contains(tail)
    case other => false
  }

  private def leaves: Int =
    if (children.size == 0) 1
    else children.values.map { _.leaves }.reduce { _ + _ }

  def size = if (children.size == 0) 0 else leaves

  override def toString() = toString(0)

  private def toString(i: Int): String =
    children.keys.map { k =>
      "    " * i + s"$k\n${children(k).toString(i + 1)}"
    }.mkString("")

  // TODO: implement Iterable
}

object TrieNode {
  def leaf[T]: TrieNode[T] = apply(Map[T, TrieNode[T]]())

  def branch[T](element: List[T]): TrieNode[T] = element match {
    case Nil => leaf
    case head :: tail => TrieNode(Map(head -> branch(tail)))
  }
}