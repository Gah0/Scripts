/*1.输入 2 个整数,求两数的平方和并输出。*/
#include "stdio.h"
#include "math.h"

int main() {
	int answer,value1,value2,i,y=2;
	printf("Press two numbers to calculate sum of squares(Separated by spaces)");
	scanf("%d %d",&value1,&value2);
	while(i<100)
	{
	if (value1-(int)value1>=0&&value2-(int)value2>=0){
		printf("Please enter integer");
		i += 1;
		continue;
		}
	else
		answer = value1 + value2;
		printf("the answer is %f",pow(answer,y));
		i += 1;
		break;
	}
	return 0;
}