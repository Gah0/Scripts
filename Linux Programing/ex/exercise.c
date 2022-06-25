#include <stdio.h>


int main(int argc, char** argv)
{

	int i;
	for(i=0;i<5;i++){
		printf("this is %d \n",i,argv[i]);
		return 1;
	}
}