/*
 *10.神州行用户无月租费,话费每分钟 0.6 元,全球通用户月租费 50 元,话费每分钟 0. 4
 *元。输入一个月的通话时间,分别计算出两种方式的费用,判断哪一种合适。
 */


#include "stdio.h"

int main{
	float shenzhou_fee,global_fee;
	int min;
	printf("请输入你的通话时间:\n");
	scanf("%f",&min);

	shenzhou_fee = 0.6 * min;
	global_fee = 0.4 * min + 50;

	if (shenzhou_fee=global_fee)
	{
		printf("全球通和神州行都可以！");
	else if (shenzhou_fee>global_fee)
		printf("选择神州行更便宜");
	else
		printf("选择全球通更便宜");
	}
	return 0;
}