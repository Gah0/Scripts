#include iostream

class container{
    public:
    virtual double& operator[](int) = 0;    //operator是抽象类
    virtual int size() const = 0;           //size是抽象类
    virtual Container(){}
};

container是派生类对象，必须定义这个函数

container *p = new Vector_container(10);

如何使用container

void use(container &c){
    const int sz = c.size;
    for(int i =0 ;i!=z;i++){
        cout<<c[i]<<'\n'
    }
}