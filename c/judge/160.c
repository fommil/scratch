/*
  @JUDGE_ID: 48343FK 160 C

  my solution to the "Factors and Factorials" found at
  http://acm.uva.es/p/v1/160.html

*/

#include <stdio.h>
#include <stdlib.h>

#define PRIMES 25
signed int primes[PRIMES] = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
  31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
  73, 79, 83, 89, 97
};

/* most inefficient factorising algorithm... ever! */
void
ifactor (signed int i, signed int factors[])
{
  signed int n;

  /* start with max prime and work down the list... */
  for (n = PRIMES-1; (0 <= n) && (1 != i); ) {
    if (0 == i % primes[n]) {
      factors[n]++;
      i = i / primes[n];
    }
    if (0 != i % primes[n])
      n--;
  }
}

int
main ()
{
  signed int i, ii, factors[PRIMES];

  while (1) {
    /* reset the factors array */
    for (ii = 0; ii < PRIMES; ii++)
      factors[ii] = 0;

    /* scan in a new integer */
    scanf ("%d\n", &i);
    if ((i < 2) || (100 < i))
      return 0;

    printf ("%3u! =", i);

    /* factor i, then i-1, i-2, ..., 2 */
    for (ii = i; ii > 1; ii--)
      ifactor (ii, factors);

    /* print out the answer */
    for (ii = 0; (ii < PRIMES) && (primes[ii] <= i); ii++) {
      if ((0 != ii) && (0 == ii % 15))
	printf ("\n      ");
      printf ("%3u", factors[ii]);
    }
    printf ("\n");
  }
}
