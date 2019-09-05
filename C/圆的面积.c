#include "stdio.h"

#include <math.h>

int main()
{
	float area;
	int radius,y=2;

	printf("press a int value for radius:");

	if (scanf("%d",&radius) != 1) 
		printf("it's not a int number!\n");
	else
		area= 3.14159 * pow(radius,y);
		printf("answer:%.8f\n",area);
}