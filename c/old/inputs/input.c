#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
char temp[50];
float test;

printf("Enter a double: ");
scanf("%g",&test);
//test=atof(temp);
printf("%g\n",test);
printf("%g\n",fabs(test));
return 0;
}
