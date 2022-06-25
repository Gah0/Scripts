#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_one(void *arg)
{
    while(1)
    {
        printf("this is thead one\n");
        sleep(2);
    } 
/*     sleep(10);
    printf("thread one pthread_exit!\n");
    ptherad_exit(NULL); */
}

int main(int arg, char **argv){
    pthread_t thread;
    pthread_create(&thread,NULL,thread_one,NULL);
    sleep(10);
    printf("thread one cancel\n");
    pthread_cancel(thread);
    while(1){
        sleep(2);
        printf("primary thread!\n");
    }
    //printf("任意exit都会导致所有线程退出！\n");
    //sleep(10);
    //exit(0);
}