/*
This program adds 2 integers together. But it teaches the computer to count in
decimal (in a way) and therefore only has a maximum number of digits given by
the memory space dedicated to the program. This limit is given by MAXDIGITS
in the defines. This is comparable to the incomplete 10 digits which 32-bit
numbers limit, and combats the problem that double numbers are only accurate
to 6 digits despite the raised power. Should be easily changed to decimal
addition, or to addition in hexadeciaml or octal. A future version attains to do
decimal point addition. Future plans are also to build a library of math
functions which add, subtract, divide, multiply, raise to the power and square
root with the same limitations, also with decimal points and with negative
values included. This will be in the form of a function library where string
arrays of numbers and special symbols are passed to it.

Allowed values in string arrays:			Character 	Represents
                                         0-9       The Number Value
                                          .        Decimal Point Position !!NOT ON THIS VERSION!!
                                          ,        Decimal Point Position !!NOT ON THIS VERSION!!
                                          -        Negative Value !!NOT ON THIS VERSION!!
                                          +        Positive Value (not necessary) !!NOT ON THIS VERSION!!
													  NULL      End of Numbers (essential)

Format for the number arrays:			    Value		Reserved For
                                         0-9     	Associated Value
                                         255       End of Numbers in Array Marker
                                         254       Decimal Point Marker !!NOT ON THIS VERSION!!
                                         253			Negative Value !!NOT ON THIS VERSION!!
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXDIGITS 100
#define ENDMARK 255

main()
{
static unsigned char array1[MAXDIGITS+1],array2[MAXDIGITS+1],addarray[MAXDIGITS+2];
static unsigned char digit,carry,larger,logizero;
static unsigned char string[MAXDIGITS+2];
static unsigned long int i,j,k,ea1,ea2,eaa,errorcount,temp1,temp2;
printf("Sam Halliday, GNU Public License\nThis program adds 2 integer values together, limited to %d input digits\ncompared to the incomplete 10 digits of 32 bit processing\n",MAXDIGITS);
//-----------------------------------------------------------------------------
//Input values
printf("Enter value one (integer): ");
scanf("%s",&string);
for(i=0,logizero=0;logizero==0;i++) //This loop removes unnecessary preceeding zeros
	{if(string[i]!=48)logizero=1;}
i--;
for(j=0;(string[i]!='\0');i++,j++)
	{if((string[i]>57)||(string[i]<48)){errorcount++;printf("ERROR \"%c\" is not a valid number!",string[i]);printf("\nExiting\n");return errorcount;}
	array1[j]=string[i]-48;}
ea1=j-1;
array1[j]=ENDMARK;

//for(i=0;i<MAXDIGITS+2;i++){string[i]=0;} //TO ZERO STRING ARRAY

printf("Enter value two (integer): ");
scanf("%s",&string);
for(i=0,logizero=0;logizero==0;i++) //This loop removes unnecessary preceeding zeros
	{if(string[i]!=48)logizero=1;}
for(i--,j=0;(string[i]!='\0');i++,j++)
	{if((string[i]>57)||(string[i]<48)){errorcount++;printf("ERROR \"%c\" is not a valid number!",string[i]);printf("\nExiting\n");return errorcount;}
   array2[j]=string[i]-48;}
ea2=j-1;
array2[j]=ENDMARK;

if(ea1>ea2){larger=1;eaa=ea1+1;}
else if(ea1<ea2){larger=2;eaa=ea2+1;}
else{larger=0;eaa=ea1+1;}
addarray[eaa+1]=ENDMARK;
carry=0;
//-----------------------------------------------------------------------------
//This is the counting bit, the core of the program
i=ea1;
j=ea2;
k=eaa;
while(((i+1)>0)&&((j+1)>0)&&((k+1)>0))
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
   while((i+1)>0)
   {temp1=array1[i];
   digit=temp1+carry;
   if(digit>9){addarray[k]=digit-10;carry=1;}
   else{addarray[k]=digit;carry=0;}
   i--;k--;
   }}
else if(larger==2)
	{
   for(;(j+1)>0;j--,k--)
   {temp2=array2[j];
   digit=temp2+carry;
   if(digit>9){addarray[k]=digit-10;carry=1;}
   else{addarray[k]=digit;carry=0;}
   }}
addarray[0]=carry;
//-----------------------------------------------------------------------------
//Print out part
for(i=0;array1[i]!=ENDMARK;i++)
	{
   printf("%u",array1[i]);
   }
printf("\n+\n");
for(i=0;array2[i]!=ENDMARK;i++)
	{
   printf("%u",array2[i]);
   }
printf("\n=\n");
if(addarray[0]==1){printf("1");}
for(i=1;addarray[i]!=ENDMARK;i++)
	{
   printf("%u",addarray[i]);
   }
printf("\nFinished\n");
return 0;
}
