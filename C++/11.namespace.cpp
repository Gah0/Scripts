/*
 * 声明一个整体以及他们的名字不会与其他名字冲突
 * 
 * */

namespace My_code{
    class complex{
        //..
    };

    complex sqrt(complex);
    int main();
}

int My_code::main(){
    complex z{1,2};
    auto z2 = sqrt(z);
    std:cout << "{" << z2.real() << ',' << z2.image() << "}\n";
    //...
}


//namespace 简化名字，对std使用using后，
//using namespace std；
//就不需要写std::cout;
//cout << 
//cin >>

void my_code(vector<int>& x,vector<int>& y){
    using std::swap;
    //
    swap(x,y)
;    other::swap(x,y);
//
}