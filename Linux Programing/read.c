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

int main (int argc, char **argv){

	struct student stu[SIZE];

	char *path = "/home/gah0/桌面/code/lesson/student.txt";

	int cnt = 0;
	int fd = 0;
	int i;

	fd = open(path, O_RDONLY);
	if(fd < 0){
		printf("open error");
	}

	cnt = read(fd, stu, SIZE * sizeof(struct student));
	if(cnt == -1){
		printf("read failed\n");
	}

	for(i=0 ;i < SIZE; i++){
		printf("name:%s num:%d sex:%c score:%f\n",stu[i].name,stu[i].num,
									stu[i].sex,stu[i].score);
	}

	return 0;
}
