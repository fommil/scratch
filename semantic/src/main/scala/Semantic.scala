package com.github.fommil.semantic

import java.util.Date
import java.util.concurrent.TimeUnit._
import javax.xml.bind.DatatypeConverter

import scala.xml._

/*
libraryDependencies ++= Seq(
  "org.parboiled"         %% "parboiled-scala" % "1.1.6",
  "com.github.stacycurl"  %% "pimpathon-core"  % "1.0.0",
  "org.scalaj"            %% "scalaj-http"     % "0.3.16",
  "org.scalatest"         %% "scalatest"       % "2.2.1" % "test"
)
*/
import org.parboiled.scala._
import scalaj.http._
import pimpathon.option._

/**
 * The challenge is to implement a very simple information retrieval
 * system that can understand a very limited range of questions about
 * public figures.
 *
 * It combines the areas of:
 *
 * 1. Natural language processing
 * 2. Entity identification and disambiguation
 * 3. REST / JSON data parsing
 *
 * and advises the use of dbpedia.
 *
 * This challenge could be interpreted to include a much larger domain
 * of questions. I choose to interpret the challenge as being limited
 * to the age and birth location of public figures using the exact
 * syntax described in the specification (tests). I also choose to
 * code for extension rather than to be terse or implement unrequested
 * features.
 *
 * I have tried to answer in one file to simplify the logistics. I have
 * created some additional ScalaTest specs, which you may or may not
 * receive depending on how this file is delivered.
 *
 * It is worth noting that I have previously worked on:
 *
 * 1. entity identification and disabiguation for the BBC News team.
 * 2. natural language processing and the prediction of intent from
 *    free-form text with Morgan Stanley's Securitized Products Group.
 * 3. statistical inference of gender based on SMS content for the
 *    Texperts (now KGB / 118 118).
 *
 * and related projects for the UK Ministry of Defence. In all
 * projects, I developed advanced in-house techniques to address
 * specific challenges, complemented by open technologies when
 * appropriate.
 *
 * I had not used SPARQL (or scalaj) before this exercise. I felt that
 * the most important part of this challenge was to understand the
 * SPARQL query syntax to be able to issue nested queries.
 */
object Question {
  import scala.language.existentials
  def ask(question: String): String = {
    // understand the question and construct a plan
    val (guru, DbpEntity(entity)) = QuestionParser.parse(question).getOrThrow(
      "Any fool can know. The point is to understand " + question
    )
    // deliver on the plan
    guru.ask(entity).getOrThrow(
      "A wise man can learn more from a foolish question (like " + question +
        ") than a fool can learn from a wise answer."
    )
  }
}

/**
 * A Guru may answer specific questions about an entity, returning
 * their answer in plain English.
 */
trait Guru[T <: Answer] {
  def ask(entity: Entity): Option[String] = askT(entity).map(_.render)
  // for composites
  def askT(entity: Entity): Option[T]
}
case class Entity(uri: String)
trait Answer {
  def render: String
}

/**
 * Represents a SPARQL query on DBPedia for a single resource.
 *
 * `T` is type that the response should be marshalled into.
 *
 * I would not wish to rely on an external service such as DBPedia
 * without a rigorous service level and data quality agreement in
 * place. It went down while I was writing this, and it lacks basic
 * information such as Edinburgh's country (Tony Blair's birthplace):
 * or perhaps dbpedia knows more about the Scottish referendum on
 * independence than we do?
 */
trait DbpSparqlQuery[T <: Answer] extends Guru[T] {
  protected def query(entity: Entity): String
  protected def extract(cols: Seq[String]): T

  private val EndPoint = Http("http://dbpedia.org/sparql").
    param("format", "application/sparql-results+xml")

  def askT(entity: Entity): Option[T] = {
    val response = EndPoint.param("query", query(entity)).asXml
    (response \\ "sparql" \\ "results" \\ "result").headOption.
      map { first =>
        extract((first \\ "binding" \\ "literal").map(_.text))
      }
  }
}

case class DateOfBirth(timestamp: Long) extends Answer {
  def render = new Date(timestamp).toString
}
object DateOfBirthQuery extends DbpSparqlQuery[DateOfBirth] {
  def query(res: Entity) = s"""
PREFIX dbpedia-owl: <http://dbpedia.org/ontology/>
PREFIX foaf: <http://xmlns.com/foaf/0.1/>
SELECT ?dob WHERE { 
  <${res.uri}> dbpedia-owl:birthDate ?dob.
}
LIMIT 1"""

