// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/trafigura

organization := "com.github.fommil"

name := "trafigura"

version := "1.0-SNAPSHOT"

scalaVersion := "2.10.2"

libraryDependencies ++= Seq(
  "com.google.guava" % "guava" % "15.0",
  "org.specs2" %% "specs2" % "2.2.3" % "test"
)

javaOptions += "-Djava.awt.headless=true"

mainClass := Some("com.github.fommil.trafigura.Chess")

fork := true
