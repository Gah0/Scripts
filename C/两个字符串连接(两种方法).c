/*.编程，（非一维数组）输入两个任意的字符串，编写程序实现两个字符串的链接。（不
能使用 strcat()函数）*/

#include "stdio.h"
#include "string.h"
#include "stdib.h"

#define N 65535

void catstring(char *st1,char *st2)
{
	int i=0,j=0
	for(i=0;str1[i]!='\0';i++){
		for(j=0;str2[j]!='\0';j++)
			{
				str1[i++]=str2[j]
			}
	}
	str1[i]'\0' //结束

}

int main (){
	char *str1 = NULL，*str2 = NULL;

#ifdef CONFIG_APPLICATION_LEN
	char* str1;
	char* str2;
	int len1,len2;
#else
	char str1[128],str2[128];//固定长度，可能会溢出
#endif

	printf("input the first string:")
	scanf("%s",len1);
	str1 = (char *)malloc((len1+1)*sizeof(char)*32);

	if(str1 == NULL){
		printf("分配内存失败\n");
		exit(1)
	}

#ifdef CONFIG_APPLICATION_LEN
	free(str1);//释放
#endif

	printf("input the third string:")
	scanf("%s",len2);
	str2 = (char *)malloc((len2+1)*sizeof(char)*32);

	if(str2 == NULL){
		printf("分配内存失败\n");
		exit(1)
	}

#ifdef CONFIG_APPLICATION_LEN
	free(str2);//释放
#endif


	catstring(str1,str2);
	//strcat(str1,str2);

    return 0;
}


