#include <iostream.h>
#include <fstream.h>

main()
{
short i,ii;
unsigned char l,r,zero=0,top=255;
char filename[15]="ascii.txt";
ofstream outfile(filename, ios::binary);
for(ii=0;ii<256;ii++)
    {
    l=ii;
    for(i=0;i<256;i++){r=i;outfile<<zero<<l<<zero<<top<<zero<<r;}
    }
return 0;
}
