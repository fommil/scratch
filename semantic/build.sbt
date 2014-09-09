// mkdir -p src/{main,test}/{java,scala}/com/github/fommil/semantic

organization := "com.github.fommil"

name := "semantic"

version := "1.0-SNAPSHOT"

scalaVersion := "2.11.2"

libraryDependencies ++= Seq(
  "org.parboiled"         %% "parboiled-scala" % "1.1.6",
  "com.github.stacycurl"  %% "pimpathon-core"  % "1.0.0",
  "org.scalaj"            %% "scalaj-http"     % "0.3.16",
  "org.scalatest"         %% "scalatest"       % "2.2.1" % "test"
)

scalacOptions in Compile ++= Seq(
  "-encoding", "UTF-8", "-target:jvm-1.6", "-feature", "-deprecation",
  "-Xfatal-warnings",
  "-language:postfixOps", "-language:implicitConversions"
)

javacOptions in (Compile, compile) ++= Seq (
  "-source", "1.6", "-target", "1.6", "-Xlint:all", "-Werror",
  "-Xlint:-options", "-Xlint:-path", "-Xlint:-processing"
)
