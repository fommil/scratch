/*
 * @JUDGE_ID: fommil 126 C
 * 
 * my solution to the "Errant Physicist" found at
 * http://acm.uva.es/p/v1/126.html
 *
 * i intend to beat:
 *  time: 0:00.033 mem: 64
 * by rewriting the parser, but i got 
 *  time: 0:00.035 mem: 64
 *
 * unfortunately i solved this in the most obvious way; i created a 2D
 * array of ints, the 1st index denoting X and the 2nd Y. the actual value 
 * is then the coefficient; so poly[3][2]=2 would mean 2x^3y^2. i then
 * created 3 main functions to deal with this object; a parser to convert
 * stdin into such an array, a multiplication function, and a print
 * function.
 * 
 * the smarter solution would have been to create a linked list of
 * polynomial terms... which would mean no redundant memory usage.
 * 
 * also, im sure a parser could be written which works in a single sweep,
 * reading from stdin, instead of the monstrosity i wrote. my print
 * function also leaves a lot to be desired. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readpoly (signed int poly[201][201]);
void printpoly (signed int poly[201][201]);
void multpoly (signed int out[201][201], signed int p1[201][201],
	       signed int p2[201][201]);

int
main ()
{
  signed int inPolyLeft[201][201], inPolyRight[201][201], outPoly[201][201];
  signed int x, y, eof;

  eof = getc (stdin);
  ungetc (eof, stdin);

  while ('#' != eof) {
    for (x = 200; x >= 0; x--)
      for (y = 0; y < 201; y++) {
	inPolyLeft[x][y] = 0;
	inPolyRight[x][y] = 0;
	outPoly[x][y] = 0;
      }

    readpoly (inPolyLeft);
    readpoly (inPolyRight);

    multpoly (outPoly, inPolyLeft, inPolyRight);
    printpoly (outPoly);

    eof = getc (stdin);
    ungetc (eof, stdin);
  }
  return 0;
}

unsigned char
readexp (unsigned char c, signed int *x, signed int *y)
{
  unsigned char c2;

  c2 = getc (stdin);
  if (0 != isdigit (c2)) {
    ungetc (c2, stdin);
    /* next value is an exponent */
    if ('x' == c)
      scanf ("%d", &(*x));
    else
      scanf ("%d", &(*y));
    /* read the next byte */
    c2 = getc (stdin);
    if ('-' == c2)
      ungetc (c2, stdin);
  }
  else {
    /* exponent is 1 */
    if ('x' == c)
      *x = 1;
    else
      *y = 1;
  }
  return c2;
}

void
readpoly (signed int poly[201][201])
{
  signed int n, v, x, y;
  unsigned char c, d, eol;

  for (n = 0, d = 0, eol = 0; (n < 80) && (1 != eol); n++) {
    c = getc (stdin);
    if (('+' != c) && ('\n' != c)) {
      /* read the coefficient */
      if (!(('x' == c) || ('y' == c))) {
	if ('-' == c) {
	  /* coefficient is negative. hack since scanf cannot handle a lone - */
	  c = getc (stdin);
	  ungetc (c, stdin);
	  if (0 != isdigit (c)) {
	    scanf ("%d", &v);
	    v = 0 - v;
	  }
	  else
	    v = -1;
	}
	else {
	  ungetc (c, stdin);
	  scanf ("%d", &v);
	}
	c = getc (stdin);
      }
      else
	v = 1;

      /* now it is either the end of the term or it is x/y term */
      if (('x' == c) || ('y' == c)) {
	/* read the first exponent */
	d = readexp (c, &x, &y);
	if (('x' == d) || ('y' == d)) {
	  /* read the second exponent */
	  d = readexp (d, &x, &y);
	}
	else {
	  /* there is no 2nd exponent... it must have coeff zero */
	  if ('x' == c)
	    y = 0;
	  else
	    x = 0;
	}
      }
      else {
	/* must not have coefficients */
	if ('-' == c)
	  ungetc (c, stdin);
	x = 0;
	y = 0;
      }

      /* x, y and v should all be set */
      poly[x][y] = poly[x][y] + v;
    }

    /* determine if it is an EOL */
    if (('\n' == c) || ('\n' == d))
      eol = 1;
  }
}

void
printspaces (unsigned int spaces)
{
  unsigned int n;

  if (0 != spaces)
    for (n = 0; n < spaces; n++)
      printf (" ");
}

void
printpoly (signed int poly[201][201])
{
  signed int e, x, y, term;
  char tempstr[80];

  for (e = 0; e < 2; e++) {
    term = 0;
    for (x = 200; x >= 0; x--) {
      for (y = 0; y < 201; y++) {
	if (0 != poly[x][y]) {
	  term++;
	  if (1 != term) {
	    if (0 < poly[x][y]) {
	      if (0 == e)
		printf ("   ");
	      else
		printf (" + ");
	    }
	    else {
	      if (0 == e)
		printf ("   ");
	      else
		printf (" - ");
	    }
	  }
	  else {
	    if (poly[x][y] < 0) {
	      if (0 == e)
		printf (" ");
	      else
		printf ("-");
	    }
	  }
	  if ((1 != abs (poly[x][y])) || ((0 == x) && (0 == y))) {
	    if (0 == e) {
	      sprintf (tempstr, "%d", abs (poly[x][y]));
	      printspaces (strlen (tempstr));
	    }
	    else
	      printf ("%d", abs (poly[x][y]));
	  }
	  if (0 != x) {
	    if (0 == e)
	      printf (" ");
	    else
	      printf ("x");
	    if (1 != x) {
	      if (0 == e)
		printf ("%d", x);
	      else {
		sprintf (tempstr, "%d", x);
		printspaces (strlen (tempstr));
	      }
	    }
	  }
	  if (0 != y) {
	    if (0 == e)
	      printf (" ");
	    else
	      printf ("y");
	    if (1 != y) {
	      if (0 == e)
		printf ("%d", y);
	      else {
		sprintf (tempstr, "%d", y);
		printspaces (strlen (tempstr));
	      }
	    }
	  }
	}
      }
    }
    printf ("\n");
  }
}

void
multpoly (signed int out[201][201], signed int p1[201][201],
	  signed int p2[201][201])
{
  signed int x1, x2, y1, y2;

  for (x1 = 0; x1 < 201; x1++) {
    for (y1 = 0; y1 < 201; y1++) {
      if (0 != p1[x1][y1]) {
	for (x2 = 0; x2 < 201; x2++) {
	  for (y2 = 0; y2 < 201; y2++) {
	    if (0 != p2[x2][y2]) {
	      out[x1 + x2][y1 + y2] =
		out[x1 + x2][y1 + y2] + p1[x1][y1] * p2[x2][y2];
	    }
	  }
	}
      }
    }
  }
}
