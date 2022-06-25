#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
pthread_mutex_t lock;


void PrintHello(void *id){
    long tid;
    int i,j;
    tid = (long)id;

    while(1){
        sleep(2);
        pthread_mutex_lock(&lock);
        printf("It's thread #%ld beginning!\n",tid);
        for(int k=0;k<5;k++){
            printf("thread #%ld job %d printing \n",tid,k);
            for(i=0;i<100000;i++){
                for(j=0;j<6666;j++);
            }
        }
        printf("thread#%ld is over!\n",tid);
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc,char *argv[]){
    pthread_t threads[NUM_THREADS];
    long t;
    for(t=0;t<NUM_THREADS;t++){
        printf("In main: creating thread %ld\n",t);
        pthread_create(&threads[t],NULL,PrintHello,(void *)t);
    }
    pthread_mutex_init(&lock,NULL);
    while(1);
}