//OUTDATED BY CONVOLVE LIBRARY BY A LONG WAY!!!!!!!!!!
//
//program to apply a filter to an array
//Version 2, now with graphics!!
//Compile with line:
//
//gcc filter1d2g.c -lg2 -L /usr/X11R6/lib/ -lX11 -lgd -o convolve -O3 --static
//
//Filter file description (text file):    	MAX SIZE = 500 values
//				line 1: 50 character description
//				line 2: filter size
//				line 3: logical: if 1 zero all negative output values
//				Line N: size * text values
//
//Input file description (text file):     	MAX SIZE = 10000 values
//				values to filter
//------------------------------------------------------------------------------
//HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include <g2_PS.h>
//#include <g2_GIF.h>
#include <math.h>
//#include "penguin.c"
//------------------------------------------------------------------------------
//DEFINITIONS
#define SIZE 10000
#define FILTERSIZE 502

//------------------------------------------------------------------------------
//MAIN PROGRAM
main(int argc, char *argv[])
{
static double input[SIZE],filter[FILTERSIZE],output[SIZE],allout[SIZE+FILTERSIZE];
char ch,tempch='s',infilename[50],filterfilename[50],outfilename[50],temp[50],helparg[6]="-help",filterarg[8]="-filter";
int i,id,j,k,size,filtersize,zeroneg,samehelp=0,samefilter=0;
FILE *infile,*filterfile,*outfile;
int ymax,xmax,colour,allpos;
double plotx,ploty,filtermax,filtermin,filterxscale,filteryscale,doubfiltersize;
double inmin,inmax,inxscale,inyscale;
double outmax,outmin,outxscale,outyscale;

if(argc>1)
{
for(j=1;j<argc;j++)
	{
	for(i=0,samehelp=0;i<5;i++){if(argv[j][i]==helparg[i])samehelp++;}
	if(samehelp==5){printf("\nUsage:  %s [infile] [filter] [outfile]\n\n\rInfile format is ASCII text single column data, data separated by \\n\n%s -help      brings up this screen\n%s -filter    for filter file format details\nBy Sam Halliday\n\n",argv[0],argv[0],argv[0]);return 0;}
	else samehelp=0;
	for(i=0,samefilter=0;i<7;i++){if(argv[j][i]==filterarg[i])samefilter++;}
	if(samefilter==7){printf("\nFilter file description (text file):\n\tMAX SIZE = 500 values\n\tline 1: 50 character description\n\tline 2: filter size\n\tline 3: logical: if 1 zero all negative output values\n\tLine N: size * text values\nBy Sam Halliday\n\n");return 0;}
	else samefilter=0;
	}
}


//printf("\n%s\n%s\n%s\n",argv[1],argv[2],argv[3]);

if(argc<2)
{printf("Enter input filename: ");
scanf("%s",&infilename);getchar();}
else if(argv[1][0]=='-')
        	{//printf("\nremoving -\n");
        	 for(j=0,i=1;tempch!='\0';j++,i++)
			{
			tempch=argv[1][i];
			infilename[j]=tempch;
			//printf("tempch = %c, infilename[j] = %c\n",tempch,infilename[j]);
			}
        	}
else {strcpy(infilename,argv[1]);}
if((infile=fopen(infilename,"r"))==NULL){printf("%s failed to open!!\n",infilename);return 1;}

tempch='s';
if(argc<3)
{printf("Enter filter name: ");
scanf("%s",&filterfilename);getchar();}
else if(argv[2][0]=='-')
        	{
        	 for(j=0,i=1;tempch!='\0';j++,i++)
			{
			tempch=argv[2][i];
			filterfilename[j]=tempch;
			//printf("tempch = %c, filterfilename[j] = %c\n",tempch,filterfilename[j]);
			}
        	}
else strcpy(filterfilename,argv[2]);
if((filterfile=fopen(filterfilename,"r"))==NULL){printf("%s failed to open!!\n",filterfilename);fclose(infile);return 1;}

tempch='s';
if(argc<4)
{printf("Enter output filename: ");
scanf("%s",&outfilename);getchar();}
else if(argv[3][0]=='-')
        	{
        	 for(j=0,i=1;tempch!='\0';j++,i++)
			{
			tempch=argv[3][i];
			outfilename[j]=tempch;
			//printf("tempch = %c, outfilename[j] = %c\n",tempch,outfilename[j]);
			}
        	}
else strcpy(outfilename,argv[3]);
if((outfile=fopen(outfilename,"w"))==NULL){printf("%s failed to open!!\n",outfilename);fclose(infile);fclose(filterfile);return 1;}

fgets(temp,50,filterfile);
printf("\nDescription of filter: %s",temp);
fscanf(filterfile,"%d",&filtersize);
fscanf(filterfile,"%d",&zeroneg);


for(j=0;feof(infile)==0;j++)
	{
	
	if(feof(infile)!=0)break;
	fscanf(infile,"%s",&temp);
	input[j]=atof(temp);
   	if(j>(SIZE-1)){printf("Input too big, proceeding with first %d data points",SIZE);break;}
   	}

  	
size=(j+1);
size=size-filtersize;

for(j=0;j<filtersize;j++)
	{
	if(feof(filterfile)!=0){printf("\n\rWrong size of Filter");break;}
 	fscanf(filterfile,"%s",&temp);
	filter[j]=atof(temp);
	}

for(j=0;j<size;j++)
	{for(k=0;k<filtersize;k++)
   		{output[j]=output[j]+((input[j+k])*(filter[k]));}
	if((zeroneg==1)&&(output[j]<0.0))
		{output[j]=0.0;}
   	}

for(j=0;j<filtersize/2;j++)
	{allout[j]=0.0;}
for(j=0;j<size;j++)
	{allpos=j+filtersize/2;
	allout[allpos]=output[j];}
for(j=0;j<filtersize/2;j++)
	{allpos++;
	allout[allpos]=0.0;}	
		

for(j=0;j<(size+filtersize);j++)
	{
	fprintf(outfile,"%g\n",allout[j]);
	}


fclose(infile);
fclose(filterfile);
fclose(outfile);

//--------------- The Graphics Part-----------------------------------------------
xmax=800;
ymax=400;
id = g2_open_X11(xmax,ymax);


plot_it_all:
//-- The Filter Printing Part -------------------------------------------
g2_set_coordinate_system(id,xmax-91,ymax-51,1,1);
for(i=0,filtermax=0,filtermin=0;i<filtersize;i++)
	{if(filter[i]>filtermax){filtermax=filter[i];}
	if(filter[i]<filtermin){filtermin=filter[i];}}
filterxscale=filtersize/80.0;
if((fabs(filtermax))>(fabs(filtermin))){filteryscale=fabs(filtermax/40.0);}
else{filteryscale=fabs(filtermin/40.0);}	
for(i=0;i<filtersize;i++)
	{if(i==0) {plotx = i/filterxscale;
	           ploty = (filter[i])/filteryscale;
	           g2_move(id,plotx,ploty);}
	else      {plotx = i/filterxscale;
	           ploty = filter[i]/filteryscale;
	           g2_line_to(id,plotx,ploty);}}
g2_move(id,-10,-50);
colour=g2_ink(id,1.0,0,0);
g2_pen(id,colour);
g2_line_r(id,0,100);
g2_line_r(id,100,0);
g2_line_r(id,0,-100);
g2_line_r(id,-100,0);
g2_move(id,-10,0);
g2_line_r(id,100,0);
g2_string(id,0,-65,filterfilename);
//-----Start input data printing-----------------------------------------
g2_set_coordinate_system(id,50,50,1,1);
//g2_image(id,xmax-104,-50,53,62, penguin);  //Just for Fun
for(i=0,inmax=0,inmin=0;i<(size+filtersize);i++)
	{if(input[i]>inmax){inmax=input[i];}
	if(input[i]<inmin){inmin=input[i];}}
inxscale=(size+filtersize)/(xmax-100.0);
if((fabs(inmax))>(fabs(inmin))){inyscale=fabs(inmax/(ymax-100));}
else{inyscale=fabs(inmin/(ymax-100));}
colour=g2_ink(id,1,0,0);
g2_pen(id,colour);
g2_set_line_width(id,1);
for(i=0;i<(filtersize+size);i++)
	{if(i==0) {plotx = i/inxscale;
	           ploty = (input[i])/inyscale;
	           g2_move(id,plotx,ploty);}
	else      {plotx = i/inxscale;
	           ploty = input[i]/inyscale;
	           g2_line_to(id,plotx,ploty);}}
//--------------End of Input printing to screen, start output--------------
for(i=0,outmax=0,outmin=0;i<(size+filtersize);i++)
	{if(allout[i]>outmax){outmax=allout[i];}
	 if(allout[i]<outmin){outmin=allout[i];}}
outxscale=(size+filtersize)/(xmax-100.0);
if( (fabs(outmax))>(fabs(outmin))){outyscale=fabs(outmax/(ymax-100));}
else{outyscale=fabs(outmin/(ymax-100));}
colour=g2_ink(id,0,0,0);
g2_pen(id,colour);
g2_set_line_width(id,1);
for(i=0;i<(filtersize+size);i++)
	{if(i==0)  {plotx = i/outxscale;
		    ploty = (allout[i])/outyscale;
		    g2_move(id,plotx,ploty);}
	else       {plotx = i/outxscale;
		    ploty = allout[i]/outyscale;
	 	    g2_line_to(id,plotx,ploty);}}
//--------------End of Output, Start Axis-----------------------------------
g2_move(id,0,0);
colour=g2_ink(id,0,0,0);
g2_pen(id,colour);
g2_set_line_width(id,1);
g2_line_to(id,xmax-100,0);
g2_filled_triangle(id,xmax-94,0,xmax-100,3,xmax-100,-3);
g2_move(id,0,0);
g2_line_to(id,0,ymax-100);
g2_filled_triangle(id,0,ymax-94,-3,ymax-100,3,ymax-100);
g2_set_font_size(id,20);
g2_string(id,xmax/2-100,ymax-100,"Convolved Output");
colour=g2_ink(id,1,0,0);
g2_pen(id,colour);
g2_string(id,xmax/2-100,ymax-80,"Input");
g2_set_font_size(id,20);
colour=g2_ink(id,0,0,0);
g2_pen(id,colour);
g2_string(id,350,-30,"X");
g2_string(id,-30,150,"Y");



printf("Click here then [enter] to exit, 's' to save to PS and exit\n");
scanf("%c",&ch);
if(ch=='s')
	{
	g2_close(id);
	printf("Enter PS output filename: ");
	scanf("%s",&temp);
	id=g2_open_PS(temp,g2_A4,g2_PS_land);
	xmax=756;ymax=522;
	goto plot_it_all;
	}
/*else if(ch=='g')
	{
	g2_close(id);
	printf("Enter GIF output filename: ");
	scanf("%s",&temp);
	id=g2_open_GIF(temp,xmax,ymax);
	goto plot_it_all;
	}
*/
else{g2_close(id);}
//----------------End of Graphics Part


printf("Use '-help' for help and '-filter' for filter specifications.\nUses g2 Graphics Library and Subject to Terms of GNU Public Licence\nFinished\n\n");
return 0;
}

//------------------------------------------------------------------------------
//END OF CODE
