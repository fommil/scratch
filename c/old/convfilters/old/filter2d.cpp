//OUTDATED - this is very much behind the conv.c series!!!!!!!!!
//program to apply a filter to a 2D-array
//Filter file description (text file):    MAX SIZE = 500 values
//			line 1: 50 character description
//			line 2: filter size
//			line 3: logical if 1; zero all negative values
//			Line N: size * text values
//
//Input file description (text file):     values to filter
//------------------------------------------------------------------------------
//HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <iostream.h>
#include <fstream.h>


//------------------------------------------------------------------------------
//DEFINITIONS
#define SIZE 2050
#define FILTERSIZE 502

//------------------------------------------------------------------------------
//MAIN PROGRAM
main()
{
static double input[SIZE],filter[FILTERSIZE],output[SIZE];
char infilename[15],filterfilename[15],outfilename[15],temp[50];
int i,j,k,size,filtersize,zeroneg;

cout<<"Enter input filename: ";
cin>>infilename;
ifstream infile(infilename);if(!infile){cout<<"\""<<infilename<<"\" failed to open!"<<endl;return 1;}
cout<<"Enter filter filename: ";
cin>>filterfilename;
ifstream filterfile(filterfilename);if(!filterfile){cout<<"\""<<filterfilename<<"\" failed to open!"<<endl;return 1;}
cout<<"Enter output filename: ";
cin>>outfilename;
ofstream outfile(outfilename);if(!outfile){cout<<"\""<<outfilename<<"\" failed to open!"<<endl;return 1;}

filterfile.getline(temp,50,'\n');
cout<<"Description of filter: "<<temp<<endl;
filterfile>>filtersize;
filterfile>>zeroneg;
for(j=0;j<filtersize;j++)
	{if(filterfile.eof()){cout<<"Wrong size of Filter";break;}
   filterfile>>filter[j];}

infile>>temp;
outfile<<temp<<"\t";
for(j=0;j<2050;j++){infile>>input[j];}
for(j=0;j<2050;j++){outfile<<input[j]<<"\t";}
outfile<<endl;
cout<<"channels of output saved"<<endl;

size=2050-filtersize;
for(i=0;!(infile.eof());i++)
	{
   for(j=0;j<2050;j++){output[j]=0;}
   for(j=0;j<2050;j++){infile>>input[j];}
   if(infile.eof()!=0)break;
   printf("\r%d rows",i+1);
	for(j=0;j<2050;j++)
   	{
   	for(k=0;k<filtersize;k++)
   		{output[j]=output[j]+((input[j+k])*(filter[k]));}
      if((zeroneg==1)&&(output[j]<0.0)){output[j]=0.0;}
   	}
   printf("  %d converted",i+1);
   for(j=0;j<filtersize/2;j++){outfile<<"0\t";}
   for(j=0;j<size;j++){outfile<<output[j]<<"\t";}
   for(j=0;j<filtersize/2;j++){outfile<<"0\t";}
   printf("  %d saved",i+1);
   outfile<<endl;
   }

infile.close();
filterfile.close();
outfile.close();
cout<<endl<<"Finished!"<<endl;
return 0;
}

//------------------------------------------------------------------------------
//END OF CODE
