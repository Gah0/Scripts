#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <time.h>

int main(void){
    int fd;
    char buf[101];
    int cnt;
    buf[100]='\0';
    fd = open("/dev/ttyS7",O_RDWR|O_NOCTTY| O_NDELAY);
    if(fcntl(fd,F_SETFL,0)<0){
        //zusai
    }else{
        printf("fcntl=%d\n",fcntl(fd,F_SETFL,0));
    }
    cnt = read(fd,buf,100);


    printf("read %d",cnt);
    printf("%s\n",buf);
    close(fd);
}