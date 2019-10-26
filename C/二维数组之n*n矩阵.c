/*编程，（二维数组）求一个 n*n 矩阵二条对角线元素之和。*/

#include "stdio.h"


void main(){
    int n,i,j,h,l,sum=0;

    printf("请输入矩阵行列数，用空格隔开：");
    scanf("%d %d",&h,&l);
    printf("请依次输入矩阵中的数值：\n");

    for ( i = 0; i < h; i++){
        for ( j = 0; j < l; j++){
            scanf("%d",&a[h][l]);
        }
    }

    for ( i = 0; i < h; i++)
        for (j = 0; j < l; j++)
        {
            a[l][h]=a[h][l];//矩阵倒置
        }

    sum = a[h][l]+a[l][h];
    printf("结果为：\n",sum);
}