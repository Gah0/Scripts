#include <stdio.h>
#include <ctype>

#define Maxsize 10;


typedef struct sqlist{
    int *elem;
    int length;
};


void main (){
    int ret,input;
    struct sqlist sql;
    printf("请输入一个数字：");
    scanf("%d",&input);

    if (isdigit(input)){
        sql.elem = int [Maxsize];
    }
    else {
        printf("请输入一个有效的数字！");
    }
}

void creatlist(struct sqlist *sql){
    int i;

    sql->elem = malloc(Maxsize * sizeof(int));
    if(!sql->elem){
        printf("内存分配失败");
        return ERROR;
    }
    sql->length=0;
    return OK;
}

void locateelem(struct sqlist *sql,int elem){
    int *p;
    int i=1;
    p=sql.elem;
    while(i<sql.length&&(*p++)!=elem)//时间复杂度为O(n)  平均比较次数为n+1/2
    {
        ++i;
    }
    if(i<=sql.length)
        return i;
    else
        return 0;
}

void listinsert(struct sqlist *sql, int i, int e){//顺序表存在，当1<i<length+1时，在第i个位置之前插入新数据e，然后length+1
    int *newsql;
    int j;

    if(i<1||i>sql->length+1)
        return ERROR;
    if(sql->length == Maxsize){//如果储存空间满了
        newsql=(int *)realloc((*sql).elem, 
            (Maxsize + LISTINCREMENT) * sizeof(int); //堆小了，多申请2增量sizeof(int)
        if(!newsql)
            printk("连续空间已满");
            return ERROR;
        sql->elem = newsql;
        sql->length = sql->Maxsize + LISTINCREMENT;
    }
    for(j=(sql->length)-1; j>=i-1; j--)
    {
        sql->elem[j+1]=sql->elem[j];//元素后移
    }
    sql->elem[i-1]=e;//在i位置插入元素e
    //表长+1
    ++sql->length;
    return OK;
}//在长度为n的线性表中插入一个元素所需移动数据元素的平均次数是  E= 求和（n+1）i=1 =n/2;
//平均时间复杂度为O（n）

void listdelete(struct sqlist *sql,int i,int e){
    int j;
    if(i<1||i>sql->length)
    {
        return ERROR;
    }
    //把删除元素存入e中
    e = sql->elem[i-1];
    for (j=i;j<sql->length;j++)
    {
        sql->elem[j-1]=sql->elem[j];
    }
    sql->length++;
    return e;
}
