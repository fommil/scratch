// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/codility

organization := "com.github.fommil.codility"

name := "long"

version := "1.0-SNAPSHOT"

scalaVersion := "2.10.4"

libraryDependencies ++= Seq(
  "org.scalatest" %% "scalatest" % "2.2.1" % "test"
)
