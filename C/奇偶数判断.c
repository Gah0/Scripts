#include "stdio.h"
#include "conio.h"

int main (){
    int i,n,even,odd;
    char c;
    char num [n+1];//定义可变长数组
    char p = &num[n+1];

    printf("请输入你想输入的数字，按Y结束输入并计算和\n");
    scanf("%d",&num);

    for(i=0; i<num; i++){
        if(p%2==0){
            even += num[i];
            printf("你输入的值%d已放入数组，按Y求奇数和/偶数和\n",even);
        }
        else{
            odd += num[i];
            printf("你输入的值%d已放入数组，按Y求奇数和/偶数和\n",odd);
        }
    if(getch =='^Z')
        break;
    }

    printf("偶数和%d,奇数和%d,偶数和-奇数和的结果为%d\n",even,odd,even-odd);
    return 0;
}
