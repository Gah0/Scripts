#
# 如果已知英制长度的英尺foot和英寸inch的值，那么对应的米是(foot+inch/12)×0.3048。现在，如果用户输入的是厘米数，那么对应英制长度的英尺和英寸是多少呢？别忘了1英尺等于12英寸。
#

#include<stdio.h>

int main(){
	
	int cellmeter,foot,inch;
	float meter;

	printf("请输入厘米数：");
 
 foot = cm/0.3048/100;
 inch = (cm/0.3048-foot)*12;
 
	scanf("%d",&cellmeter);
	printf("%d %d",foot,inch);
}
