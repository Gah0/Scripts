#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>


#define SIZE 1024

struct MSG{
	long mtype;
	char buf[SIZE];
};


int main (){
	struct MSG msg;
	int len;

	int msgid = msgget((key_t)1235, 0600 | IPC_CREAT);
	if(msgid<0){
		return -1;
	}

	printf("son pid:%d\n",getpid());

	len = sizeof(struct MSG)-sizeof(long)+sizeof(1);
	//msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
	msgrcv(msgid,&msg,sizeof(len),1,0);
	printf("son rec:%s\n",msg.buf);

	msgrcv(msgid,&msg,sizeof(len),2,0);
	printf("son rec:%s\n",msg.buf);

	msgrcv(msgid,&msg,sizeof(len),1,0);
	printf("son rec:%s\n",msg.buf);

	msgrcv(msgid,&msg,sizeof(len),2,0);
	printf("son rec:%s\n",msg.buf);

	msgctl(msgid,IPC_RMID,NULL);
	return 0;
}