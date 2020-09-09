#include <iostream>

using namespace std;

/*
 * 用户自定义类型，具体类，抽象类，类层次。
 * 
 * 
 */

class complex
{
//构造变量
    double re,im;
//以下为构造函数
    public:
        complex(double r,double i):re{r},im{i}{}//两个标量构造复数
        complex(double r): re{r},im{0}{}        //一个标量
        complex():re{0},im{0}{}默认复数{0，0}    //0+0i

        double real() const{  //返回实数
            return re;
        }

        void real(double d){
            re=d;
        }

        double imag() const{   //返回虚数
            return im;
        }

        void imag(double d){
            im = d;
        }

        //构造函数
        complex& operator+=(complex z){
            re += z.re;  //通过类里面构造的函数进行名字引用
            im += z.im;
            return *this;
        }
}

//如何调用class类函数，直接调用传参即可
//非const成员无法调用const对象
complex z = {1,0}

const complex cz = {1,3};
z=cz;//向一个非const函数赋值。

double x = z.real();
complex::real();//是一个成员函数



在外部不需要访问complex类，可以直接调用
complex operator+(complex a,complex b){
    return a+=b;
}

//直接调用类定义里面的real()返回复数实数re值，imag()返回复数i虚数值，并返回到a，并return。
complex operator-(complex a){
    return {-a.real(),-a.imag()};
}

bool operator==(complex a, complex b){
    return a.real()==b.real() && a.imag()==b.imag();
}

complex sqrt(complex){
    //...
}

//类的使用方法
void f(complex z){
    complex a{2.3};
    comlex b{1/a};
    complex c {a+z*complex{1，2.3}}

    //if(c != b)
        c= -(b/a)+2*b
}

