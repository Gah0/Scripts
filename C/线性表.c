#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define Maxsize 10
#define LISTINCREMENT 2

typedef struct
{
    int *elem;
    int length;
}sqlist;

int main (){
    sqlist sql;
    int i,e,input,sq;
    int err=0;

    do{
	printf("请输入小键盘数字操作\n");
	printf("(1)创建链表\n(2)添加数字到链条\n(3)从链条删除数字\n(4)查找数字\n(5)输出sqlist\n");
    scanf("%d",&input);

        switch(input){
            case 1:
                printf("创建链表");
                sq = createlist(&sql);
                if(sq != 0)
                    printf("创建不成功，表长为%d\n", sq);
                else
                    printf("创建成功，表长为%d\n", sq);
                break;
            case 2:
                printf("请输入你要添加的位置和数字:");
                scanf("%d,%d",&i,&e);
                sq = listinsert(&sql,i,e);
                if(sq == err){
                    printf("添加%d不成功\n",sq);
                    }
                else{
                    printf("成功添加%d\n",sq);
                }
                break;

            case 3:
                printf("请输入你要删除的数字:");
                scanf("%d,%d",&i,&e);
                sq = listdelete(&sql,i,e);
                if(sq == err){
                    printf("删除不成功\n");
                }else{
                    printf("成功删除%d\n",sq);
                }
                break;

            case 4:
                printf("请输入你要查找的数字\n");
                scanf("%d",&e);
                sq = locateelem(&sql,e);
                printf("你的数字在第%d个,错误会返回0\n",sq);
                break;

            case 5:
                displaysql(&sql);
                break;

            default:
				printf("没有此功能！\n");
				break;
        }
    }while(1);
    return 0;
}

int createlist(sqlist *sql){
    int i;

    sql->elem = (int *)malloc(Maxsize * sizeof(int));
    if(!sql->elem){
        printf("内存分配失败\n");
    }
    sql->length = 0;

    return sql->length;
}

int locateelem(sqlist *sql,int elem){
    int *p;
    int i=1;

    p = sql->elem;

    while(i<sql->length&&(*p++)!=elem)//时间复杂度为O(n)  平均比较次数为n+1/2
    {
        ++i;
    }
    if(i<=sql->length)
        return i;
    else
        return 0;
}

int listinsert(sqlist *sql, int i, int e){//顺序表存在，当1<i<length+1时，在第i个位置之前插入新数据e，然后length+1
    int j=0;
    int err=0;

    if(i<1||i>sql->length+1){
        return err;
    }

    //如果储存空间满了
    //堆小了，多申请2增量sizeof(int)
    if(sql->length == Maxsize){
        sql->elem = (int *)realloc(sql->elem, (Maxsize + LISTINCREMENT) * sizeof(int));
    }

    if(!sql->elem){
        printf("%d\n",sql->elem);
        return -1;
    }

    if(i <= sql->length)
        for (j=sql->length-1; j>=i-1; j--)
        {
            sql->elem[j+1]=sql->elem[j];//元素后移
        }
    //在i位置插入元素e
    sql->elem[i-1]=e;
    //表长+1
    sql->length++;

    return e;
}//在长度为n的线性表中插入一个元素所需移动数据元素的平均次数是  E= 求和（n+1）i=1 =n/2;
//平均时间复杂度为O（n）

int listdelete(sqlist *sql,int i,int e){
    int j;
    int err = 0;

    if(i<1||i>sql->length||sql->length == 0)
    {
        return err;
    }
    //把删除元素存入e中
    e = sql->elem[i-1];
    for (j=i;j<=sql->length;j++)
    {
        sql->elem[j-1]=sql->elem[j];
    }
    sql->length--;
    return e;
}

int displaysql(sqlist *sql){
    for (int i=0;i<sql->length;i++) {
        printf("%d\t\n", sql->elem[i]);
    }
}
