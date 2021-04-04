#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>

#define SIZE 1024

int main(int argc, char **argv){
    int fd;
    char buf[SIZE];
    int cnt;

    fd = open("fifo",O_RDONLY);
	if(fd < 0){
		printf("open error");
	}

    while(1){
        cnt= read(fd,buf,SIZE);
        buf[cnt] = '\0';
        if(cnt == -1){
		    printf("read failed\n");
	    }
        printf("(receive)>:%s\n",buf);
    }

    close(fd);
    return 0;
}