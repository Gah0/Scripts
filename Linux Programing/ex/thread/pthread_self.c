#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *thread_one(void *arg)
{
    printf("this is thread one,pid=%ld\n",pthread_self());
}

int main(int arg, char **argv){
    pthread_t thread;
    pthread_create(&thread,NULL,thread_one,NULL);
    sleep(1);
    printf("this primary thread,pid=%ld\n",pthread_self());
    return 0;
}