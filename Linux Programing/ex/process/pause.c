#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum){
    printf("捕获信号 %d，跳出...\n",signum);

}

int main(){
    signal(SIGINT,sig_handler);
    sleep(2);
    printf("before apuse\r\n");
    pause();
    printf("after pause\r\n");
}