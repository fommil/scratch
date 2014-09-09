// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/semantic

organization := "com.github.fommil"

name := "semantic"

version := "1.0-SNAPSHOT"

scalaVersion := "2.11.2"

libraryDependencies ++= Seq(
  "org.scalatest" %% "scalatest" % "2.2.1" % "test"
)
