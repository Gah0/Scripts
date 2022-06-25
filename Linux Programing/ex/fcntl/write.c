#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 3

struct student{
	int num;
	char name[10];
	char sex;
	float score;
};

int main(int argc, char **argv){

	struct student stu[SIZE];

	int fd = 0;
	int cnt = 0;
	int i;

	char *path = "/home/gah0/桌面/code/lesson/student.txt";

	for(i = 0 ; i<SIZE; i++){
		printf("input num:\n");
		scanf("%d",&stu[i].num);

		printf("input name:\n");
		scanf("%s",stu[i].name);
		
		scanf("%c",&stu[i].sex);
		printf("input sex:\n");
		scanf("%c",&stu[i].sex);

		printf("input score:\n");
		scanf("%f",&stu[i].score);
	}

	fd = open(path, O_CREAT | O_WRONLY, 0777);
	if(fd < 0){
		printf("open error");
	}


	cnt = write(fd, &stu, SIZE * sizeof(struct student));
	if(cnt == -1){
		printf("read failed\n");
	}

	printf("write end\n");

#if 0
	for(i=0 ;i < SIZE; i++){
		printf("name:%s num:%d sex:%c score:%f\n",stu[i].name,stu[i].num,
									stu[i].sex,stu[i].score);
	}
#endif

	close(fd);

	return 0;
}