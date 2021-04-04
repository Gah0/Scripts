#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>

int main (int argc, char **argv){
    int pid;
    int fd;
    char buf[1024]="";

    fd = open("./fifo",O_WRONLY);

    while(1){
        printf("(Enter to send):>");
        scanf("%s",buf);

        write(fd,&buf,strlen(buf));
    }
    close(fd);
    return 0;
}