// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/trafigura

organization := "com.github.fommil"

name := "trafigura"

version := "1.0-SNAPSHOT"

scalaVersion := "2.10.2"

libraryDependencies ++= Seq(
  "com.github.fommil"      %  "java-logging" % "1.1",
  "com.google.guava"       %  "guava"        % "15.0",
  "com.typesafe.akka"      %% "akka-contrib" % "2.2.1" intransitive(),
  "com.typesafe.akka"      %% "akka-actor"   % "2.2.1",
  "org.specs2"             %% "specs2"       % "2.2.3" % "test"
)

javaOptions += "-Djava.awt.headless=true -XX:MaxPermSize=128M -Xmx2G -XX:+UseConcMarkSweepGC -XX:+CMSIncrementalMode -Djava.util.logging.config.file=logging.properties"

mainClass := Some("com.github.fommil.trafigura.Chess")

fork := true
