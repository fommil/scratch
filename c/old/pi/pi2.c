/* Calculation of pi to 32372 decimal digits */
/* Size of program: 152 characters */
/* After Dik T. Winter, CWI Amsterdam */

#include <stdio.h>

main(){
register signed a=1e4,b,c=113316,d,e,g,h,i;
signed f[113316];
for(;b=c,c-=14;i=printf("%04d",e+d/a),e=d%a)
while(g=--b*2)d=h*b+a*(i?f[b]:a/5),h=d/--g,f[b]=d-g*h;
return 0;}

