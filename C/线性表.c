//线性表

#include "stdio.h"

#define LIST_INIT_SIZE 10
#define LISTINCREMENT 2

typedef struct{
    elemtype *elem;
    int lenth;//4个字节
    int listsize;
}sqlist

int initlist(sqlist *L)
{
    //创建一个空的线性数据表
    L->elem=(elemtype* )malloc(LIST_INIT_SIZE* sizeof(elemtype));
    if(!L->elem)
        printf("overflow");
        exit 0;

    L->lenth=0;
    L->listsize=LIST_INIT_SIZE;
    printf("sucess!")
}


int LocateElem(sqlist L,elemtype e)
{
    elemtype *p;
    int i = 1;

    p = L.elem;

    while(i<L.lenth&&(*p++)!=e)
        i++;
    
    if(i<=L.lenth)
        return i;
    else
        return 0;
}

int listinsert(sqllist *L,int i,elemtype e)
{
    elemtype *newbase,*q,*p;
    int j;

    if(i<1||i>L->lenth+1)
        printf("error")

    if(L->lenth>=L->listsize)
    {
        //当前储存空间已满，增加分配
        newbase=(elemtype* )realloc((*L).elem)
            ((*L).listsize+LISTINCREMENT)*sizeof(elemtype))
        
        if(!newbase)
            printf("空间已满\n");
        
        L->elem=newbase;
        L->listsize=L->listsize+LISTINCREMENT;

    }

    for(j=(L->lenth)-1; j>=i-1; j--)
        L->elem[j+1]=L->elem[j];
    
    L->elem[i-1]=e
    ++L->lenth;
    printf("insert OK");
    
}

int lisadelete(sqlist *L,int i, elemtype e)
{
    elemtype *p, *q;
    int j;

    if(i<1||i>L>lenth)
        printf("error")
    
    e=L->elem[i-1];

    for(j=i; j<L->lenth; j++)
        L->elem[j-1]=L->elem[j];
        L->lenth++;
        return e
}

