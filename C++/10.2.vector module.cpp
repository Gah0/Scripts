/*
 * 定义一个名为Vector的模块，他导出类Vector及其所有成员函数和非成员函数的size()
 * 
 * 模块和头文件用法差不多，风格可以混合。模块只会编译一遍。
 */

module;

export module Vector;

export module Vector{
    public:
        Vector(int s);
        double& operator[](int s);
        int size();
    private:
        double *elem;
        int sz;
};


Vector::Vector(int s)
    ：elem(new double[s]),sz{s}
{

}


double& Vector::operator[](int i){
    return elem[i];
}

int Vector::size(){
    return sz;
}

export int size(const Vector& v){
    return v.size();
}