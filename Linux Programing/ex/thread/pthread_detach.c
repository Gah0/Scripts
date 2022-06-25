#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void *thread_one(void *arg)
{
    long t2;
    long result = 0;
/*     while(1)
    {
        printf("this is thead one\n");
        sleep(2);
    }  */
    sleep(2);
    t2=(long)arg;
    for(int i=0;i<t2;i++){
        result = result +i;
    }
    printf("thread one arg is %ld pthread_exit!\n",t2);
    pthread_exit((void *)result); 
}

int main(int arg, char **argv){
    pthread_t thread;
    int res,rc;
    long t=110;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //分离态
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    rc=pthread_create(&thread,&attr,thread_one,(void *)t);
    pthread_attr_destroy(&attr);
//    pthread_detach(thread);
    sleep(2);
    //printf("thread one cancel\n");

    void *thread_result;
    res = pthread_join(thread,&thread_result);
    if(res){
        printf("error!\n");
    }

    long result2 =(long)thread_result;
    printf("this result is %ld\n",result2);
/*     pthread_cancel(thread);
    while(1){
        sleep(2);
        printf("primary thread!\n");
    } */
    //printf("任意exit都会导致所有线程退出！\n");
    //sleep(10);
    //exit(0);
}