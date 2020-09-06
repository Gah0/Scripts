#include <iostream>

static_assert(4<=sizeof(int),"integers are too small");
//speed必须是常量
void f(double max_speed){
    constexpr double speed = 160.0/12*12;
    static_assert(speed<=sizeof(int),"integers are too small");
}

