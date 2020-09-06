



/*
类
struct 和 class太大区别，struct是public的class

class常用于数据分离。
保持数据对用户不可见。
public定义接口，private成员用过接口访问。
*/
class Vector(){
    public:
        //在类的公共处构造一个vector,  : 后面初始化vector成员
        Vector(int s) : elem{new double[s]}, sz{s}{ } 

        /*定义operator和size接口*/
        double &operator [](int i){//
            return elem[i];
        }

        int size(){
            return sz;
        }
/*
 * private只能通过接口访问，私有的
*/
    private:
        double *elem;
        int sz;
}

//定义一个新变量，与上一节vector_init()功能一样。
//与类同名的函数叫构造函数（constructor）。
//编译器会初始化对象使用构造函数
//自定义构造函数可以消除类变量未初始化问题。
Vector v(6);


double read_and_sum(int s){
    Vector v(s);//创建一个包含s的元素的向量

    for(int i=0;i!=v.size();++i){
        cin>> v.[i];
    }

    double sum = 0;

    for(int i=0;i!=v.size();++i){
        sum += v[i];
    }

    return sum;
}


/*struct A的继承*/

struct A{}；
 
    class B : A{};    //private继承
 
    struct C : B{}；  //public继承