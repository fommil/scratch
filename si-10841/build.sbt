inThisBuild(
  Seq(
    scalaVersion := "2.12.4"
  )
)

libraryDependencies ++= Seq(
  "eu.timepit" %% "refined" % "0.8.7",
  "org.scalaz" %% "scalaz-core" % "7.2.21",
  "com.codecommit" %% "shims" % "1.2",
  "com.github.mpilquist" %% "simulacrum" % "0.12.0",
  "com.fommil" %% "deriving-macro" % "0.13.0",
  "org.typelevel" %% "cats-core" % "1.1.0",
  "org.typelevel" %% "kittens" % "1.0.0-RC3",
  "org.typelevel" %% "mouse" % "0.16",
  "com.chuusai" %% "shapeless" % "2.3.3",
  "org.typelevel" %% "cats-effect" % "0.10",
  "org.scalatest" %% "scalatest" % "3.0.5" % "test",
  "org.ensime" %% "pcplod" % "1.2.1" % "test"
)

unmanagedResources in Test += (scalaSource in Compile).value

scalacOptions ++= List(
  // cleared by a jury...
  "-Yrangepos", "-encoding", "UTF-8", "-feature", "-deprecation", "-unchecked", "-language:implicitConversions", "-Xlint", "-Yno-adapted-args", "-Ywarn-dead-code", "-Xfuture", "-Ywarn-unused:patvars,imports,privates,locals", "-Ypartial-unification", "-language:higherKinds"
)

// cleared by a jury...
addCompilerPlugin("org.spire-math" %% "kind-projector" % "0.9.6")
addCompilerPlugin(
  ("org.scalamacros" % "paradise" % "2.1.1").cross(CrossVersion.full)
)
addCompilerPlugin("com.fommil" %% "deriving-plugin" % "0.13.0")
