/*
编程，计算 n 的阶乘（n！）,n 的取值在 1~10 之间。分别使用 while、do...while 和 for 语句 实现。
1*2*3*4
*/
#include <stdio.h>

int main(){
    long int num,i=1,result=1;
    printf("press a number(<10):");
    scanf("%d",&num);


    for(i=1;i<=num;i++){
        result*=i;
    }
    printf("%d的阶乘是%d",num,result);
    return 0;
}

