/*
  @JUDGE_ID: fommil 100 C

  my solution to "The 3n + 1 problem" found at
  http://online-judge.uva.es/p/v1/100.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned int
cyc (unsigned int n)
{
  unsigned int c = 1;

  while (1 != n) {
    c++;
    if (1 == (n % 2))
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

  while (2 == scanf ("%u %u\n", &i, &j)) {

    printf ("DEBUG: %u %u\n", i, j);
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
  }

  return 0;
}
