#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void sig_usr(int signum){
    if(signum == SIGUSR1){
        printf("SIGUSR1 received\n");
    }else if(signum == SIGUSR2){
        printf("SIGUSR2 received\n");
    }else{
        printf("signal %d received\n",signum);
    }
}

int main(void){
    char buf[512];
    int n,ret;

    struct sigaction sa_usr;
    sa_usr.sa_flags=0;
    sa_usr.sa_handler = sig_usr;//信号处理函数

    sigaction(SIGUSR1,&sa_usr,NULL);
    sigaction(SIGUSR2,&sa_usr,NULL);

    printf("My pid is %d\n",getpid());

    while(1){
        ret = read(STDIN_FILENO,buf,511);
        if((ret == -1)){
            if(errno == EINTR){
                printf("READ IS INTERRUPT NY SIGNAL\n");
            }
        }else{
            buf[n]='\0';
            printf("%d bytes read:%s\n",n,buf);
        }
    }
    return 0;
}