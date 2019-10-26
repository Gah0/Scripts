/*编程，将 1－200 中所有 11 的倍数存放到一个一维数组中，并输出*/
#include "stdio.h"

void main (){
    int i,num;
    char a[i+1];//定义可变长数

    printf("请输入整数的个数");
    scanf("%d",&num);

    printf("请输入n个整数，用空格隔开");
    
    for (int i = 0; i < num; ++i)
    {
        scanf("%hhd",&a[i]);
    }

    for (int i = num; i>0; i--)
    {
        printf("%d",a[i]);
    }
}




/*http://bbs.bccn.net/thread-444964-1-1.html
#include <stdio.h>
#include <malloc.h>

int main()
{
    int n=0;
    printf("请输入n个整数中的n是:");
    scanf("%d",&n);
    int* p;
    int i=0;
    int m=0;
    p=(int*)malloc(n*sizeof(int));  //因不知输入的数据量 所以不能类似int a[n]的声明
    printf("请输入一组数据 容量为%d:\n",n);
    for(;i<n;i++)
    {
        scanf("%d",&m);
        *(p+i)=m;
    }
    //对于输入的数据 进行首尾交换
    int tmp;
    i=0;
    m=n-1;
    while(i<=m)
    {
        tmp=*(p+i);
        *(p+i)=*(p+m);
        *(p+m)=tmp;
        i++;
        m--;
    }
    //对逆置后的数据进行输出
    i=0;
    for(;i<n;i++)
    {
        printf("%d ",*(p+i));
    }
    free(p);释放p指针
    return 0;
}

*/