/*编程，从键盘输入 6 个同学计算机课程期末考试成绩，并统计出平均分、最高分、最
低分，以及统计超过平均分的人数，并实现正确输出。
 */
#include "stdio.h"

#define NUM 6;

void main() {
	int s[NUM];
	int i,max,min,score,sum = 0 people counter = 0 ;

	for (int i=0;i<NUM;i++){
		printf("please input the stage of the %d scroe");
		scanf("%d",s[i]);
		sum += s[i];
	}
	score = (double)sum/NUM;
	printf("成绩录入完毕，the average score is %d",score)


	for(int i=0;i<max;i++){
		if (s[i]>max){
			max = s[i];
			sum = i;
		}
	}
	printf("the max of score is %d",sum);

	for(int i=0;i<min;i++){
		if (s[i]<min){
			min = s[i];
			sum = i;
	}
	printf("the min of score is %d",sum);

	for (int i = 0; i < people; ++i)
	{
		if (score<s[i])
			people counter++;
	}

	printf("Number of people above average score is %d",people counter)
}