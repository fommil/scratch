#include <stdio.h>
main()
{
unsigned char i;
printf("  %d nul %d %c   %d %c   %d %c   %d %c   %d %c   %d %c   %d bel %d \\b  %d \\t\n ",0,1,1,2,2,3,3,4,4,5,5,6,6,7,8,9);
for(i=10;i<23;i=i+13)
	{
   printf("%d lf %d %c  %d %c  %d \\n %d %c  %d %c  %d %c  %d %c  %d %c  %d %c  %d %c  %d %c  %d %c\n",i,i+1,i+1,i+2,i+2,i+3,i+4,i+4,i+5,i+5,i+6,i+6,i+7,i+7,i+8,i+8,i+9,i+9,i+10,i+10,i+11,i+11,i+12,i+12);
   }
for(i=23;i<36;i=i+13)
	{
   printf(" %0d %c  %0d %c  %0d %c  %0d UP %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c\n",i,i,i+1,i+1,i+2,i+2,i+3,i+4,i+4,i+5,i+5,i+6,i+6,i+7,i+7,i+8,i+8,i+9,i+9,i+10,i+10,i+11,i+11,i+12,i+12);
   }
for(i=36;i<88;i=i+13)
	{
   printf(" %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c\n",i,i,i+1,i+1,i+2,i+2,i+3,i+3,i+4,i+4,i+5,i+5,i+6,i+6,i+7,i+7,i+8,i+8,i+9,i+9,i+10,i+10,i+11,i+11,i+12,i+12);
   }
for(i=88;i<101;i=i+13)
	{
   printf(" %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c  %0d %c %0d %c\n",i,i,i+1,i+1,i+2,i+2,i+3,i+3,i+4,i+4,i+5,i+5,i+6,i+6,i+7,i+7,i+8,i+8,i+9,i+9,i+10,i+10,i+11,i+11,i+12,i+12);
   }
for(i=101;i<244;i=i+13)
	{
   printf("%0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c\n",i,i,i+1,i+1,i+2,i+2,i+3,i+3,i+4,i+4,i+5,i+5,i+6,i+6,i+7,i+7,i+8,i+8,i+9,i+9,i+10,i+10,i+11,i+11,i+12,i+12);
   }
printf("%0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d %c %0d EOF\n",244,244,245,245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255);
return 0;
}
