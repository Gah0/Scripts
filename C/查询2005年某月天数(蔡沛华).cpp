/*完善上课时交的，这次完善了2月为29天的bug
  anthor:蔡沛华
*/
#include <stdio.h>
#include "ctype.h"
int main()
{
	int a[7]={1,3,5,7,8,10,12};
	int i,k,month,day;
	printf("input the month of 2005: ");
top:
	scanf("%d",&month);
	if(isalpha(month))
	{
		printf("input the month of 2005 again: ");
        goto top;
	}
	else if(month==2)
    {
        k=3;
    }
	else
	{
	for(i=0;i<7;i++)
	{
		if(month==a[i])
		{
			k=1;
			break;
		}
		else
		{
			k=2;
		}
	}
	}
	switch(k)
	{
	case 1:day=31;break;
	case 2:day=30;break;
	case 3:day=29;
	}
	printf("2005年%d月有%d天",month,day);
	}
