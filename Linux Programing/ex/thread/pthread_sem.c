#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void *thread_func(void *msg);
sem_t sem;

#define MSG_SIZE 512


int main(){
    int res = -1;
    pthread_t thread;
    void *thread_result = NULL;
    char msg[MSG_SIZE];
    res = sem_init(&sem,0,0);
    if(res==-1){
        perror("semaphore intitialization failed\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread,NULL,thread_func,msg);
    if(res!=0){
        perror("pthread_create failed\n");
        exit(EXIT_FAILURE);
    }
    //输入信息，以输入end结束，由于fget会把回车\n读入，所以判断时就变成了”end\n“
    printf("Input some text. Enter 'end' to finish...\n");
    while(strcmp("end\n",msg)!=0){
        fgets(msg,MSG_SIZE,stdin);
        sem_post(&sem);//+1
    }
    printf("waiting for thread to finish...\n");
    res = pthread_join(thread,&thread_result);
    if(res!=0){
        perror("pthread_join failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined \n");
    sem_destroy(&sem);
    exit(EXIT_SUCCESS);


}

void *thread_func(void *msg){
    sem_wait(&sem);
    char *ptr=(char *)msg;

    while(strcmp("end\n",ptr)!=0){
        int i =0;
        for(;ptr[i]='\0';++i){
            if(ptr[i]>='a'&&ptr[i]<='z'){
                ptr[i]-='a'-'A';
            }
        }
        printf("YOu input %d characters\n",i-1);
        printf("to uppercase:%s\n",ptr);
        sem_wait(&sem);
    }
    pthread_exit(NULL);
}