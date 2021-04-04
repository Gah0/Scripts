#include <unistd.h>
#include <stdio.h>

int main(){
	printf("pid:%d\n",getpid());
	fork();
	printf("pid:%d\n",getpid());
	while(1);
	return 0;
}