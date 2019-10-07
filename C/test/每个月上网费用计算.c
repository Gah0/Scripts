/*
编一程序每个月根据每个月上网时间计算上网费用,计算方法如下:
          |30元（<=10 小时）
费用--=    |每小时3元(10-50小时)
         |每小时2.5元(>50小时)
要求当输入每月上网小时数,显示该月总的上网费用
*/


#include "stdio.h"

struct Data
{
    int hour;
    float fee;
    char ch;
}data;

void main()
{
    struct Data *pt;
    pt = &data;
	printf("请输入你的上网小时数:");
	scanf("%f",(*pt).hour);

	if((*pt).hour<=10){
		(*pt).fee = 30;
		(*pt).ch=3;
		}

	if(10<(*pt).hour<=50){
		(*pt).fee = 3 * (*pt).hour;
		(*pt).ch=2;
		}

	if((*pt).hour>50){
		(*pt).fee = 2.5 * (*pt).hour;
		(*pt).ch=1;
		}

	switch((*pt).ch)
	{
        case 1 :printf("你这个月网费是:%f",pt->fee);
        case 2 :printf("你这个月网费是:%f",(*pt).fee);
        case 3 :printf("你这个月网费是:%f",pt->fee);
	}
	return 0;
}

