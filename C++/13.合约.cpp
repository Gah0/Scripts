#include <iostream>

double& Vector::operator[](int i){
    if(range_check && (i<0||size()<i))
        throw out_of_range{"Vector::operator[]"}
    return elem[i];
}


//标准库调试宏 assert()
void f(const char *p){
    assert(p!=nullptr);
}



