#include <iostream>

//container为operator，size提供接口


/*抽象类型
 * 特点是没有构造函数，因为没有数据需要初始化
 * 析构函数是virtual，抽象类常见接口。
*/
class container{
    public:
    virtual double& operator[](int) = 0;    //operator是抽象类
    virtual int size() const = 0;           //size是抽象类
    virtual Container(){}
};

/*container是派生类对象，必须定义这个函数
 * 抽象类徐亚通过引用或者指针来操控
*/
container *p = new Vector_container(10);

/*如何使用container
*/
void use(container &c){
    const int sz = c.size;//如果有一个类为其他类型实现了size接口，我们称为多态类型
    for(int i =0 ;i!=z;i++){
        cout<<c[i]<<'\n'
    }
}

/*抽象类只实现了接口，未提供实现，为了令cntainer有用，我们必须实现一个定义了接口所需函数的容器*/
/*container没有构造函数，毕竟没有数据初始化*/
/*如果一个类为其他一些类提供接口*/
/*多态类型*/

//Vector_container派生自container
class Vector_container: public container{ //container是vector_container的基类。vector_container派生类是container
//Vector_container是子类   container是超类    基类和派生类的使用通常称为继承(inheritance)
    public:
        Vector_container(int s):v(s){} 
        ~Vector_container() {}    //析构函数，覆盖了基类的析构函数~container。一般会引式调用他。

        double &operator[](int i)override {  /*override显式，令编译器能捕捉函数拼写错误，函数可以覆盖使用*/
            return v[i];
        }
        int size() const override{
            return v.size();
        }

    private:
        Vector v;
}


/*派生类从基类继承成员
基类和派生类的使用通常被称为继承*/

/*如何使用抽象函数呢*/

void g(){
    Vector_container vc(10);//21.虚函数。虚函数表头是Vector_container,这样才能use(vc)才能调用operator
    //写入十个数据
    for(int i;i<10;++i){
        cin>>i;
    }
    use(vc);
}

class List_container : public Container{
    public:
        List_container(){}
        List_container(initializer_list<double> il) : ld{il} {}
        ~List_container(){}   

        double &operator[](int i) override;
        int size() const override {
            return ld.size();
        }

    private:
        std::list<double> ld;
}

double& List_container::operator[](int i)
{
    for (auto & x:ld){
        if(i=0)
            return x;
        --i;
    }
    throw out_of_range("List container");
}

void h(){
    List_container lc = {1,2,3,4,5,6,7,8,9};
    use(lc);//use(&container)
}

