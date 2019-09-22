#include "stdio.h" 

int main(){
	int x,y;
	printf("press a number:");
	scanf("%d",&x);
	if(x<0){
		y=2*x+1;
		goto Label;
		}
	if(x==0){
		y=0;
		goto Label;
		}
	if(x>0){
		y=2*x-1;
		goto Label;
		}
	Label:printf("answer:%d",y);
}