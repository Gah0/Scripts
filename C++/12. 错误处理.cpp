#include <iostream>


//越界处理
//假设越界是一种错误，从中恢复需要由vector实现者检测意图越界的访问并通知user。使用者就可以采取适当的措施。
//例如这样。

double& Vector::operator[](int i){
    if(i<0||size()<=i){
        throw out_of_range{"Vector::operator[]"};//out of range在标准库中。
    return elem[i];
    }

}

//不变式
//throw可以将程序的控制权从某个直接或间接调用Vector::operator[]()的函转移到 lenth_error异常处理。
//length_error是标准库函数
Vector::vector(int s){
    if(s<0){
        throw length_error{"Vector constructor:negative size"};
    }
    elem = new double[s];
    sz=s();
}

//try可以处理某段代码的异常，良好的设计应该减少try块。
void test(){
    try{
        Vector(-27);//试图用-27访问
    }
    catch (std::lenth_error& err){
        //处理负数大小
        cerr << err.what << '\n';
    }
    catch (std::bad_alloc& err){
        //处理内存耗尽
        cerr << err.what << '\n';
    }
}


//一个永远不会抛出异常的函数声明成noexcept
//如果仍有异常，此时会调用std::terminate();
void sue(int sz) noexcept{
    Vector v(sz);
    iota(&v[0],&v[sz],1);
}



