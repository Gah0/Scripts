#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <time.h>
#include <sys/select.h>

#include  <termios.h>

int UART_Recv(int fd,char *rcv_buf, int data_len, int timeout){
    fd_set fs_read;
    int fs_sel,cnt;
    //int timeout;
    struct timeval time;
    time.tv_sec=timeout/1000;
    time.tv_usec = timeout%1000*1000;

    FD_ZERO(&fs_read);//cleanup port rec
    FD_SET(fd,&fs_read);//set port rec


    fs_sel= select(fd,&fs_read,NULL,NULL,&time);
    if(fs_sel){
        cnt = read(fd,rcv_buf,100);
    	return cnt;
    }
}

int UART_Send(int fd,char *send_buf,int data_len){
	ssize_t ret = 0;
	ret = write(fd,send_buf,data_len);
	if(ret == data_len){
		printf("send data is \"%s \n\"",send_buf);
	}else{
		tcflush(fd,TCOFLUSH);
		return -1;
	}

}



int main(void){
    int fd,cnt,len;
    char buf[101];

    buf[100]='\0';
    fd = open("/dev/ttyS6",O_RDWR|O_NOCTTY| O_NDELAY);
    if(fcntl(fd,F_SETFL,0)<0){
        printf("fcntl failed\n");
    }else{
        printf("fcntl=%d\n",fcntl(fd,F_SETFL,0));
    }


    fcntl(fd,F_SETFL,0);//port block
    while(1){
    	tcflush(fd,TCIOFLUSH);//清掉port cache
    	len=UART_Recv(fd,buf ,99,10000);
    
	    if(len>0){
	    	printf("read %d from ",cnt);
	    	printf("%s\n",buf);
	    	UART_Send(fd,buf,len);
	    	len = 0;
	    }
	}


    close(fd);
}