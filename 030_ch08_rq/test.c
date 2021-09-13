#include <stdio.h>
#include <stdlib.h>

double d = 3.14159;
int * p = (int *)&d;
*p = 42;
printf("%f\n", d);
