#include "stdio.h"
#include "math.h"

int main (){
    long long int i,j,k,l,n,m;
    printf("输入正整数的个数n：");
    scanf("%d",&n);
    printf("输入%d个正整数\n",n);
    for(j=0;j<=k;j++)
    {
            scanf("%d",&m);
            n=(long long int)sqrt((long double)m);//15
                for(i=2;i<=n;i++)
                {
                    if(m%i==0)
                        break;
                }
                    if(i>n){
                    printf("%d是一个素数!\n",m);
                }else{
                    printf("%d不是一个素数!\n",m);
                }
    }
    return 0;
}
