#include "stdio.h"

int main(void){	struct Data{int your_age,friend_age; char ch;}data;
	printf("你的年龄:");
	scanf("%d",&data.your_age);
	printf("朋友的年龄:");
	scanf("%d",&data.friend_age);

	if(data.your_age>data.friend_age)
		ch=1;
	else
		ch=2;

    switch(ch)
    {
       case 1 :printf("%d",data.your_age);
       case 2 :printf("%d",data.friend_age);
    }
	return 0;

}
