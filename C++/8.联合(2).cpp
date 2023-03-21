以上的情况是有p则不会有i，使用struct会浪费内存
我们使用联合
#include <iostream>

using namespace std;

union Value{
    Node *p;
    int i;
}

struct Entry {
    string name;
    Type t;
    Value v;
}

void f(Entry *pe){
    if(pe->t==num){
        cout<< pe->v.i;
    }else{
        cout<< pe->v.p;
    }
}