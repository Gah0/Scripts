#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
//

union semum{
	int val;
	int sum_num;
	struct semid_ds *buf;
};

void mutex_lock(int semid, int num){
	struct sembuf sembuf2 = {0,-1,0};
	sembuf.sum_num = num;
	semop(semid,&sembuf,1);
}

void mutex_unlock(int semid, int num){
	struct sembuf sembuf2 = {0,1,0};
	sembuf.sum_num = num;
	semop(semid,&sembuf,1);
}

int main(int argc, char **argv){
	int semid = 0;
	union semun val;

	semid = semget(IPC_PRIVATE,4,IPC_CREAT|0600);//创建四个信号量
	if (semid < 0){
		printf("error");
		exit (0);
	}

	printf("sem%d:%d\n",semctl(semid,0,GETVAL));
	
	if(fork()){
	
		mutex_lock(semid,0);
		
		int i;
		for(i = 0;i<10;i++){
			printf("AABBCCDD\n");
			sleep(1);
		}
		
		mutex_unlock(semid,0);
		
		wait(NULL);
	}else{
	
		mutex_lock(semid,0);
		
		int i;
		for(i=0;i<10;i++){
			printf("11223344\n");
			sleep(1);
		}
		
		mutex_unlock(semid,0);
	}

	semop(semid,&sembuf,1);//设置第0个信号为1
	semctl(semid,IPC_RMID,0);//删除信号量
	
	return 0;
}
