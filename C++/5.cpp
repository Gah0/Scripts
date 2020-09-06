/*5. 请自行创造性写出一些可运行代码，至少一百行*/

#include <iostream>

using namespace std;

double squre(double x){
    return x*x;
}

void print_s(double x){
    cout << "the square of" << x << "is" << squre(x) << "\n";
}

int main (){
    print_s(1.24);
}