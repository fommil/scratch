#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>

main()
{
unsigned char c,zero=0;
char filename[15]="ascii.txt",filename1[15]="input";
FILE *infile;
int position=0;

if ((infile=fopen(filename1,"rb"))==NULL){printf("Cannot open %s.\n",filename);getch();return 1;}
ofstream outfile(filename, ios::binary);
while((feof(infile))==0)
    {
    c=fgetc(infile);
    outfile<<zero<<c;
    printf("\r%u",position);
    position++;
    }
return 0;
}
