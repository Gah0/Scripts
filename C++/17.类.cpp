#include <iostream>

using namespace std;

/*
 * 用户自定义类型，具体类，抽象类，类层次。
 * 
 * 
 */

class complex
{
    double re,im;

    public:
        complex(double r,double i):re{r},im{i}{}//两个标量构造复数
        complex(double r): re{r},im{0}{}一个标量
        complex():re{0},im{0}{}默认复数{0，0} 0+0i

        double real() const{
            return re;
        }

        void real(double d){
            re=d;
        }

        double imag() const{
            return im;
        }

        void imag(double d){
            im = d;
        }

        complex& operator+=(complex z){
            re += z.re;
            im += z.im;
            return *this;
        }
}

//如何调用class类函数，直接调用传参即可
//非const成员无法调用const对象
complex z = {1,0}
const complex cz = {1,3};
z=cz;//向一个非const函数赋值。


complex operator+(complex a,complex b){
    return a+=b;
}

complex operator-(complex a){
    return {-a.real(),-a.imag()};
}

bool operator==(complex a, complex b){
    return a.real()==b.real() && a.imag()==b.imag();
}

complex sqrt(complex){
    //...
}

类
void f(complex z){
    complex a{2.3};
    comlex b{1/a};
}
