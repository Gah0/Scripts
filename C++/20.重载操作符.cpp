class person{
    private:
        int age;
    public:
        person(int a){
            this -> age = a;
        }
        inline bool operator == (const person &ps) const;
};


//实现方法如下：

inline bool person::operator==(const person &ps) const
{
    if(this -> age == ps.age)//
        return true;
    else
        return false; 
}


