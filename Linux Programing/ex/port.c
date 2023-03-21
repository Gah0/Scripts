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

#include <string.h>

int setOpt(int fd, int nspeed, int nBits, int nParity, int nStop){
	int flag;
	struct termios newtio, oldtio;
	if(tcgetattr(fd,&oldtio)!=0){//失败
		return -1;
	}
	memset(&newtio,0,sizeof(newtio));
	newtio.c_cflag = CLOCAL| CREAD;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]= 1;
	newtio.c_cflag &=~CSIZE;

	switch(nBits){
		case 8:
				newtio.c_cflag |= CS8;//修改数据位为8bit
				break;
		case 7:
				newtio.c_cflag |= CS7;//修改数据位为7bit
				break;
		default:
				return -1;
	}

	switch(nParity){
		case 'o':
			break;
		case 'O':
			newtio.c_cflag |=(PARODD|PARENB);
			newtio.c_iflag |=(INPCK|ISTRIP);
			break;
		case 'e':
			break;
		case 'E':
			newtio.c_cflag &= ~PARENB;
			newtio.c_cflag&=~PARODD;
			newtio.c_iflag |=(INPCK|ISTRIP);
			break;
		case 'n':
			break;
		case 'N':
			newtio.c_cflag &= ~PARENB;
			break;
		default:
			return -1;
	}

	switch(nStop){
		case 1:
			newtio.c_cflag &= ~CSTOPB;
			break;
		case 2:
			newtio.c_cflag |= CSTOPB;//
			break;
		default:
			return -1;
	}

	switch(nspeed){
		case 9600:
			cfsetospeed(&newtio,B9600);
			cfsetispeed(&newtio,B9600);
			break;
		case 115200:
			cfsetispeed(&newtio,B115200);
			cfsetospeed(&newtio,B115200);
			break;
		default:
			return -1;
	}

	tcflush(fd,TCIFLUSH);
	flag=tcsetattr(fd,TCSANOW,&newtio);
	if (flag!=0){
		return -1;
	}
	return 0;
}

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
    fd = open("/dev/ttyS1",O_RDWR|O_NOCTTY| O_NDELAY);
    if(fcntl(fd,F_SETFL,0)<0){
        printf("fcntl failed\n");
    }else{
        printf("fcntl=%d\n",fcntl(fd,F_SETFL,0));
    }


    fcntl(fd,F_SETFL,0);//port block
    setOpt(fd,115200,8,'N',1);


    while(1){
    	tcflush(fd,TCIOFLUSH);
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