/*编程,有1020个西瓜,第一天卖出一半多两个,以后每天卖剩下的一半多两个,问几 天后能卖完
 *
 *
 *
 *
*/

#include "stdio.h"
int main(){
    int i,a=1020;

    for (i=1;i<a;i++){
        a=a-(a/2+2);
    }
    printf("能卖%d次",i);
    return 0;
}
