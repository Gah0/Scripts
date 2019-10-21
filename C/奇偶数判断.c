#include "stdio.h"
#include "conio.h"
#include "iostream.h"

int main (){
    int num [];
    int even,odd,num;
    char c;

    printf("请输入你想输入的数字，按Y结束输入并计算和\n");
    scanf("%d",&num);

    for(i=0; i<num; i++){
    if(num%2==0)
        even += a[i]
        print("你输入的值%d已放入数组，按Y求奇数和/偶数和\n",even);
    else
        odd += a[i]
        print("你输入的值%d已放入数组，按Y求奇数和/偶数和\n",odd);

    if(getch =='^Z')
        break;
    }

    printf("偶数和%d,奇数和%d,偶数和-奇数和的结果为%d\n",even,odd,even-odd);
    return 0;
}
