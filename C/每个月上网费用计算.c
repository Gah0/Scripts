/*
编一程序每个月根据每个月上网时间计算上网费用,计算方法如下:
          |30元（<=10 小时）
费用--=    |每小时3元(10-50小时)
         |每小时2.5元(>50小时)
要求当输入每月上网小时数,显示该月总的上网费用
*/


#include "stdio.h"

void main()
{
	int hour;
 float fee;

	printf("请输入你的上网小时数:")
	scanf("%f",&hour);

	if(hour<=10){
		fee = 30
		goto label;
		}

	if(10<hour<=50){
		fee = 3 * hour;
		goto label;
		}

	if(hour>50){
		fee = 2.5 * hour;
		goto label;
		}

	label: printf("你这个月网费是:%f",fee);
}
