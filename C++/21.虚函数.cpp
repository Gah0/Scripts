class Vector_container: public container{ //container是vector_container的基类。vector_container派生类是container
//Vector_container是子类   container是超类    基类和派生类的使用通常称为继承(inheritance)
    public:
        Vector_container(int s):v(s){} 
        ~Vector_container() {}    //析构函数 //析构函数，覆盖了基类的析构函数~container。一般会引式调用他。

        double &operator[](int i)override {  /*override显式，令编译器能捕捉函数拼写错误，函数可以覆盖使用*/
            return v[i];
        }
        int size() const override{
            return v.size();
        }
        private:
            Vector v;
}

void use(Container &c)
{
    const int sz = c.size();
    for(int i = 0; i!=sz; ++i){
        cout<<c[i]<<'\n';
    }
}


/*当上一个20抽象类型的h调用use()时，必须调用Listcontainer的operator[]()*/
void h(){
    List_container lc = {1,2,3,4,5,6,7,8,9};
    use(lc);//use(&container) use可以在未知类实现的情况下工作。
}



/*当g()调用use()的时候，必须调用Vector——container的operator[]()*/
void g(){
    Vector_container vc(10);
    //写入十个数据
    use(vc);
}




