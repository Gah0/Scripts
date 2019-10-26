/*编程，将 1－200 中所有 11 的倍数存放到一个一维数组中，并输出*/
#include "stdio.h"

void main (){
    int s[200];
    int i,j;

    for (int i = 0; i < 200; ++i)
    {
        if(i%11==0)
            s[j]=i;
    }
    for (int i = 0; i < j; ++i)
    {
        printf("%d",s[i]);
    }
}