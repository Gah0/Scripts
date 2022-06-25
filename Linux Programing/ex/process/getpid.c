#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>


int main(){
    pid_t my_pid,parent_pid;
    uid_t my_uid,my_euid;
    gid_t my_gid,my_egid;

    my_pid = getpid();
    parent_pid=getppid();
    my_uid=getuid();
    my_gid=getgid();
    my_egid =getegid();

    printf("process id:%d\n",my_pid);
    printf("parent id:%d\n",parent_pid);
    printf("User id:%d\n",my_uid);
    printf("Effective user id:%d\n",my_euid);
    printf("group id:%id\n",my_gid);

    for(;;);
    return 0;
}