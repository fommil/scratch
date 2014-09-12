This test is designed to show how you think, code and deal with new
technologies. Please spend no more than an hour or two on your
solution. Your code does not have to be perfect, think of it as a
prototype and still send us your code even if you cannot get the tests
to pass.

Please use Scala or Java and http://dbpedia.org  to make the following tests pass:

```
  test("How old is Tony Blair") {
    val answer = Question.ask("How old is Tony Blair?")
    assert("61" === answer)
  }
  test("What is the birth place of David Cameron") {
    val answer = Question.ask("What is the birth place of David Cameron?")
    assert("London, United Kingdom" === answer)
  }
```

Feel free to use any external libraries that you like but make sure
the solution will build when you send it back to us. You may find the
following links useful:

http://dbpedia.org/resource/Tony_Blair
http://dbpedia.org/resource/David_Cameron 
http://dbpedia.org/sparql  (to query the date of birth, birth place etc)
http://wiki.dbpedia.org/lookup/  (to help disambiguate the resource that you are interested in)

Good luck
 
