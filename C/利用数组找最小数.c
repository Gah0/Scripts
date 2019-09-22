/*4、编写一个程序,从 4 个整数中找出最小的数,并显示此数。*/
#include "stdio.h"

int main()
{	
	int i,num[4];
	float min=0.0;
	printf("分别输入4个整数，输出最小值:\n");
    for(i=0;i<4;i++)
    {
     scanf("%d",&num[i]);
    }
    min = num[0];
	for(i=1;i<4;i++)
	{
		if(num[i]<min)
			min=num[i];
	}
	printf("%f\n", min);
    return 0;
}
