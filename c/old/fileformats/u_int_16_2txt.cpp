/*
Sam Halliday
10226982
This program is written in C++
It converts a file of binary, unsigned, 2-byte integers to an ASCII format output file.
*/

#include <iostream.h>
#include <fstream.h>
#include <stdio.h>

main()
{
FILE *infile;
static unsigned char i,ii;
static char filename[50],filename2[50];
static long position;
static unsigned short integer;

cout<<"Sam Halliday, GNU Public Licence"<<endl<<"This program converts a binary 2-byte signed integer input file"<<endl<<"into an ASCII output"<<endl<<"Enter filename to convert: ";
cin>>filename;
if((infile=fopen(filename,"rb"))==NULL){printf("%s failed to open!!\n",filename);return 1;}
cout<<"Enter output filename: ";
cin>>filename2;
ofstream outfile(filename2);
if(!outfile){cout<<"\""<<filename2<<"\" failed to open!!"<<endl;fclose(infile);return 1;}
cout<<"Converting to ASCII"<<endl;
while ((feof(infile)==0))
    {
    i=fgetc(infile);
    ii=fgetc(infile);
    integer=(i<<8)+ii;
    outfile<<integer<<endl;
    position++;
    printf("\r%d",position);
    }
cout<<" integer values successfully converted to ASCII"<<endl;
fclose(infile);
return 0;
}
