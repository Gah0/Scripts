#include "stdio.h"

int main(void)
{	
	int your_age,friend_age;
	printf("你的年龄:");
	scanf("%d",&your_age);
	printf("朋友的年龄:");
	scanf("%d",&friend_age);

	if(your_age>friend_age)
		printf("%d",your_age);
	else
		printf("%d",friend_age);

	return 0;

}
