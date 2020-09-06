


#include <iostream>

using namespace std;

double sqrt(double);//接受一个double类型的数值，返回double类型数值

class Vector{
    public:
        Vector(int s);
        double &operator[](int i);
        int size();

    private:
        double *elem;//指向数值
        int sz;//长度
}

//不需要定义，这是标准函数sqrt
double sqrt(double d){
    return x*x;
}

//构造函数的定义
Vector::Vector(int s)
    :elem{new double[s],sz{s}
{

}

double& Vector：：operator[](int i){
    return elem[i];
}

int Vector::size(){
    return sz;
}