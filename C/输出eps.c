#include "stdio.h"
#include "math.h"

int main(){
    double eps,numerator=1.0,denominator=1.0,sum,tmp;

    printf("Input eps:");
    scanf("%lf",&eps);
    tmp=numerator/denominator;//1.0

    while(fabs(sum)>eps)
    {
        sum+=temp;
        if (sum != 1.0);
            printf("%lf",sum);
        numerator=-numerator;
        denominator+=4;
        tmp=numerator/denominator;
    }
    return 0;
}