  def extract(cols: Seq[String]) = {
    val dt = DatatypeConverter.parseDateTime(cols(0))
    DateOfBirth(dt.getTimeInMillis())
  }
}

case class BirthPlace(city: String, country: String) extends Answer {
  // NOTE: spec calls for trailing "the " to be dropped from country
  def render = s"""$city, ${country.replace("the ", "")}"""
}
object BirthPlaceQuery extends DbpSparqlQuery[BirthPlace] {
  def query(res: Entity) = s"""
PREFIX dbpedia-owl: <http://dbpedia.org/ontology/>
PREFIX foaf: <http://xmlns.com/foaf/0.1/>
SELECT ?cityName ?countryName WHERE { 
  <${res.uri}> dbpedia-owl:birthPlace ?city.
  ?city foaf:name ?cityName.
  ?city dbpedia-owl:country ?country.
  ?country foaf:name ?countryName.
}
LIMIT 1"""

  def extract(cols: Seq[String]) = BirthPlace(cols(0), cols(1))
}

case class Age(years: Int) extends Answer {
  def render = years.toString
}
object AgeQuery extends Guru[Age] {
  def askT(e: Entity): Option[Age] =
    DateOfBirthQuery.askT(e).map {
      case DateOfBirth(ts) =>
        // this will give the wrong answer for dead people
        val diff = System.currentTimeMillis - ts
        val days = DAYS.convert(diff, MILLISECONDS)
        Age((days / 365).toInt)
    }
}

// for the ease of testing, I'd prefer to have a Resolver trait, which
// can be mocked without network access, but that would be far too
// cumbersome for this exercise. Instead I've gone for a clean syntax
// in the Question object.
object DbpEntity {
  private val Lookup =
    Http("http://lookup.dbpedia.org/api/search.asmx/KeywordSearch").
      param("QueryClass", "Person")

  def unapply(entity: String): Option[Entity] = {
    // this XML processing is not as performant as SAX parsers like
    // Jackson, or raw Java XPath, but it's a one liner
    val response = Lookup.param("QueryString", entity).asXml
    (response \\ "ArrayOfResult" \\ "Result" \ "URI").headOption.map {
      uri => Entity(uri.text)
    }
  }
}

/* I have not used a remote entity disambiguation service such as
 * [YAGO NAGA](https://github.com/yago-naga/aida)
 * simply because I don't feel that you would learn anything from seeing
 * me contact yet another REST API endpoint.
 * 
 * Instead, you might be interested to see the parboiled parser
 * syntax. In my experience human communication cannot be specified by
 * a parser such as the toy one described here, but that's not really
 * the point of this exercise.
 */
object QuestionParser extends Parser {
  // ugly signature
  /** returns a guru and a string representation of the entity */
  def parse(question: String): Option[(Guru[_ <: Answer], String)] =
    ReportingParseRunner(GuruSubject).run(question).result

  // effectively ignore whitespace and simplify the syntax
  implicit def strToRule(string: String): Rule0 =
    WhiteSpace ~ ignoreCase(string) ~ WhiteSpace
  private def WhiteSpace = rule { zeroOrMore(anyOf(" \n\r\t\f")) }
  override val buildParseTree = true

  private def GuruSubject: Rule1[(Guru[_ <: Answer], String)] = rule {
    StopWords ~ (GuruOfAges | GuruOfPlaces) ~ StopWords ~ Subject ~ StopWords ~ "?"
  } ~~> { (g, s) => (g, s) }

  private def StopWords: Rule0 = rule {
    zeroOrMore("what" | "how" | "where" | "is" | "the" | "of" | "for" | "would" | "be")
  }

  private def GuruOfAges: Rule1[Guru[Age]] = rule {
    ("age" | "old")
  } ~> { _ => AgeQuery }

  private def GuruOfPlaces: Rule1[Guru[BirthPlace]] = rule {
    ("birth place" | ("place" ~ StopWords ~ "birth"))
  } ~> { _ => BirthPlaceQuery }

  private def Subject: Rule1[String] = rule {
    oneOrMore(noneOf("?")) ~> (_.toString.trim)
  }
}
