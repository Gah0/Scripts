#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>


int main (int argc, char **argv){

	int shid = 0;
	char *ptr;
	char str []= "hellp world";
	
	//create the share memory
	//the key value of size rounded  IPC_PRIVATE
	shid = shmget (IPC_PRIVATE, 1024, 0660 | IPC_CREAT);
	if(shid  == -1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILUER);
	}
	
	
	if(fork()){
		//attaches memory and call the process
		ptr = (char*)shmat(shid, NULL, 0);
		
		//(src,dst,sizeof) copy ptr to str
		strncpy(ptr, str, strlen(str)+1);
		
		printf("father pid :: %d\n",getpid());
		
		//block the process
		wait(NULL);
		if(wait == -1){
			printf("wait failed");
			return 0;
		}
		//(pid,cmd,*buf)
		shmctl(shid,IPC_RMID,NULL);
		
	}else{
		usleep(1000);
		
		//(id,page-aligned addr,flag)
		ptr = (char *)shmat (shid,NULL,0);
		if(ptr == -1 ){
        	fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        	exit(EXIT_FAILURE);
		}
		
		printf("son rec :: %s\n",ptr);
		printf("son pid :: %d\n",getpid());
	}
	return 0;
}

