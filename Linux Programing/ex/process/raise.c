#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_catchfunc(int){
    printf("捕获信号\n");
}

int main(){
    int ret;
    signal(SIGINT,sig_catchfunc);

    printf("start a signal\n");

    ret = raise(SIGINT);
    if(ret!=0){
        printf("错误，不能生成sigint信号\n");
        exit(0);
    }
    printf("退出...\n");
    return 0;
}