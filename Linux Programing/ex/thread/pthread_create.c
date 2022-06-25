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
}

int main(int arg, char **argv){
    pthread_t thread;
    pthread_create(&thread,NULL,thread_one,NULL);
/*     while(1){
        sleep(2);
        printf("primary thread exit!\n");
    } */
    printf("任意exit都会导致所有线程退出！\n");
    sleep(10);
    exit(0);
}