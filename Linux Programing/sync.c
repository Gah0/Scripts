#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

union semum{
	int val;
	struct semid_ds *buf;
};


void sync_lock(int semid,int num){
	struct sembuf sembuf = {0,-1,0};
	sembuf.sem_num = num;
	semop(semid,&sembuf,1);
}

void sync_unlock(int semid,int num){
	struct sembuf sembuf = {0,1,0};
	sembuf.sem_num = num;
	semop(semid,&sembuf,1);
}

int main(int argc, char **argv){
	int semid = 0;
	union semum arg;
	
	semid = semget(IPC_PRIVATE,4,IPC_CREAT|0600);//创建四个信号量
	if (semid < 0){
		printf("error");
		exit (0);
	}

	/*semctl(id, num, command,arg)
		semaphore control operations */
	arg.val = 3;
	semctl(semid,0,SETVAL,arg);
	
	arg.val = 5;
	semctl(semid,1,SETVAL,arg);

	arg.val = 6;
	semctl(semid,2,SETVAL,arg);
	
	arg.val = 7;
	semctl(semid,3,SETVAL,arg);
	
	for(int i = 0;i<3;i++){
	/* GETVAL    Return the value of semval for the semnum-th semaphore of the
                 set.  The calling process must have read  permission  on  the
                 semaphore set.*/
		printf("sem%d:%d\n",i,semctl(semid,i,GETVAL));//获取信号量arg，并打印
		sleep(1);
	}
	
	semctl(semid,IPC_RMID,0);//删除信号量
	return 0;
}
