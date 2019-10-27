/*..编程（一维字符数组）从键盘输入一个不超过 30 个字符的字符串，存储到一个字符
数组中。将下标为奇数位置上的字符按顺序复制到另外一个字符数组中并输出。如：输入
“abcdefg”，则输出”bdf”。*/

#include "stdio.h"
#include "string.h"

int main (){
	int i,j=0;
	char str[31];
	char str2[31];

	gets(str);

	for (i=0; str[i]!='\0'; i++){
		if(i%2!=0){
			str2[j]=str[i];
			j++;
		}
	}
	str2[j] = '\0';
	puts(str2);
	return 0;
}