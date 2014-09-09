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
 * I choose to interpret the problem to be limited to asking for the
 * age and birth dates of public figures using the exact syntax
 * described in the specification (tests).
 *
 * This challenge could be extended to include a much larger domain of
 * questions about public figures, places and locations, as well as
 * handling a much larger variety of ways to ask the questions. I have
 * chosen to prefer code cleanliness and possibility of extension over
 * feature implementation.
 *
 * 
 * Of most relevance to this particular challenge, it is worth noting
 * that I have previously worked on:
 *
 * 1. entity identification and disabiguation for the BBC News team.
 * 2. natural language processing and the prediction of intent from
 *    free-form text with Morgan Stanley's Securitized Products Group.
 *
 * and strongly related projects for the UK Ministry of Defence. In
 * all these projects, advanced in-house techniques were developed to
 * address specific challenges, complemented by open technologies when
 * appropriate.
 *
 * 
 * It is worth noting that, in my experience, human communication
 * cannot be specified by a parser such as the toy one described here,
 * and that I would not wish to rely on an external service such as
 * DBPedia without a rigorous service agreement in place.
 */
object Question {
  def ask(question: String): String = ???
}
