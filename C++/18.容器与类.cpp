#include <iostream>

/* 具体类型（concrete type）
*/
class Vector{
    public:
        Vector(int s): elem{new double[s]},sz{s}//构造函数
        {
            for(int i = 0;i!=s;i++){
                elem[i]=0;
            }
        }
    
    //析构函数，在析构函数中释放他们的技术被称为RAII，避免在一般代码分配内存，隐藏在行为良好的抽象实现内部。避免了裸delete和裸new更不易出错，更不易资源泄露。。
    Vector(){ 
        delete[] elem; 
    }

    double& operator[](int i);
    int size() const;

    private:
        double *elem;
        int sz;
};


/*如何使用上面的容器呢？
 * 
 */
void fct(int n)
{
        Vector v(n);
        //使用v
        {
            Vector v2(2*n);
            //使用v和v2
        }//v2销毁
        //使用v
}//v销毁



/*初始化容器
 *
 * 
 */

class Vector
{
    public：
        Vector(std::initalizer_list<double>);
        //..
        void push_back(double);
}

Vector read(istream& is){
    Vector v;
    for(double d; is>>d)
        v.push_back(d);
    return v;
}

从read()写入数据到容器v
Vector v = read(cin);



/*
 * 
 * */
Vector::Vector(std::initializer_list<double> lst)
    :elem{new double[lst.size()]},sz{static_cast<int>(lst.size())}
{
    copy(lst.begin(),lst.end(),elem);
}
Vector v1 = {1,2,3,4,5}
Vector v2 = {1.23,3.45,6.7,8}


