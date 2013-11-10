// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/chess

organization := "com.github.fommil"

name := "chess"

version := "1.0-SNAPSHOT"

scalaVersion := "2.10.2"

libraryDependencies ++= Seq(
  "com.github.fommil"      %  "java-logging" % "1.1",
  "com.google.guava"       %  "guava"        % "15.0",
  "com.typesafe.akka"      %% "akka-contrib" % "2.2.1" intransitive(),
  "com.typesafe.akka"      %% "akka-actor"   % "2.2.1",
  "org.specs2"             %% "specs2"       % "2.2.3" % "test"
)

// sbt semes to ignore these
javaOptions += "-XX:+UseConcMarkSweepGC -XX:+CMSIncrementalMode -Djava.util.logging.config.file=logging.properties"

mainClass in (Compile, run) := Some("com.github.fommil.chess.AkkaSolverApp")

fork := true
