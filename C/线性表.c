#include "stdio.h"
#include <iostream.h>
using namespace std;

#define Maxsize 10

Typedef int ElemType;

typedef struct{
    ElemType *elem;
    int length; //表的长度。
}SqList;

ElemType init_list(SqList &L)
{
    L.elem = new ElemType [Maxsize];
    if(!L.elem)
        printf("Overflow on elem");
        return 0;
    L.length = 0;
    return 1;
}

ElemType list_create(SqList &L)
{
    int x,i=0;
    while(x>Maxsize)
    {
        if(L.length == Maxsize)
        {
            cout<<"顺序表满了"
            return 0;
        }
    cin>>x;
    L.elem[i++];
    L.length++;
    }
    return 1;
}

ElemType get_elem(SqList &L, int i, int &e)
{
    if(i<1||i>L.length)
        return false;
    
    e=L.elem[i-1];
    return 1;
}

ElemType locate_elem(SqList &L, int e)
{
    for(i=0;i<L.length;i++)
        if(L.elem[i] == e)
            return i+1;
    return -1;
}

ElemType insert_elem(SqList &L, int i, int e)
{
    int j=0;

    if(i<1||i>L.length+1)
        return false;

    if(L.length == Maxsize)
        return false;    

    for(int j=i;j<L.length;j++)
        L.elem[i+1]=L.elem[j]
        L.length++;
    
    return 1;
}

ElemType delete_elem(SqList &L, int i, int e)
{
    if(i<1 || i>L.Length)
        return false;

    e = L.elem[i-1];//把index为i的元素赋值给e   0123i5678
    for(int j=i;j<=L.length-1;j++)
        L.elem[j-1]=L.elem[j];//把index为5的j元素赋值给j的上一个位置
        L.length--;
}

