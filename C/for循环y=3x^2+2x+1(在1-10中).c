#include "stdio.h"


int main(){
    int x,i,y;

    for(i=1;i<10;i++)
    {
        for(x=1;x<10;x++)
        {
            y=3*x*x+2*x+1;
            printf("y=%d\n",y);
        }
        return 0;
    }
}

