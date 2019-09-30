/*编程，输入一行字符，分别统计输入了多少个字母、数字、空格和其他字符。*/

#include "stdio.h"

int main(){
    int other=0,num=0,blank=0,Eng=0;
    printf("输入你喜欢的一个句子，统计各类字符：\n");
    while(getchar()!='\n')
    {
        if (getchar > 'a' && getchar <'z'){
            ++Eng;
        }
        else if (getchar > '0' && getchar < '9'){
            num -= -1;
        }
        else if (getchar==' '){
            blank -= -1;
        }
        else{
            other -= -1;
        }
    }

    printf("你总共输入了%d个字母,%d个数字,%d个空格,%d个其他字符！\n",Eng,num,blank,other);
    return 0;
}
