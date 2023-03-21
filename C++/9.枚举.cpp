#incldue <iostream>

using namespace std;

enum class Color {red,blue,green};
enum class Traffic_light {green,yellow,read};

Color col= Color::red;
Traffic_light light = Traffic_light::red;


枚举通常用在规模小的数值集合。
提高代码可读性，降低出错风险。


怎么引用枚举呢？
Color只能引用Color类型
Color z = Color::red;

Color x = Color{5};
Color y {6}


Traffic_light &operator++(Traffic_light &t){
    switch(t){
        case Traffic_light::green:
            return Traffic_light::yellow;
        case Traffic_light::yellow:
            return Traffic_light::read;
        case Traffic_light::read:
            return Traffic_light::green;
    }
}

Traffic_light next = ++light;