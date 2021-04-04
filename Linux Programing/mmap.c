#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

struct stat info;
	
int main (int argc, char **argv){
	int i,fd=0,ret=0;
	char *ptr = NULL;

	fd = open("cat.txt", O_RDWR);
	if(fd<0){
		printf("error");
		return -1;
	}
	
	ret = stat("cat.txt", &info) ;
	if(ret != 0){
		printf("file name not exist!");
		return 0;
	}
	
	printf("size: %d\n", info.st_size);
	printf("Last status change:  %s\n",    ctime(&(info.st_ctime)));
	printf("Last file access:    %s\n",    ctime(&(info.st_atime)));
	printf("Last file modification: %s\n", ctime(&(info.st_mtime)));
	
	ptr = (char *)mmap(NULL, info.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	printf("%c\n",ptr[4]);  //abcdefg
	
	ptr[4] = 'A';
	
	for(i=0; i< info.st_size; i++);
	{
		printf("%c",ptr[i]);
	}
	
	munmap(ptr, info.st_size);
	return 0;

}
