/*
  @JUDGE_ID: fommil 100 C

  my solution to "The 3n + 1 problem" found at
  http://online-judge.uva.es/p/v1/100.html

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
isodd (unsigned int i)
{
  /* also check a bitshift */
  /* return div (i, 2).rem; */
  return -(i << (sizeof (unsigned int) * 8 - 1));
}

unsigned int
cyc (unsigned int n)
{
  unsigned int c = 1;

  while (1 != n) {
    c++;
    if (isodd (n))
      n = 3 * n + 1;
    else
      n = n / 2;
  }
  return c;
}

int
main ()
{
  unsigned int i, j, n, m, t;
  char eof = '1';

  while (isdigit (eof)) {
    scanf ("%u %u\n", &i, &j);

    if (i < j) {
      for (n = i, m = 0; n <= j; n++) {
	t = cyc (n);
	if (m < t)
	  m = t;
      }
    }
    else {
      for (n = j, m = 0; n <= i; n++) {
	t = cyc (n);
	if (m < t)
	  m = t;
      }
    }

    printf ("%u %u %u\n", i, j, m);
    eof = getc (stdin);
    ungetc (eof, stdin);
  }

  return 0;
}
