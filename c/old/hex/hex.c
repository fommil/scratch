/* This is SamHex at VERSION 1 (V1.02).
Record of Updates;
	V1.01 - Added date and time to exit

Implementing 
	Adding ability to place a simple bitmap picture file on exit

Problems to fix:
	- Output is on new line, would prefer same line output.
	- New screens for menu options and convertor parts.
*/

#include <stdio.h>
#include <ctype.h>
#include <time.h>

bitmap_load()
{

}

datetime()
{
time_t now;
time(&now);
printf("Current Date and Time is %s",asctime(localtime(&now)));
}

main()
{
unsigned char samhex_title[]={32,219,'\0'};
int z, loginum;
char c[2], *c_ptr=c, test;
printf("Welcome to SamHex.\n");
intro:	test=0;
	printf("To convert Hexadecimals to Decimals press '1'\nTo convert Decimals to Hexadecimals press '2'\n'x' to exit.\n");
	scanf("%s",c);
	switch (*c_ptr)
{	case 'x': 	break;
	case '1': 	printf("Enter Hexadecimal (x to exit):\nHex\tDecimal\n");
			for(;test!='x';){scanf("%X",&z);test=getchar();loginum=isalpha(test);
				if(loginum==0){printf("\t%d\n",z);}
				else if(test!='x'){printf("\aNot a Hexadecimal!\n");}}
			goto intro;
	case '2': 	printf("Enter Decimal (x to exit):\nDecimal\tHex\n");
			for(;test!='x';){scanf("%d",&z);test=getchar();loginum=isalpha(test);		
				if(loginum==0){printf("\t%X\n",z);}
				else if(test!='x'){printf("\aNot a Decimal!\n");}}
			goto intro;	
	default: 	printf("Not an option.\n\n");
			goto intro;
}
datetime();
printf("%s\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVersion 1.00\nWritten on C by Sam Halliday on 3rd October 2000\nThis program is free.\n\n\n\n",samhex_title);
return 0;}
