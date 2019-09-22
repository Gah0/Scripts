/*2. 输入一个圆半径(r)当 r>=0 时,计算并输出圆的面积和周长,否则,输出提示信息。*/

#include "stdio.h"
#include <math.h>

int main()
{
	float area;
	int length,radius,y=2;

	printf("press a int value for radius:");

	if (scanf("%d",&radius) < 0) 
		printf("Your value cannot be calculated as a circle\n");
	else
		length =  y * 3.14159 * radius;
		area = 3.14159 * pow(radius,y);
		printf("length:%.8f\narea:%.8f\n",length,area);
}