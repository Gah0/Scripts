#include <iostream>

using namespace std;

struct Vector{
    int sz;//数目
    double *elem;//指向元素的指针
}

void vector_init(Vector &v,int s){
    v.elem = new double[s];//自由储存  分配一个数组
    v.sz = s;
}

double read_and_sum(int s){
    Vector v;
    vector_init(v,s);//给v分配s个元素

    for(int i = 0;i!=s;++i){
        cin>>v.elem[i]
    }

    double sum = 0;
    for(int i = 0;i!=s;++i){
        sum+=v.elem[i];
    }

    return sum;
}

//结构体访问方法，名字访问，引用访问，指针访问
void f(Vector v,Vector &rv, Vector *pv){
    int i1 = v.sz
    int i2 = rv.sz 
    int i3 = pv->sz
}

