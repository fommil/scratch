/*
 * @JUDGE_ID: fommil 126 C
 * 
 * my solution to the "Errant Physicist" found at
 * http://acm.uva.es/p/v1/126.html
 * 
 * time: 0:00.033 mem: 64
 * 
 * my code was not as fast as it could have been. i suspect this is due to 
 * my crap parser.
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

void *
partialstring (char str[], unsigned int start, unsigned int end)
{
  char *partial;

  if (end < start) {
    printf ("Error: partialstring() called with end < start\n");
    exit (EXIT_FAILURE);
  }

  partial = malloc (end - start + 1);
  partial[end - start + 1] = 0;

  memcpy (partial, str + start, end - start + 1);

  return partial;
}

void
readterm (signed int poly[201][201], char str[])
{
  signed int coeff, fred, n, xp = -1, yp = -1;
  unsigned int x, y;
  char *strtemp;

  fred = strlen (str);

  for (n = 0; n < fred; n++) {
    if ('x' == str[n])
      xp = n;
    else if ('y' == str[n])
      yp = n;
  }

  /*
   * there is a lot of repeated code in here 
   */

  /*
   * no x or y terms 
   */
  if ((-1 == xp) && (-1 == yp)) {
    x = 0;
    y = 0;
    coeff = atoi (str);
  }

  /*
   * x, but no y terms 
   */
  else if ((-1 == yp)) {
    y = 0;
    if (fred - 1 != xp) {
      strtemp = partialstring (str, xp + 1, fred - 1);
      x = atoi (strtemp);
      free (strtemp);
    }
    else
      x = 1;
    if (0 == xp)
      coeff = 1;
    else if ((1 == xp) && ('-' == str[0]))
      coeff = -1;
    else {
      strtemp = partialstring (str, 0, xp);
      coeff = atoi (strtemp);
      free (strtemp);
    }
  }

  /*
   * y, but no x terms 
   */
  else if ((-1 == xp)) {
    x = 0;
    if (fred - 1 != yp) {
      strtemp = partialstring (str, yp + 1, fred - 1);
      y = atoi (strtemp);
      free (strtemp);
    }
    else
      y = 1;
    if (0 == yp)
      coeff = 1;
    else if ((1 == yp) && ('-' == str[0]))
      coeff = -1;
    else {
      strtemp = partialstring (str, 0, yp);
      coeff = atoi (strtemp);
      free (strtemp);
    }
  }

  /*
   * both x and y terms 
   */
  /*
   * x listed before y 
   */
  else if (xp < yp) {
    if (fred - 1 != yp) {
      strtemp = partialstring (str, yp + 1, fred - 1);
      y = atoi (strtemp);
      free (strtemp);
    }
    else
      y = 1;
    if (xp + 1 == yp)
      x = 1;
    else {
      strtemp = partialstring (str, xp + 1, yp - 1);
      x = atoi (strtemp);
      free (strtemp);
    }
    if (0 == xp)
      coeff = 1;
    else if ((1 == xp) && ('-' == str[0]))
      coeff = -1;
    else {
      strtemp = partialstring (str, 0, xp);
      coeff = atoi (strtemp);
      free (strtemp);
    }
  }
  /*
   * y listed before x 
   */
  else {
    if (fred - 1 != xp) {
      strtemp = partialstring (str, xp + 1, fred - 1);
      x = atoi (strtemp);
      free (strtemp);
    }
    else
      x = 1;
    if (yp + 1 == xp)
      y = 1;
    else {
      strtemp = partialstring (str, yp + 1, xp - 1);
      y = atoi (strtemp);
      free (strtemp);
    }
    if (0 == yp)
      coeff = 1;
    else if ((1 == yp) && ('-' == str[0]))
      coeff = -1;
    else {
      strtemp = partialstring (str, 0, yp);
      coeff = atoi (strtemp);
      free (strtemp);
    }
  }

  poly[x][y] = poly[x][y] + coeff;
}

void
readpoly (signed int poly[201][201])
{
  signed int n, start, end, fred;
  char temp, buf[80];
  char *strtemp;

  /*
   * read the input line into buf 
   */
  for (n = 0, temp = 1; (n < 80) && ('\n' != temp); n++) {
    temp = fgetc (stdin);
    if ('\n' == temp)
      buf[n] = 0;
    else
      buf[n] = temp;
  }

  fred = strlen (buf);
  /*
   * parse the buffer and load each term one by one 
   */
  for (start = 0, n = 0, end = -1; n <= fred; n++) {
    if ((('+' == buf[n]) || ('-' == buf[n]) || (0 == buf[n]))
	&& (0 != n)) {
      if ((0 == n) || (1 == n))
	end = n;
      else
	end = n - 1;
    }
    if ('+' == buf[start])
      start++;
    if (-1 != end) {
      strtemp = partialstring (buf, start, end);
      start = end + 1;
      end = -1;
      readterm (poly, strtemp);
      free (strtemp);
    }
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
