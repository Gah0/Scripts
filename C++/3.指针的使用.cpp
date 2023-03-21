#include <iostream>

using namespace std;

double *pd = nullptr;
Link<Record>*lst = nullptr;


int count(const char *p,char x){
    if(p==nullptr){
        return 0;
    }

    int count = 0;
    while(*p){
        if(*p==x){
            ++count;
        }
        ++p;
    }
    return count;
}

int main(){
    cout<<count()<<'\n';
}