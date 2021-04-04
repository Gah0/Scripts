#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 3

struct student{
	int num;
	char name;
	int size;
	char sex;
	float score;
	struct student *next;
};

int main(int argc, char **argv){

	struct student stu[SIZE];
	int fd = 0;
	int cnt = 0;
	int i;

	char *path = "/home/gah0/桌面/code/lesson/cat.txt";
	char buf[BUFSIZE]="Pitbull，305 Mr.worldwide";

	for(int i = 0 ; i<SIZE; i++){
		printf("input num:\n");
		scanf("%d",&stus[i].num);
		fflush(NULL);

		printf("input name:\n");
		scanf("%s",stu[i].name)
		fflush(NULL);

		scanf("%s",&stu[i].size);

		printf("input name:\n");
		scanf("%s",&stu[i].size);
		fflush(NULL);

		printf("input name:\n");
		scanf("%s",&stu[i].score);
		fflush(NULL);
	}

	fd = open(path, O_CREAT | O_WRONLY, 0777);
	if(fd < 0){
		printf("open error");
	}


	cnt = write(fd, buf, strlen(buf));
	if(cnt == -1){
		printf("read failed\n");
	}



	cnt = read(fd, buf, 1024);
	buf[cnt] = '\0';

	printf("read cnt :: %d :: %s\n",cnt,buf);
	printf("name:%s num:%d sex:%c score:%f\n",zs.name.zs.num,
									zs.sex,zs.score);
	close(fd);
	return 0;
}
