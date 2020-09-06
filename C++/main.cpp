#include <iostream>

using namespace std;

auto x = 5;

double square();

int main(){
    cout<<"the square is "<< square()<<endl;
    return 0;
}

double square(){
    return x*x;
}