/*
Sam Halliday
10226982
This program is written in C++
It converts a file of binary, signed, 4-byte integers to an ASCII format output file.
*/
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>

main()
{
FILE *infile;
unsigned char i,ii,iii,iiii;
char filename[50],filename2[50];
static long position,integer;

cout<<"This program converts a binary 4-byte unsigned integer input file into an ASCII output"<<endl<<endl<<"Enter filename to convert: ";
cin>>filename;
if((infile=fopen(filename,"rb"))==NULL){printf("Cannot open %s.\n",filename);fclose(infile);return 1;}
cout<<"Enter output filename: ";
cin>>filename2;
ofstream outfile(filename2);
cout<<"Opening \""<<filename<<"\" for conversion"<<endl;
if(!outfile){cout<<"\""<<filename2<<"\" failed to open!!"<<endl;return 1;}
cout<<"Opened \""<<filename<<"\""<<endl<<"Converting to ASCII"<<endl;
while ((feof(infile))==0)
    {
    i=fgetc(infile);
    ii=fgetc(infile);
    iii=fgetc(infile);
    iiii=fgetc(infile);
    integer=(i<<24)+(ii<<16)+(iii<<8)+iiii;
    outfile<<integer<<endl;
    position++;
    printf("\r%d",position);
    }
cout<<" integer values successfully converted to ASCII"<<endl;
fclose(infile);
return 0;
}
