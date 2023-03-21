#include <iostream>

using namespace std;
//将d1d2d3初始化为2.3
doubele d1 = 2.3;
double d2 {2.3};
doubel d3 = {2.3};
//标量为双精度浮点数的复数。
complex <double> z = 1;
complex <double> z2 {d1,d2};
complex <double> z3 = {d1,d2};
//=和{}是可选的

//整数向量
vector <int> v {1,2,3,4,5,6};


auto b = true;
auto ch = 'x';
auto i = 123;
auto z = sqrt(y);
看
//bool 类型
auto bb {true};

void sqrt(double){
    return i*i;
}

void pront(int){
    std::cout<<"ahsiofsa"<<endl
}

vector <int> vec;

struct Record {
    string name;
}

void fct(int arg){
    string motto{"Who dare wins"};
    auto p = new Record{"Hume"};
}

int *func1(){
    int a[10]={1,2,3};
    return a;
}

int &func2(){
    int x = 66;
    return x;
}

//生命周期在局部作用域

int main (){
    int *p = func1();
    int p2 = func2();

    cout << p2 <<endl;
    for(int i = 0; i<10;i++){
        cout << p[i] << " ";
    cout << endl;
    return 0;
   }
}


#include <iostream>

using namespace std;

int i=0;

int main (){
    int i =66;
    cout << i << endl;
    return 0;
}


constexpr int dmv =17;
int var = 17;
const doubel sqv = sqrt(var);

double sum(const vector <double>&);

vector <double> v {1.2,3.4,4.5};
const double s1 = sum(v);
constexpr double s2 = sum(v); 