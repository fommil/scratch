/* This file is licensed under the GNU GPL */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int skipwhitespace (FILE * file);

int
main (int argc, char *argv[])
{
  double data[MAX][MAX];
  FILE *inputfile, *outputfile;
  int r = 0, c = 0, cols = 0, rows = 0;

  if (argc < 3)
    {
      printf ("Usage: %s <input.dat> <output.dat>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  if ((inputfile = fopen (argv[1], "r")) == NULL)
    {
      printf ("Cannot open %s for read!\n", argv[1]);
      exit (EXIT_FAILURE);
    }
  if ((outputfile = fopen (argv[2], "w")) == NULL)
    {
      printf ("Cannot open %s for write!\n", argv[2]);
      fclose (inputfile);
      exit (EXIT_FAILURE);
    }

  /* read in the input file */
  /* the first 2 rows are indices */
  while (0 == feof (inputfile))
    {
      if (0 < skipwhitespace (inputfile))
	{
	  r++;
	  if (1 == r)
	    cols = c;
	  if (cols != c)
	    printf
	      ("WARNING: number of columns changed from %d to %d on line %d\n"
	       "         the input data is most likely corrupted.\n",
	       cols, c, r - 1);
	  c = 0;
	}
      if (0 != feof (inputfile))
	{
	  rows = r - 2;
	  break;
	}
      fscanf (inputfile, "%lg", &data[r][c]);
#ifdef DEBUG
      printf (": data[%d][%d]=%lg\n", r, c, data[r][c]);
#endif
      c++;
    }
#ifdef DEBUG
  printf ("\nrows=%d\tcols=%d\n", rows, cols);
#endif

  /* output the gnuplot formatted file */
  fprintf (outputfile, "# generated using matlab2gnuplot\n\n");
  for (r = 0; r < rows; r++)
    {
      for (c = 0; c < cols; c++)
	/* matlab works to 7 decimal places by default */
	fprintf (outputfile, "%.7le\t%.7le\t%.7le\n", data[0][r], data[1][c],
		 data[r + 2][c]);
      fprintf (outputfile, "\n");
    }

  fclose (inputfile);
  fclose (outputfile);
#ifdef DEBUG
  printf ("EXITING: %s %d\n", __FILE__, __LINE__);
#endif
  return 0;
}

int
skipwhitespace (FILE * file)
{
  char fred;
  int n = 0, loopagain = 1;

  while (0 != loopagain)
    {
      /* skip whitespace */
      fred = getc (file);
      while (' ' == fred || '\t' == fred || '\f' == fred || '\r' == fred
	     || '\v' == fred)
	{
	  fred = getc (file);
#ifdef DEBUG
	  printf (" WHITESPACE");
#endif
	}

      /* increment the newline count, and loop again */
      if ('\n' == fred)
	{
	  n++;
	  loopagain = 1;
#ifdef DEBUG
	  printf (" NEWLINE ");
#endif
	}
      else
	loopagain = 0;
    }

  /* non-whitespace found, rewind so the file descriptor sits on it */
  /* unless it is the EOF, in which case we leave it pointed there */
  if (0 == feof (file))
    ungetc (fred, file);

  /* return the number of newlines we encountered */
#ifdef DEBUG
  printf (" (%d newlines)", n);
#endif
  return n;
}
