/*
Sam Halliday using C
This program takes x-y values along with a preferred choice of x values and
outputs in text file the new x-values with their corresponding y-values.
input is ASCII text and should be of the form  X-Y separated by tabs.
compile with line:
	gcc cubicspline.c -O3 -o cubicspline

To implement:
        -Graphical Output
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


#define MAXLINES 16000
#define FREE_ARG char*
#define NR_END 1

void free_vector(double *v, long nl, long nh)
{free((FREE_ARG) (v+nl-NR_END));}
void nrerror(char error_text[])
{fprintf(stderr,"Numerical recipes runtime error...\n");
fprintf(stderr,"%s\n",error_text);
fprintf(stderr,"...now exiting..\n");
exit(1);}
double *vector(long nl, long nh)
{double *v;
v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
if (!v) nrerror("allocation failure in vector()");
return v-nl+NR_END;}

void spline(double x[],double y[],int n,double yp1,double ypn,double y2[])
{
int i,k;
double p,qn,sig,un,*u;

u=vector(1,n-1);
if(yp1>0.99e30) y2[1]=u[1]=0.0;
else
	{
   y2[1]=-0.5;
   u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
   }
for(i=2;i<=n-1;i++)
	{
   sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
   p=sig*y2[i-1]+2.0;
   y2[i]=(sig-1.0)/p;
   u[i]=(y[i+1]-y[i])/(x[i+1]-x[i])-(y[i]-y[i-1])/(x[i]-x[i-1]);
   u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
   }
if (ypn>0.99e30) qn=un=0.0;
else
	{
   qn=0.5;
   un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
   }
y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
for(k=n-1;k>=1;k--)
	{
   y2[k]=y2[k]*y2[k+1]+u[k];
   }
free_vector(u,1,n-1);
}


void splint(double xa[],double ya[],double y2a[],int n,double x,double *y)
{
void nrerror(char error_text[]);
int klo,khi,k;
double h,b,a;

klo=1;
khi=n;
while(khi-klo>1)
	{
   k=(khi+klo)>>1;
   if(xa[k]>x) khi=k;
   else klo=k;
   }
h=xa[khi]-xa[klo];
if(h==0.0) nrerror("Bad xa input to routine splint");
a=(xa[khi]-x)/h;
b=(x-xa[klo])/h;
*y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
}





main(int argc, char *argv[])
{
char filename[50],filename2[50],temp[50],filename3[50],helparg[6]="-help",usefilexarg[7]="-newx-",tempch='s';
int i,j,k,size,samehelp,rangeerror=0,sameusexfile=0,xgivensize;
double x[MAXLINES],y[MAXLINES],y2[MAXLINES],xgiven[MAXLINES],yp1,ypn,xval,yval,start,step,max,inmax,inmin;
FILE *infile,*outfile,*xfile;

if(argc>1)
{for(j=1;j<argc;j++)
	{
	for(i=0,samehelp=0;i<5;i++){if(argv[j][i]==helparg[i])samehelp++;}
	if(samehelp==5){printf("Usage:\n\t%s [infile] [outfile] [newstartx] [step] [newendx]\n   OR\t%s [infile] [outfile] -newx-[xvalue file]\n   OR\t%s -help\n\nThis program takes an ASCII input of 2 columns (X and Y) of values,\nseparated by a [tab], and performs a cubic spline interpolation in\norder to find the Y values at given X values.\nBy Sam Halliday, subject to terms of GNU Public Licence\n",argv[0],argv[0],argv[0]);return 0;}
	else samehelp=0;
	for(i=0,sameusexfile=0;i<6;i++){if(argv[j][i]==usefilexarg[i])sameusexfile++;}
	if(sameusexfile==6)
		{
		for(k=0,i=6;tempch!='\0';k++,i++)
			{
			tempch=argv[j][i];
			filename3[k]=tempch;
			//printf("tempch = %c, filename3[k] = %c\n",tempch,filename3[k]);
			}
		printf("reading \"%s\" for new X values\n",filename3);
		if((xfile=fopen(filename3,"r"))==NULL){printf("%s failed to open!!\n",filename3);return 1;}
		for(k=0;feof(xfile)==0;k++)
			{
			if(feof(xfile)!=0)break;
			fscanf(xfile,"%s",&temp);
			if(feof(xfile)!=0)break;
			xgiven[k]=atof(temp);
			//printf("%g\n",xgiven[k]);
   			if(k>(MAXLINES-1)){printf("Number of X values too large, proceeding with first %d data points",MAXLINES);break;}
   			}
   		xgivensize=k;
		}
	else sameusexfile=0;
	}

}
tempch='s';
//get file information from user
if(argc<2)
{printf("Input file must be of format X-Y separated by tabs, no headings, with %d lines maximum.\nEnter input filename: ",MAXLINES);
scanf("%s",&filename);getchar();}
else if(argv[1][0]=='-')
        	{//printf("\nremoving -\n");
        	 for(j=0,i=1;tempch!='\0';j++,i++)
			{
			tempch=argv[1][i];
			filename[j]=tempch;
			//printf("tempch = %c, infilename[j] = %c\n",tempch,infilename[j]);
			}
        	}
else{strcpy(filename,argv[1]);}
if((infile=fopen(filename,"r"))==NULL){printf("%s failed to open!!\n",filename);return 1;}

tempch='s';
if(argc<3)
{printf("Enter output filename: ");
scanf("%s",&filename2);getchar();}
else if(argv[2][0]=='-')
        	{//printf("\nremoving -\n");
        	 for(j=0,i=1;tempch!='\0';j++,i++)
			{
			tempch=argv[2][i];
			filename2[j]=tempch;
			//printf("tempch = %c, infilename[j] = %c\n",tempch,infilename[j]);
			}
        	}
else{strcpy(filename2,argv[2]);}
if((outfile=fopen(filename2,"w"))==NULL){printf("%s failed to open!!\n",filename2);fclose(infile);return 1;}

//printf("What is the first derivative (try 1e30): ");
yp1=1e30;
//printf("What is the derivative at n (try 1e30): ");
ypn=1e30;

printf("reading \"%s\"\n",filename);
for(j=0;feof(infile)==0;j++)
	{
	if(feof(infile)!=0)break;
	fscanf(infile,"%s",&temp);
	if(feof(infile)!=0)break;
	x[j]=atof(temp);
	//printf("%g",x[j]);
	fscanf(infile,"%s",&temp);
	y[j]=atof(temp);
	//printf("\t%g\n",y[j]);
   	if(j>(MAXLINES-1)){printf("Input too big, proceeding with first %d data points",MAXLINES);break;}
   	}										//read file to get arrays
size=j;

for(i=0,inmax=0,inmin=0;i<size;i++)
	{if(x[i]>inmax){inmax=x[i];}
	 if(x[i]<inmin){inmin=x[i];}}

printf("Always try to keep new X-values within range of input file;\nFrom quick file scan, a safe X range is from %g to %g\n",inmin,inmax);
//printf("\nsamusefile=%d\n",sameusexfile);
if(sameusexfile==0)
	{
	if(argc<4){printf("Enter the new starting x value: ");scanf("%s",&temp);getchar();}
	else{strcpy(temp,argv[3]);}
	start=atof(temp);
	if(start<inmin){rangeerror++;}

	if(argc<5){printf("What is the x-step: ");scanf("%s",&temp);getchar();}
	else{strcpy(temp,argv[4]);}
	step=atof(temp);

	if(argc<6){printf("What is the maximum x value: ");scanf("%s",&temp);getchar();}
	else{strcpy(temp,argv[5]);}
	max=atof(temp);
	if(max>inmax){rangeerror++;}
        }
else
	{
	for(i=0;i<xgivensize;i++)
		{
		if(xgiven[i]<inmin)rangeerror++;
		if(xgiven[i]>inmax)rangeerror++;
		}
	}	
spline(x,y,size,yp1,ypn,y2);
//printf("\nX\tY\tDerivative\n");
fprintf(outfile,"X\tY\n");

if(sameusexfile==0)
	{
	for(xval=start,j=0;xval<=(max+step/2);xval=xval+step,j++)
		{
   		splint(x,y,y2,size,xval,&yval);
   		//printf("%g\t%g\t%g\n",xval,yval,y2[j]);
   		fprintf(outfile,"%g\t%g\n",xval,yval);
   		}
  	}
else
	{
	for(j=0;j<xgivensize;j++)
		{
		xval=xgiven[j];
   		splint(x,y,y2,size,xval,&yval);
   		//printf("%g\t%g\t%g\n",xval,yval,y2[j]);
   		fprintf(outfile,"%g\t%g\n",xval,yval);
   		}
  	fclose(xfile);
	}
  	
if(rangeerror!=0){printf("\nWARNING!!!\nSelected new X values are out of bounds from original\nTHIS PROGRAM DOES NOT EXTRAPOLATE, your values will be erratic\n");}
else{printf("X values were within limits of input\n");}
printf("For help: %s -help\nFinished\n",argv[0]);
fclose(infile);
fclose(outfile);
return 0;
}
