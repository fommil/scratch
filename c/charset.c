#include <stdio.h>
#include <stdlib.h>

/* http://en.wikipedia.org/wiki/Control_character */
char asciicntrl[32][4] =
  { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT",
  "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4",
  "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US"
};
char isocntrl[32][5] =
  { "PAD", "HOP", "BPH", "NBH", "IND", "NEL", "SSA", "ESA", "HTS", "HTJ",
  "VTS", "PLD", "PLU", "RI", "SS2", "SS3", "DCS", "PU1", "PU2", "STS",
  "CCH", "MW", "SPA", "EPA", "SOS", "SGCI", "SCI", "CSI", "ST", "OSC", "PM",
  "APC"
};

void printablechar (unsigned char c);

int
main ()
{
  int i, n;

  for (i = 0, n = 1; i < 256; i++, n++)
    {
      printf ("%-3d ", i);
      printablechar ((unsigned char) i);
      printf ("   ");
      if (8 == n)
	{
	  printf ("\n");
	  n = 0;
	}
    }
  printf ("\n");

  return 0;
}


void
printablechar (unsigned char c)
{
  /* ASCII control sequences */
  if (127 == c)
    printf ("DEL ");
  else if (32 > c)
    printf ("%-4.4s", asciicntrl[(int) c]);

  /* ISO-8859 control sequences */
  else if ((127 < c) && (160 > c))
    printf ("%-4.4s", isocntrl[(int) (c - 128)]);

  /* printable characters */
  else
    printf ("%-4c", c);
}
