#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
  // M = maximum number each element can take
  int l[Q];
  unsigned long n, i, perts;

  // Find the number of pertubations
  perts = (unsigned long) pow ((double) M, (double) Q) - 1;
  //  printf("DEBUGGING: %u, %u, %lu \n",M,Q,perts);
  // TODO: put in an integer-overflow check here for perts

  for (n = 0; n < Q; n++)
    l[n] = 1;

  // Print the initial values
  printf ("{");
  for (n = 0; n < Q - 1; n++)
    printf ("%d, ", l[n]);
  printf ("%d}\n", l[n]);

  for (i = 0; i < perts; i++)
    {
      // Increment
      if (0 != incrementdigit (l, Q, 0, M))
	printf ("Failed incrementdigit(l,%u,0,%u)\n", Q, M);
      // Print the array
      printf ("{");
      for (n = 0; n < Q - 1; n++)
	printf ("%d, ", l[n]);
      printf ("%d}\n", l[n]);
    }

  return 0;
}

int
main (int argc, char *argv[])
{
  /*
     #ifdef INT64
     printf("DEBUGGING: int %ld, long %ld, long long %ld\n",8*sizeof(int),8*sizeof(long),8*sizeof(long long));
     #else
     printf("DEBUGGING: int %d, long %d, long long %d\n",8*sizeof(int),8*sizeof(long),8*sizeof(long long));
     #endif
     printf("%d\n",argc);
   */

  if (3 != argc)
    {
      printf ("Usage: %s [factors] [number]\n", argv[0]);
      return 1;
    }

  incrementall (atoi (argv[1]), atoi (argv[2]));
  return 0;
}
