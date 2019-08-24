
#include<stdio.h>

int main(){
	
	int cm,foot,inch;
	float m;

	printf("请输入厘米数：");
 
 foot = cm/0.3048/100;
 inch = (cm/0.3048-foot)*12;
 
	scanf("%d",&cm);
	printf("%d %d",foot,inch);
}
