/*
Compile with:
		gcc -O3 samadd2.c -o samadd

This program adds 2 decimal values together. But it teaches the computer to count in
decimal (in a way) and therefore only has a maximum number of digits given by
the memory space dedicated to the program. This limit is given by MAXDIGITS
in the defines. This is comparable to the incomplete 10 digits which 32-bit
numbers limit, and combats the problem that double numbers are only accurate
to 6 digits despite the raised power. Should be easily changed to addition in
hexadeciaml or octal. Future plans are to build a library of math
functions which add, subtract, divide, multiply, raise to the power and square
root with the same limitations, also with decimal points and with negative
values included. This will be in the form of a function library where string
arrays of numbers and special symbols are passed to it.

Allowed values in string arrays:		Character 	Represents
						0-9       	The Number Value
      						.        	Decimal Point Position
         					,        	Decimal Point Position
              					-        	Negative Value
                   				+        	Positive Value (not necessary)
		       				NULL      	End of Numbers (essential)

Format for the number arrays:			Value		Reserved For
						0-9     	Associated Value
      						11       	End of Numbers in Array Marker
      						12       	Decimal Point Marker
                                                13		Negation
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXDIGITS 100
#define ENDMARK 11
#define DECMARK 12
#define NEGATION 13

samadd(char string1[],char string2[],char addarray[])
{
static char array1[MAXDIGITS+4],array2[MAXDIGITS+4];
static char digit,carry,larger,logizero,logidecimal,decnumbers,largerafterdecimal,ve1,ve2;
static long int i,j,k,ea1,ea2,eaa,errorcount,temp1,temp2,a1d,a2d,aad;

for(i=0,logizero=0;logizero==0;i++) //This loop removes unnecessary preceeding zeros and '+' symbols
	{
	if((string1[i])==45){ve1=-1;}
	else{ve1=1;}
	if((string1[i]==48)||(string1[i]==43)||(string1[i]==45)){logizero=0;}
   	else{logizero++;}}
i--;
for(j=0;(string1[i]!='\0');i++,j++)
	{
   if((string1[i]==44)||(string1[i]==46)){logidecimal++;a1d=j+1;array1[j]=DECMARK;if(logidecimal>1){errorcount++;printf("ERROR decimal marker used more than once!\n");return errorcount;}}
   else if((string1[i]>57)||(string1[i]<48)){errorcount++;printf("ERROR \"%c\" is not a valid number!\n",string1[i]);return errorcount;}
	else{array1[j]=string1[i]-48;}
   }
ea1=j-1;

if(logidecimal==0){a1d=ea1+2;ea1=ea1+2;array1[ea1]=0;array1[ea1-1]=DECMARK;}
else {decnumbers=1;}
array1[ea1+1]=ENDMARK;

//for(i=0;i<MAXDIGITS+2;i++){string[i]=0;} //TO ZERO STRING ARRAY
if(logidecimal!=0)decnumbers=1;
logidecimal=0;
logizero=0;

for(i=0,logizero=0;logizero==0;i++) //This loop removes an unnecessary preceeding zero or '+' symbol
	{
	if((string2[i])==45){ve2=-1;}else{ve2=1;}
	if((string2[i]==48)||(string2[i]==43)||(string2[i]==45)){logizero=0;}
 	else{logizero++;}}
i--;
for(j=0;(string2[i]!='\0');i++,j++)
	{
   if((string2[i]==44)||(string2[i]==46)){logidecimal++;a2d=j+1;array2[j]=DECMARK;if(logidecimal>1){errorcount++;printf("ERROR decimal marker used more than once!\n");return errorcount;}}
   else if((string2[i]>57)||(string2[i]<48)){errorcount++;printf("ERROR \"%c\" is not a valid number!\n",string2[i]);return errorcount;}
   else{array2[j]=string2[i]-48;}
   }
ea2=j-1;
if(logidecimal==0){a2d=ea2+2;ea2=ea2+2;array2[ea2]=0;array2[ea2-1]=DECMARK;}
else {decnumbers=1;}
array2[ea2+1]=ENDMARK;

//printf("\ndecnumbers = %d\n",decnumbers);

ea1++;ea2++;
	if((a1d)>(a2d)){larger=1;eaa=a1d;aad=a1d;addarray[aad]=DECMARK;}
	else if((a1d)<(a2d)){larger=2;eaa=a2d;aad=a2d;addarray[aad]=DECMARK;}
	else{larger=0;eaa=a1d;aad=a1d;addarray[aad]=DECMARK;}
	//printf("\na1d = %d a2d = %d eaa = %d larger = %d",a1d,a2d,eaa,larger);
	if((ea1-a1d)>(ea2-a2d)){largerafterdecimal=1;eaa=eaa+(ea1-a1d);}
	else if((ea1-a1d)<(ea2-a2d)){largerafterdecimal=2;eaa=eaa+(ea2-a2d);}
	else {largerafterdecimal=0;eaa=eaa+(ea1-a1d);}
	//printf("\nea1 = %d ea2 = %d eaa = %d largerafterdecimal = %d\n",ea1,ea2,eaa,largerafterdecimal);

addarray[eaa+1]=ENDMARK;
//-----------------------------------------------------------------------------
//This is the counting bit, the core of the program
i=ea1-1;
j=ea2-1;
k=eaa;

carry=0;
if(largerafterdecimal==1)
	{
	while((i-a1d)>(j-a2d))
		{
		temp1=array1[i];
  		digit=temp1+carry;
  		addarray[k]=digit;
  		i--;k--;
		}
	}
else if(largerafterdecimal==2)
	{
	while((i-a1d)<(j-a2d))
		{
		temp2=array2[j];
  		digit=temp2+carry;
   		addarray[k]=digit;j--;k--;
		}
	}
//printf("i=%d j=%d k=%d\n",i,j,k);
	
while((array1[i]!=DECMARK)&&(array2[j]!=DECMARK))
	{
	temp1=array1[i];
	temp2=array2[j];
	digit=temp1+temp2+carry;
	if(digit>9){addarray[k]=digit-10;carry=1;}
	else{addarray[k]=digit;carry=0;}
	i--;j--;k--;
	}

i--;j--;k--;
//printf("i=%d j=%d k=%d\n",i,j,k);	

while((i>=0)&&(j>=0)&&(k>0))
	{
   	temp1=array1[i];
   	temp2=array2[j];
   	digit=temp1+temp2+carry;
   	if(digit>9){addarray[k]=digit-10;carry=1;}
   	else{addarray[k]=digit;carry=0;}
   	i--;j--;k--;
	}
	

if(larger==1)
	{
   	while(i>=0)
   		{temp1=array1[i];
   		digit=temp1+carry;
   		if(digit>9){addarray[k]=digit-10;carry=1;}
   		else{addarray[k]=digit;carry=0;}
   		i--;k--;}
   	}
else if(larger==2)
	{
   	for(;j>=0;j--,k--)
   		{temp2=array2[j];
   		digit=temp2+carry;
   		if(digit>9){addarray[k]=digit-10;carry=1;}
   		else{addarray[k]=digit;carry=0;}}
   	}

addarray[0]=carry;
//-----------------------------------------------------------------------------
//Print out
/*for(i=0;array1[i]!=ENDMARK;i++)
	{if(array1[i]==DECMARK){printf(".");}
   	else printf("%d",array1[i]);
   	}
printf("\n+\n");
for(i=0;array2[i]!=ENDMARK;i++)
	{if(array2[i]==DECMARK){printf(".");}
   	else printf("%d",array2[i]);
   	}
printf("\n=\n");*/
if((eaa==MAXDIGITS+2)&&(addarray[0]==1)){printf("WARNING WARNING WARNING WARNING WARNING WARNING WARNING\nAnswer out of limits!!!!\n");}
}

main()
{
static char instring1[MAXDIGITS+1],instring2[MAXDIGITS+1],outaddarray[MAXDIGITS+5];
static long int i;
printf("Sam Halliday, GNU Public License\nThis build is limited to %d input digits\n",MAXDIGITS);
printf("Enter value 1: ");
scanf("%s",&instring1);
printf("Enter value 2: ");
scanf("%s",&instring2);


samadd(instring1,instring2, outaddarray);


if(outaddarray[0]==1){printf("1");}
for(i=1;outaddarray[i]!=ENDMARK;i++)
	{
   	if(outaddarray[i]==DECMARK){printf(".");}
   	else printf("%d",outaddarray[i]);
   	}
printf("\nFinished\n\r");
return 0;
}