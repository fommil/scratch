#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void
printfactors (int *array, unsigned int arraysize, unsigned int element)
{
  unsigned int n;

#ifndef NOTMAPLE
  if ((unsigned int) NULL == element)
    {
#endif
      printf ("{");
      for (n = 0; n < arraysize - 1; n++)
	printf ("%d, ", array[n]);
      printf ("%d}\n", array[n]);
#ifndef NOTMAPLE
    }
  else
    {
      for (n = 0; n < arraysize; n++)
	printf ("h[%u,%u]:=%d: ", element, n + 1, array[n]);
      printf ("\n");
    }
#endif
}

int
checkfactors (int *array, unsigned int arraysize, unsigned int number)
{
  int n, tmp = 0;

  for (n = 0; n < arraysize; n++)
    {
      tmp = tmp + array[n];
    }

#ifdef DEBUG
  printf ("DEBUG: %d %d\n", tmp, number);
#endif

  if (number == tmp)
    return 1;
  if (number < tmp)
    return 2;
  return 0;
}

int
incrementdigit (int *array, unsigned int arraysize, unsigned int element,
		unsigned int max)
{
  // Exit if we are reading beyond the buffer
  if (element == arraysize)
    return 1;

  // Increment the element
  array[element]++;

  // If we overflowed past "max" then reset the element to 1
  // and recursively call increment to the next element
  if ((max + 1) == array[element])
    {
      array[element] = 1;
      incrementdigit (array, arraysize, element + 1, max);
    }

  return 0;
}

int
incrementall (unsigned int Q, unsigned int M)
{
  // Q = number of elements
  // M = number to factor
  int l[Q];
  unsigned int n, i, perts, j = 0;
  unsigned int max, tmp;
#ifdef OPT
  unsigned int k = 0;
#endif

  // Find the maximum value each element should be
  max = M - Q + 1;

  // Find the number of pertubations
  perts = (unsigned int) pow ((double) max, (double) Q) - 1;

#ifdef DEBUG
  printf ("DEBUG: max = %u, Q = %u, perts = %lu \n", max, Q, perts);
#endif

  // TODO: put in an integer-overflow check here for `perts'

  for (n = 0; n < Q; n++)
    l[n] = 1;

  // Print the initial values if they are factors
  tmp = checkfactors (l, Q, M);
  if (1 == tmp)
    {
      j++;
      printfactors (l, Q, j);
    }
#ifdef DEBUG
  else
    {
      printf ("DEBUG: 1 ");
      printfactors (l, Q, NULL);
    }
#endif

  for (i = 0; i < perts; i++)
    {
      // Increment
      if (0 != incrementdigit (l, Q, 0, max))
	printf ("Failed incrementdigit(l,%u,0,%u)\n", Q, max);
      // Print the array
      tmp = checkfactors (l, Q, M);
      if (1 == tmp)
	{
	  j++;
	  printfactors (l, Q, j);
	}
#ifdef TESTOPT
      if (2 == tmp)
	{
	  printf ("OPT: WILL REMOVE ");
	  printfactors (l, Q, NULL);
	}
#endif
#ifdef OPT
#warning Building with optimisations which are not fully working yet
      if (2 == tmp)
	{
	  /*

	     PUT THE OPTIMISED CODE IN HERE

	     This code is only accessed if the current
	     elements add to a value greater than M.

	     Essentially set the current element to 1,
	     and run increment on the next element;
	     but remember to increment `i' accordingly.

	   */
#ifdef DEBUG
	  printf ("OPT: SKIPPING FROM ");
	  printfactors (l, Q, NULL);
#endif

	  // we need a check to see if (1==l[0]) and then find
	  // which element to increment
	  i = i + (max - l[0]) + 1;
	  l[0] = 1;
	  if (max > k + 1)
	    incrementdigit (l, Q, k + 1, max);
	  /* BROKEN CODE
	     for (k = 0; k < max; k++)
	     {
	     if (2 == checkfactors (l, Q, M))
	     {
	     incrementdigit (l, Q, k + 1, max);
	     l[k] = 1;
	     i = i + max - l[k] + 1;

	     //printf ("TODO: Please increment `i' accordingly\n");
	     //                  printf ("OPT: SHOULD SKIP   ");
	     //                  printfactors (l, Q,NULL);
	     }
	     }
	   */

#ifdef DEBUG
	  printf ("OPT: SKIPPED TO    ");
	  printfactors (l, Q, NULL);
#endif
	}
#endif
#ifdef DEBUG
      else
	{
	  printf ("DEBUG: %lu ", i);
	  printfactors (l, Q, NULL);
	}
#endif
    }

  printf ("%u\n", j);

  return 0;
}

int
main (int argc, char *argv[])
{
  int factors, number;

#ifdef DEBUG
  printf ("DEBUG: int %d, int %d, int int %d, argc = %d\n",
	  (int) (8 * sizeof (int)),
	  (int) (8 * sizeof (int)), (int) (8 * sizeof (int)), argc);
#endif

  if (3 != argc)
    {
      printf
	("Usage: %s [factors] [number]\nFind the addition factors of number.\n",
	 argv[0]);
      return 1;
    }

  // TODO: Check that argv[1,2] are actually integers

  factors = atoi (argv[1]);
  number = atoi (argv[2]);

  if (factors > number)
    return 1;

  incrementall (factors, number);
  return 0;
}
