#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

void *thread_one(void *arg)
{
    long t2;
    long result = 0;
    while(1){

        fprintf(stderr,"%c",(char*)arg);
        for(int i=0;i<100000;i++){
            for(int j=0;j<1000;j++);{
            }
        }
    }


}

int main(int arg, char **argv){
    pthread_t thread;
    int res1,res2,rc;
    long t=110;

    pthread_attr_t attr1,attr2,attr3;
    struct sched_param param1,param2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    //分离态
   // pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
    
    pthread_attr_setschedpolicy(&attr1,SCHED_RR);
    pthread_attr_setschedpolicy(&attr2,SCHED_RR);
    pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
    param1.sched_priority=1;
    param2.sched_priority=1;

    pthread_attr_setschedparam(&attr1,&param1);
    pthread_attr_setschedparam(&attr2,&param2);
    rc1=pthread_create(&thread1,&attr1,thread_one,(void *)"1");
    rc2=pthread_create(&thread2,&attr2,thread_one,(void *)"2");
    rc3=pthread_create(&thread3,NULL,thread_one,(void *)"3");
    pthread_attr_destroy(&attr1);//destroy后无法join，print error.
    pthread_attr_destroy(&attr2);
//    pthread_detach(thread);
    sleep(2);
    //printf("thread one cancel\n");

    void *thread_result;
    res1 = pthread_join(thread,&thread_result);
    if(res1){
        printf("error!\n");
    }
    void *thread_result;
    res2 = pthread_join(thread,&thread_result);
    if(res2){
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