#include <stdio.h>
main()
{
unsigned char i;
for(i=33;i<127;i++){printf("%d\t%c\n\r",i,i);}
for(i=161;i<255;i++){printf("%d\t%c\n\r",i,i);}
return 0;
}
