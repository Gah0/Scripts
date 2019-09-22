#include "stdio.h"

#include <math.h>

int main()
{
	float area;
	int length,radius,y=2;

	printf("press a int value for radius:");

	if (scanf("%d",&radius) != 1) 
		printf("it's not a integer number!\n");
	else
		length =  y * 3.14159 * radius;
		area = 3.14159 * pow(radius,y);
		printf("length:%.8f\narea:%.8f\n",length,area);
}