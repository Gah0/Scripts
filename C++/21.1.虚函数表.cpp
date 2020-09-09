class Vector_container: public container{ //container是vector_container的基类。vector_container派生类是container
//Vector_container是子类   container是超类    基类和派生类的使用通常称为继承(inheritance)
    public:
        Vector_container(int s):v(s){} 


        /*vbtl指针指向这三个函数*/
        ~Vector_container() {}    //析构函数

        double &operator[](int i)override {  
            return v[i];
        }
        int size() const override{
            return v.size();
        }
        /*vbtl指针指向这三个函数*/

        private:
            Vector v;
}


/*vbtl能确保对象能被正确使用。
效率不会超过25%
*/



Vector_container     vbtl:
[]    ---->         []      ->       ~Vector_container() {}  
------              -----
v                   []      ->      Vector_container::operator[]()
                    -----
                    []       ->     ~Vector_container() {}  
