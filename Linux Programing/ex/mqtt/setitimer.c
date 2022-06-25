#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>


#define  COUNT_SEC 1
#define  COUNT_USEC 0

int timerflag=0;

static void Timer_Test(){
    printf("This is a Test\n");
    timerflag=1;
}

static void init_timer(struct itimerval *tick){
    int ret;
    memset(tick,0,sizeof(struct itimerval));

    /*initialize it_value*/
    tick->it_value.tv_sec=COUNT_SEC;
    tick->it_value.tv_usec=COUNT_SEC;

    tick->it_interval.tv_sec=COUNT_SEC;
    tick->it_interval.tv_usec= COUNT_USEC;
    return ;
}

int main (){
    int ret=0;

    struct itimerval tick;
    signal(SIGALRM, Timer_Test);

    init_timer(&tick);

    ret = setitimer(ITIMER_REAL,&tick,NULL);
    if(ret <0)
    {
        perror("setitimer");
        return -1;
    }
    for(;;);
    return 0;
}