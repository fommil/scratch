//Function Library to apply a filter to an array
//Version 1.4
//
// Updates:     - smart edge normalisation
//
// BUGS:        - assumes data is zeroed outside the set (ie doesnt extrapolate input field, effects edges)
//		- doesnt support even numbered filters too well.. output x-offset by 1/2 row
//              - edge normailistaion isnt always too smart
// TO IMPLEMENT:- resampling for even numbered filters
//              - 2d 'image' matrix convolution functions
//
// Filter file description (text file):    	MAX CONV_SIZE = unlimited values (given in user's program)
//				line 1: 50 character description
//				line 2: filter size
//				Line N: size * text values
//
// Input file description (text file):     	MAX CONV_SIZE = unlimited values (given in user's program)
//				values to filter
//
//------------------------------------------------------------------------------
//Included Functions:
//
//
// conv_read_filterfile(FILE *conv_filterfile,float conv_filter[],int *conv_filtersize,char conv_filterdesc[])
// conv_read_infile(FILE *conv_infile,float conv_input[],int *conv_size)
// conv_convolve(float conv_input[],int conv_size,float conv_filter[],int conv_filtersize,float conv_output[],int conv_zeroneg,int conv_doedges)
// conv_saveoutput(int conv_size, FILE *conv_outfile,float conv_output[])
//
//
//------------------------------------------------------------------------------
//HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

conv_read_filterfile(FILE *conv_filterfile,float conv_filter[],int *conv_filtersize,char conv_filterdesc[])
{
int conv_j;
char conv_temp[50];

fgets(conv_filterdesc,51,conv_filterfile);
fscanf(conv_filterfile,"%d",conv_filtersize);
for(conv_j=0;conv_j<(*conv_filtersize);conv_j++)
	{
	if(feof(conv_filterfile)!=0){printf("\n\rWrong size of Filter");break;}
 	fscanf(conv_filterfile,"%s",&conv_temp);
	conv_filter[conv_j]=atof(conv_temp);
	}
}

//-----------------------------------

conv_read_infile(FILE *conv_infile,float conv_input[],int *conv_size)
{
int conv_j;
char conv_temp[50];

for(conv_j=0;feof(conv_infile)==0;conv_j++)
	{
	if(feof(conv_infile)!=0)break;
	fscanf(conv_infile,"%s",&conv_temp);
	conv_temp[50];conv_input[conv_j]=atof(conv_temp);
   	}
*conv_size=conv_j-1;
}

//----------------------------------

conv_convolve(float conv_input[],int conv_size,float conv_filter[],int conv_filtersize,float conv_output[],int conv_zeroneg, int conv_edges)
{
static int conv_j,conv_k,conv_outpos,conv_temp2;
static float conv_temp,conv_sumfilter,conv_tempsumfilter;

for(conv_j=0,conv_sumfilter=0;conv_j<conv_filtersize;conv_j++)
        {
        conv_sumfilter=conv_sumfilter+conv_filter[conv_j];
        }

for(conv_j=0;conv_j<conv_size;conv_j++)
	{conv_output[conv_j]=0.0;}

conv_temp2=conv_filtersize/2;
conv_size=conv_size-2*conv_temp2;

if(conv_edges==1)
{
for(conv_j=0;conv_j<(conv_filtersize/2);conv_j++,conv_tempsumfilter=0,conv_temp=0)
	{
	for(conv_k=((conv_filtersize/2)-conv_j);conv_k<(conv_filtersize);conv_k++)
		{
		conv_output[conv_j]=conv_output[conv_j]+((conv_input[conv_j+ (conv_filtersize/2) -conv_k])*(conv_filter[conv_k]));
                conv_tempsumfilter=conv_tempsumfilter+conv_filter[conv_k];
                }
        conv_temp= conv_sumfilter/conv_tempsumfilter;
        conv_output[conv_j]=(conv_temp*conv_output[conv_j]);
	}
 }

conv_outpos=conv_temp2;

for(conv_j=0;conv_j<(conv_size);conv_j++,conv_outpos++)
	{
	for(conv_k=0;conv_k<(conv_filtersize);conv_k++)
		{
		conv_output[conv_outpos]=conv_output[conv_outpos]+((conv_input[conv_j+conv_k])*(conv_filter[conv_k]));
		}
	}

conv_size=conv_size+2*conv_temp2;

if(conv_edges==1)
{
for(conv_j=0,conv_tempsumfilter=0;conv_outpos<conv_size;conv_outpos++,conv_j++,conv_tempsumfilter=0,conv_temp=0)
	{
	for(conv_k=1+conv_j;conv_k<conv_filtersize;conv_k++)
		{
		conv_output[conv_outpos]=conv_output[conv_outpos]+((conv_input[1+conv_outpos+conv_k-conv_filtersize/2])*(conv_filter[conv_k]));
                conv_tempsumfilter=conv_tempsumfilter+conv_filter[conv_k];
                }
        conv_temp= conv_sumfilter/conv_tempsumfilter;
        conv_output[conv_outpos]=(conv_temp*conv_output[conv_outpos]);
        }
}
for(conv_j=0;conv_j<(conv_size);conv_j++)
	{
	if((conv_zeroneg==1)&&(conv_output[conv_j]<0.0))
		{
		conv_output[conv_j]=0.0;}
   		}
	}

//---------------------------------------------

conv_saveoutput(int conv_size, FILE *conv_outfile,float conv_output[])
{
int conv_j;
for(conv_j=0;conv_j<conv_size;conv_j++)
	{
	fprintf(conv_outfile,"%g\n",conv_output[conv_j]);
	}
}
//------------------------------------------------------------------------------
//END OF CODE
