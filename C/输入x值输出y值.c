/*5.有一函数当 x<0 时 y=1,当 x>0 时,y=3,当 x=0 时 y=5,编程,从键盘输入一个 x 值,输出 y 值。*/

#include "stdio.h"

int main(void)
{
	int x,y;
	scanf("%d",&x);

	if(x<0)
	{
		int y=1;
		goto Label;
	}

	if(x=0)
	{
		int y=5;
		goto Label;
	}

	if(x>0)
	{
		int y=3;
		goto Label;
	}
	Label: printf("y=%d\n",y);
	return 0;
}
