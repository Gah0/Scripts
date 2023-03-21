#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include "timer.h"

#define COUNT_SEC 5
#define COUNT_USEC 0

int timerflag = 0;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond;


static void Timer_Test(int sig)
{
    printf("Timer is on\n");
    pthread_cond_signal(&cond);
}

/*Initialize timer*/
static void Init_timer(struct itimerval *tick)
{
    int ret;
    memset(tick, 0, sizeof(struct itimerval));

    /*initialize it_value*/
    tick->it_value.tv_sec = COUNT_SEC;
    tick->it_value.tv_usec = COUNT_USEC;

    /*initialize it_interval*/
    tick->it_interval.tv_sec = COUNT_SEC;
    tick->it_interval.tv_usec = COUNT_USEC;

    return;
}

int timer_init(void)
{
    int ret = 0;
    struct itimerval tick;

    signal(SIGALRM, Timer_Test);

    Init_timer(&tick);

    ret = setitimer(ITIMER_REAL, &tick, NULL);
    if(ret < 0)
    {
        perror("setitimer");
        return -1;
    }

    for (;;);  //此处循环使主函数不结束。主函数结束后定时函数也将结束。

    return 0;
}
