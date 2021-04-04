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

	int msgid = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
	if(msgid<0){
		return -1;
	}

	int fpid=fork();
	
	if(fpid>0){
		//msg queue 1->2->(1)->(2)
		//      bonjour->ohayo->nihao->hello
		msg.mtype = 1;
		strcpy(msg.buf,"Bonjour");
		printf("father pid:%d\n",getpid());
		len = sizeof(struct MSG);
		msgsnd(msgid,&msg,sizeof(len),0);

		strcpy(msg.buf,"nihao");
		len = sizeof(struct MSG);
		msgsnd(msgid,&msg,sizeof(len),0);

		msg.mtype = 2;
		strcpy(msg.buf,"ohayo");
		len = sizeof(struct MSG);
		msgsnd(msgid,&msg,sizeof(len),0);

		strcpy(msg.buf,"hello");
		len = sizeof(struct MSG);
		msgsnd(msgid,&msg,sizeof(len),0);

		wait(NULL);

		/*msgctl(int msqid, int cmd, struct msqid_ds *buf)*/
		msgctl(msgid,IPC_RMID,NULL);
	}else{

		sleep(0.5);
		printf("------\n");
		printf("son pid:%d\n",getpid());
		len = sizeof(struct MSG);
		//msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
		msgrcv(msgid,&msg,sizeof(len),1,0);
		printf("son rec:%s\n",msg.buf);

		printf("son pid:%d\n",getpid());
		len = sizeof(struct MSG);
		msgrcv(msgid,&msg,sizeof(len),2,0);
		printf("son rec:%s\n",msg.buf);

		printf("son pid:%d\n",getpid());
		len = sizeof(struct MSG);
		msgrcv(msgid,&msg,sizeof(len),1,0);
		printf("son rec:%s\n",msg.buf);
	}
	return 0;
}