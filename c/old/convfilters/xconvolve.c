// xconv v0.09-
//
// THIS IS A BETA X-VERSION of convolution filter...
//
// gcc -L/usr/X11R6/lib/ -lforms -lXpm -lXext -lm xconvolve.c conv.o -o xconv
//
// To Implement:- scroll bars in graphs
//              - library of filters
//		- graphical/descriptive message filter browser
//		- save to PostScript file
//
// program to apply a filter to an array
// Filter file description (text file):    	MAX CONV_SIZE = 500 values
//				line 1: 50 character description
//				line 2: filter size
//				line 3: logical: if 1 zero all negative output values
//				Line N: size * text values
//
// Input file description (text file):     	MAX CONV_SIZE = 10000 values
//				values to filter
//------------------------------------------------------------------------------
//HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <forms.h>

//------------------------------------------------------------------------------
//DEFINITIONS
#define CONV_SIZE 10000
#define CONV_FILTERSIZE 502
FL_FORM *form;
FL_OBJECT *inplot,*filterplot,*boxchange,*zeronegbox,*doedgesbox,*outplot,*savebox,*quicksavebox,*quit,*infilenamebox,*filterfilenamebox,*filterdescbox;

//------------------------------------------------------------------------------	
//MAIN PROGRAM



main(int argc, char *argv[])
{
static int i,j,samehelp,samefilter,filtersize,size,zeroneg,doedges;
static float input[CONV_SIZE],filter[CONV_FILTERSIZE],output[CONV_SIZE],xdatapoints[CONV_SIZE];
static char infilename[50],filterdesc[51]="Please Choose Input and Filter Files",filterfilename[50],outfilename[50];
const char *fileptr;
FILE *infile,*filterfile,*outfile;

for(i=0;i<CONV_SIZE;i++){xdatapoints[i]=i+1;}	//Create an array of X-Values (0->CONV_SIZE-1)

fl_initialize(&argc,argv,"XConvolve Form",0,0);
form = fl_bgn_form(FL_FRAME_BOX,704,640);
quit = fl_add_button(FL_NORMAL_BUTTON,622,2,80,20,"Quit");
zeronegbox = fl_add_button(FL_PUSH_BUTTON,322,2,80,20,"Zero");
doedgesbox = fl_add_button(FL_PUSH_BUTTON,402,2,80,20,"Edges");
inplot=fl_add_xyplot(FL_FILL_XYPLOT,2,22,700,250,"");
filterplot=fl_add_xyplot(FL_LINEPOINTS_XYPLOT,70,272,300,100,"");
outplot=fl_add_xyplot(FL_FILL_XYPLOT,2,382,700,250,"");
infilenamebox = fl_add_button(FL_NORMAL_BUTTON,2,2,80,20,"Input");
filterfilenamebox=fl_add_button(FL_NORMAL_BUTTON,82,2,80,20,"Filter");
savebox=fl_add_button(FL_NORMAL_BUTTON,162,2,80,20,"Save As");
quicksavebox=fl_add_button(FL_NORMAL_BUTTON,242,2,80,20,"Save");
filterdescbox=fl_add_text(FL_NORMAL_TEXT,400,280,250,100,filterdesc);

fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
fl_set_xyplot_data(outplot,xdatapoints,output,size,outfilename,"X","");
fl_end_form();
fl_show_form(form,FL_PLACE_MOUSE,FL_TRANSIENT,"XConvolve");
while((boxchange =fl_do_forms())!=quit)
	{
	if(boxchange==infilenamebox)
		{
		if((fileptr=fl_show_fselector("InFile","./","*.dat","data.dat"))!= NULL)
			{
			strcpy(infilename,fileptr);
			if((infile=fopen(infilename,"r"))==NULL)
								{
								fl_show_messages("Input File Failed to Open!");
								}
			else{conv_read_infile(infile,input,&size);
			conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
			fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
			fclose(infile);}
			}
		}

	else if(boxchange==filterfilenamebox)
		{
		if((fileptr=fl_show_fselector("Filter","/home/filters/","*.cnf","smooth.cnf"))!= NULL)
			{
			strcpy(filterfilename,fileptr);
			if((filterfile=fopen(filterfilename,"r"))==NULL)
								{
								fl_show_messages("Filter File Failed to Open!");
								}
			else{conv_read_filterfile(filterfile,filter,&filtersize,filterdesc);
			fl_set_object_label(filterdescbox,filterdesc);
			conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
			fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
			fclose(filterfile);}
			}
		}	
		
	else if(boxchange==savebox)
		{
		if((fileptr=fl_show_fselector("Save As","./","*.dat","out.dat"))!= NULL)
			{
			strcpy(outfilename,fileptr);
			if((outfile=fopen(outfilename,"w"))==NULL){fl_show_messages("Output File Failed to Open!");}
			else{fl_set_xyplot_data(outplot,xdatapoints,output,size,outfilename,"X","");
			conv_saveoutput(size,outfile,output);
			fclose(outfile);}
			}
		}
	 else if(boxchange==quicksavebox)
		{
		if((outfile=fopen(outfilename,"w"))==NULL){fl_show_messages("Output File Failed to Open!");}
		else{fl_set_xyplot_data(outplot,xdatapoints,output,size,outfilename,"X","");
		conv_saveoutput(size,outfile,output);
		fclose(outfile);}
		}
        else if(boxchange==zeronegbox)
                {
                if(fl_get_button(zeronegbox)==0)
                        {
                        zeroneg=0;
                        conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
                        fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
                        fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
                        }
                else
                        {
                        zeroneg=1;
                        conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
                        fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
                        fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
                        }
                }
        else if(boxchange==doedgesbox)
                {
                if(fl_get_button(doedgesbox)==0)
                        {
                        doedges=0;
                        conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
                        fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
                        fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
                        }
                else
                        {
                        doedges=1;
                        conv_convolve(input,size,filter,filtersize,output,zeroneg,doedges);
                        fl_set_xyplot_data(inplot,xdatapoints,input,size,infilename,"X","");
                        fl_set_xyplot_data(filterplot,xdatapoints,filter,filtersize,"","","");
			fl_set_xyplot_data(outplot,xdatapoints,output,size,"","X","");
                        }
                }}
fl_hide_form(form);
return 0;
}

//------------------------------------------------------------------------------
//END OF CODE
