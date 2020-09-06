#include "10.1.分别编译.h"
定义vector

//在头文件构造了容器函数之后，用标准化组件调用 “：：”调用容器，
Vector::Vector(int s)
    :elem{new double [s]},sz{s} //初始化成员
{

}

double& Vector::operator[](int i){
    return elem[i];
}

int Vector::size(){
    return sz;
}