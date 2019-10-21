/*36块砖，36人搬；男搬4，女搬3，两个小孩抬一块砖。要求一次全搬完，问男、女、小孩各需多少人？
 *
 *
 *
*/

#include<stdio.h>
int main()
{
int m,f,child; //m 男 w 女 c 小孩
for(m=0;m<=9;m++)
   for(f=0;f<=12;f++)
        for(child=0;child<=36;child+=2)
            if((m+f+child==36)&&(4*m+3*f+child/2==36))
printf("男%d 女%d 小孩%d \n",m,f,child);
return 0;
}
