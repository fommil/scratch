/*
Sam Halliday
10226982
Physics level 3 Project
Ion Traps

This program recieves 3 numbers and finds a parabola to fit these
values, it then calculates the maximum (or minimum) value of the parabola.
*/

#include <stdio.h>

main()
{
float y1,y2,y3,a,b,c;
printf("\rEnter a value for y1: ");
scanf("%f",&y1);
printf("\rEnter a value for y2: ");
scanf("%f",&y2);
printf("\rEnter a value for y3: ");
scanf("%f",&y3);
a = -(y1/2) + y2 - (y3/2);
if(((y1>y2)&&(y2>y3))||((y3>y2)&&(y2>y1))){printf("\nCannot find peak with these values!!\nAny Key to Exit");}
else if(a==0) {printf("\nStraight Line!\nAny Key to Exit");}
else
    {
    printf("\n\rY(x) = -ax%c - 2abx - ab%c + c\n\r(-1,%g), (0,%g),(1,%g)\n\n\r",178,178,y1,y2,y3);
    printf("a = %g\n\r",a);
    b = (y3-y1) / (4*a);
    printf("b = %g\n\r",b);
    c = y2 + a*b*b;
    printf("Peak of Parabola = %g\n\r",c);
    printf("\tY(x) = %gx%c + %gx + %g\n\n\rBy Sam Halliday\n\r",-a,178,2*a*b, c-a*b*b);} return 0; }
