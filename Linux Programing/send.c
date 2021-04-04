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

	len = sizeof(struct MSG)-sizeof(long)+sizeof(1);
	printf("father pid:%d\n",getpid());
	//msg queue 1->2->(1)->(2)
	//      bonjour->ohayo->nihao->hello
	msg.mtype = 1;
	strcpy(msg.buf,"Bonjour");
	msgsnd(msgid,&msg,sizeof(len),0);

	strcpy(msg.buf,"nihao");
	msgsnd(msgid,&msg,sizeof(len),0);

	msg.mtype = 2;
	strcpy(msg.buf,"ohayo");
	msgsnd(msgid,&msg,sizeof(len),0);

	strcpy(msg.buf,"hello");
	msgsnd(msgid,&msg,sizeof(len),0);

	sleep(5);

	/*msgctl(int msqid, int cmd, struct msqid_ds *buf)*/
//	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}