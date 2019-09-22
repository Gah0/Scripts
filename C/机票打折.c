/*6.输入机票原价(3 到 4 位的正整数,单位:元),再输入机票打折率(小数点后最多一
位数字)。编程计算打折后机票的实际价格(单位:元。计算结果要将个位数四舍五入到
十位数“元”)。输入只有一行两个数(两数间用一个空格分隔),第一个为整数,表示
机票原价,第二个整数或实数(如是实数,小数点后最多 1 位数字)表示打折率。*/
#include <stdio.h>

int main()
{
	int price,final_price,new_price,new_rate;
	float rate;
	printf("请输入原价和打折率（打折率用小数）");
	scanf("%d %f",&price,&rate);

	final_price = (int)(price * rate / 10)/10; //62.1

	if(final_price-(int)final_price>=0.5){
		final_price +=1;
		new_price = final_price * 10;
	}
	else{		
		new_price = (int)(final_price * 10);
	}
	printf("最终价格为：%d",new_price);
}