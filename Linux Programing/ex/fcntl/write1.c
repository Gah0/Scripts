#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int cnt;
    int *str= "hello,world!";

    fd=open("/dev/ttyS7",O_RDWR|O_CREAT,0766);
    cnt=write(fd,str,12);

    printf("%d bytes written!\n",cnt);
    close(fd);
}