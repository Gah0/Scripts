/*3．编程，输入学生成绩登记表中的信息（如下表所示），
按成绩从低到高排序后再输出成绩表，并求计算总分。*/

#include "stdio.h"

int i;

struct data{
    int num;
    char name;
    int score;
    }s[10];

int quick_sort (int s[i], int left, int right){

    int temp;
    int j = left,k = right;
    int pivot;

    pivot = s[left + right / 2];

    while (i <= j)
    {
        //找到左边大于基准点的元素
        while(s[j] < pivot)
        {
            j++;
        }

        while(s[k] < pivot)
        {
            k--;
        }

        if(j <= k)
        {
            temp = s[j];
            s[j] = s[k];
            s[k] = temp;
            j++;
            k--;
        }
    }
    if (left < k){
        quick_sort(s, left, k);
        }
    if (j < right){
        quick_sort(s, j, right);
        }
}

int main (void){
    int i,length;

    for (i=0; i<10; i++){
        scanf("%d %s %d",&s[i].num, &s[i].name, &s[i].score);
        printf("already save %d,please input the next %d data",i,i++);
    }

    length = sizeof(s) / sizeof(s[0]);

    quick_sort(s, 0, length-1);

    for(i=0; i< length; i++)
    {
        printf("%4d %s %4d\n",s[i].num, s[i].name, s[i]);
    }
    return 0;
}
