/*编程，（一维字符数组）在一个指定的字符串中删除指定的字符，并输出该字符串。*/

#include "stdio.h"

#define N 128

int main (){
	char str1[N],str2[N];
	char cat;
	int i,j=0;

	printf("请输入一组字符串：");
	get(str1);
	printf("请输入要删除的字符：")
	scanf("%c",&cat);
		for(i=0; str1[i]!='\0';i++){
			if(str1[i]!=cat){
				str2[j+1]=str1[i];
			}
		}
	str2[j] = '\0';
	printf("是这个吗：%s\n",str2);
}