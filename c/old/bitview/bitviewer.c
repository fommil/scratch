/*
This is the linux version of bitviewer, written in c

To compile:

gcc bitviewer.c -o bv -DROWS=8

*/

#include <stdio.h>
//#define ROWS 8

main()
{
    FILE *infile;
    char filename[50];
    unsigned char i, c, c1, c2, c3, c4, c5, c6, c7, c8;
    unsigned int size = 0;

    printf
	("Sam Halliday, GNU Public Licence\n\rThis program shows any file as a bitmap\n\n\rEnter filename to view: ");
    scanf("%s", &filename);
    if ((infile = fopen(filename, "rb")) == NULL) {
	printf("%s failed to open!!\n", filename);;
	return 1;
    }
    printf("Viewing %s\n", filename);
    while (feof(infile) == 0) {
	for (i = 0; i < ROWS; i++, size++) {
	    c = getc(infile);
	    if (feof(infile) != 0)
		break;
	    c1 = (c >> 7);
	    c2 = ((c - (c1 << 7)) >> 6);
	    c3 = ((c - (c1 << 7) - (c2 << 6)) >> 5);
	    c4 = ((c - (c1 << 7) - (c2 << 6) - (c3 << 5)) >> 4);
	    c5 = ((c - (c1 << 7) - (c2 << 6) - (c3 << 5) -
		   (c4 << 4)) >> 3);
	    c6 = ((c - (c1 << 7) - (c2 << 6) - (c3 << 5) - (c4 << 4) -
		   (c5 << 3)) >> 2);
	    c7 = ((c - (c1 << 7) - (c2 << 6) - (c3 << 5) - (c4 << 4) -
		   (c5 << 3) - (c6 << 2)) >> 1);
	    c8 = (c - (c1 << 7) - (c2 << 6) - (c3 << 5) - (c4 << 4) -
		  (c5 << 3) - (c6 << 2) - (c7 << 1));
	    printf("%u%u%u%u%u%u%u%u ", c1, c2, c3, c4, c5, c6, c7, c8);
	}
	printf("\n\r");
    }
    printf("\n\rFile size %u Bytes\n\rFinished\n\r", size);
    return 0;
}
