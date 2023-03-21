#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define EXPORT_PATH "/sys/class/gpio/export"
#define DP "/sys/class/gpio/gpio131/direction"
#define DEV_PATH "/sys/class/gpio/gpio131/value"
#define GPIO "131"
#define IN "in"
#define OUT "out"



int main(){
    int fd_dir,fd_dev,ret;
    char buf[10],direction[10],value[10];
    //echo 131 > /sys/class/gpio/export
    int fd_export=open(EXPORT_PATH,O_WRONLY);

    write(fd_export,GPIO,strlen(GPIO));
    printf("gpio131/ generated\n");


    //change DP in/out
    fd_dir=open(DP,O_RDWR);
    strcpy(buf,OUT);
    //echo "in" > sys/class/gpio/gpio131/value
    ret = write(fd_dir,buf,strlen(OUT));
    ret = read(fd_dir,direction,sizeof(direction));


    fd_dev=open(DEV_PATH,O_RDWR);
    ret = read(fd_dev,value,sizeof(value));
    printf("diretions is %s input value is %s\n",direction,value);

    while(1){
        write(fd_dev,"1",1);
        sleep(1);
        write(fd_dev,"0",1);
        sleep(1);
    }

}
