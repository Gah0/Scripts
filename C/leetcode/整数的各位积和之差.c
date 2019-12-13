#include "stdio.h"

int math_multi(int n);
int math_plus(int n);
int diff_value(int sum, int multi);
int new_n;
int diff;

int diff_value(int sum, int multi) {
    diff = multi - sum ;
    return (diff);
}

int math_multi (int n){
    int multi;

    do
    {
     new_n=n%10;
     multi *= new_n;
    }while(n);

    return multi;
}

int math_plus (int n){
    int sum;

    do
    {
     new_n=n%10;
     sum += new_n;
    }while(n);

    return sum;
}

int main (int sum, int multi,int diff){
    int n;

    printf("请输入数字：");
    scanf("%d",&n);

    math_plus(n);
    math_multi(n);

    printf("数字之和为%d\n数字之积为%d\n积和之差为%d\n", sum, multi, diff);
    printf("\n");
}
