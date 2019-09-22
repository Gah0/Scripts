/*
3、函数 y=f(x)可表示为:
      |2x+1 (x<0)
y=----|y=0	(x=0)
      |2x-1	(x>0)
编程实现输入一个 x 值,输出 y 值。
*/
#include "stdio.h" 

int main(){
	int x,y;
	printf("press a number:");
	scanf("%d",&x);
	if(x<0){
		y=2*x+1;
		goto Label;
		}
	if(x==0){
		y=0;
		goto Label;
		}
	if(x>0){
		y=2*x-1;
		goto Label;
		}
	Label:printf("answer:%d",y);
}