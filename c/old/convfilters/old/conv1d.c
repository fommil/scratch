//OUTDATED!
//
//program to apply a filter to an array
//
//This is the command line code, the convolution functions are in conv.c whic needs compiling first
//This file is out of date with the funcion capabilities, this program is redundant
//as i have written an easier to use GUI which takes full advantage of the funtion capabilities.
//unfortuntly, it uses a Linux only library, called XForms.
//
//HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define CONV_SIZE 10000
#define CONV_FILTERSIZE 502

main(int argc, char *argv[])
{
static double input[CONV_SIZE],filter[CONV_FILTERSIZE],output[CONV_SIZE];
static char infilename[50],filterfilename[50],outfilename[50],filterdesc[51],helparg[6]="-help",filterarg[8]="-filter";
static int i,j,k,size,filtersize,samehelp,samefilter,zeroneg=0,doedges=0;
FILE *infile,*filterfile,*outfile;

if(argc>1)
{
for(j=1;j<argc;j++)
	{
	for(i=0,samehelp=0;i<5;i++){if(argv[j][i]!=helparg[i])samehelp++;}
	if(!samehelp){printf("\nUsage:\n\r%s infile filter outfile\n\n\rInfile format is ASCII text single column data, data separated by \\n\n%s -help\tbrings up this screen\n%s -filter\tfor filter file format details\nBy Sam Halliday\n\n",argv[0],argv[0],argv[0]);return 0;}
	for(i=0,samefilter=0;i<7;i++){if(argv[j][i]!=filterarg[i])samefilter++;}
	if(!samefilter){printf("\nFilter file description (text file):\n\tline 1: 50 character description\n\tline 2: filter size\n\tLine N: size * text values\nAlways check the conv.c file to make sure this is up to date.\n\rBy Sam Halliday\n\n");return 0;}
	}
}

if(argc<2)
{printf("Enter input filename: ");
scanf("%s",&infilename);}
else strcpy(infilename,argv[1]);
if((infile=fopen(infilename,"r"))==NULL){printf("%s failed to open!!\n\nUse '-help' for help and '-filter' for filter specifications.\n",infilename);return 1;}

if(argc<3)
{printf("Enter filter name: ");
scanf("%s",&filterfilename);}
else strcpy(filterfilename,argv[2]);
if((filterfile=fopen(filterfilename,"r"))==NULL){printf("%s failed to open!!\n\nUse '-help' for help and '-filter' for filter specifications.\n",filterfilename);fclose(infile);return 1;}


if(argc<4)
{printf("Enter output filename: ");
scanf("%s",&outfilename);}
else strcpy(outfilename,argv[3]);
if((outfile=fopen(outfilename,"w"))==NULL){printf("%s failed to open!!\n\nUse '-help' for help and '-filter' for filter specifications.\n",outfilename);fclose(infile);fclose(filterfile);return 1;}

conv_read_filterfile(filterfile,filter,&filtersize,filterdesc);
conv_read_infile(infile,input,&size);
conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
conv_saveoutput(size,outfile,output);

fclose(infile);
fclose(filterfile);
fclose(outfile);

printf("Finished!\nUse '-help' for help and '-filter' for filter specifications.\n\n");
return 0;
}

//------------------------------------------------------------------------------
//END OF CODE
