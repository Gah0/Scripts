#include "10.1.分别编译.h" //获得接口
#include <cmath>

double sqrt_sum(double& v){
    double sum = 0;
    for(int i=0;i!=v.size();++i){
        sum+=sqrt_sum(v[i]);
    }
    return sum;
}

