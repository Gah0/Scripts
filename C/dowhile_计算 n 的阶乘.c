/*
编程，计算 n 的阶乘（n！）,n 的取值在 1~10 之间。分别使用 while、do...while 和 for 语句 实现。
1*2*3*4
*/
#include <stdio.h>

int main(){
    long int i=1,num,result=1;
    printf("press a number(<10):");
    scanf("%d",&num);


    do{
        result*=i;
        i++;
    }
    while(i<=num);

    printf("%d的阶乘是%d",num,result);
    return 0;
}

