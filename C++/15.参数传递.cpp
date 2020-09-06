void test(Vector<int>& v,vector<int>& rv){
    v[1]=99;
    rv[2]=66;
}

void int main(){
    vector fib={1,2,3,5,8,13,21};
    test(fib,fib);
    cout<<fib[1]<<' '<<fib[2]<<'\n';
    //daying 2 66;
}



void print(int value,int base=10);

print(x,16);


class Vector{
    public:
        double& operator[](int i){return elem[i]};
    private:
        double *elem;
};

//错误写法
int &bad(){
    int x;
    return x;
}



//引用大量信息的函数传递

Matrix operator+(const Martrix x,const Matrix&y){
    Matrix res;
    //....
    return res;
}

直接调用
Matrix m1,m2;
Matrix m3 = m1+m2; 


//


Matrix *add(const Matrix& x,const Matrix& y){
    Matrix *p =new Matrix;
    //....
    p=x+y;
    return p;
}

然后调用
Matrix m1,m2;
Matrix *m3= add (m1,m2);
delete m3;


