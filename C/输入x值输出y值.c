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
