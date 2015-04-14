// mkdir -p src/{main,test}/{java,scala}/com/github/fommil

organization := "com.github.fommil"

name := "playground"

version := "1.0-SNAPSHOT"

scalaVersion := "2.11.6"

libraryDependencies ++= Seq(
  "com.github.stacycurl" %% "pimpathon-core" % "1.4.0",
  "io.spray"      %% "spray-json" % "1.3.1",
  "com.chuusai" %% "shapeless" % "2.2.0-RC4",
  "org.scalatest" %% "scalatest" % "2.2.1" % "test"
)
