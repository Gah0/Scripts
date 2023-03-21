#include <iostream>

using namespace std;

//enum是特殊的struct
enum Type {ptr,num};

struct Entry{
    string name; //b标准库类型
    Type t;
    Node *p;
    int i;
}
/*
如果t是str，使用p
如果t是num，使用i
*/
void f(Entry *pe){
    if(pe->t==num){
        cout<<pe->i;
    }else{
        cout<<pe->p;
    }
}



