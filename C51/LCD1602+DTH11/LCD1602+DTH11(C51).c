/*author Gah0*/

#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <intrins.h>


#define uchar unsigned char
#define uint unsigned int

#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR E=0
#define EN_SET E=1

sbit RS = P2^0;
sbit RW = P2^1;
sbit E = P2^2;	 
sbit DHT_DATA=P3^7;

uchar CheckSum=0;
uchar bin_buf[5];
uchar *p = bin_buf;


uchar shidu_hex[16];
uchar wendu_hex[16];
uchar C[20];
/*
 *  二进制转十六进制
 *  不需要校验，不需要小数位高精度，节省内存。
 *  
*/
void BIN2HEX(){
    	sprintf(shidu_hex,"Hum = %d.%d",*p,*(p+1));
		sprintf(wendu_hex,"Tem = %d.%d",*(p+2),*(p+3));
        sprintf(C,"%d",CheckSum);
}

/*
 *  定时器函数和delay();
 *  18419us=18.42ms=1011100000001100   47116=X
 *  30us=1111111111100010              65506=X
 *  us=(65536-X)*1us [12mhz下]
 *  尽量使用keil compiler生成
*/
void timer_delay20ms(){		/* Timer0 delay function */
	TMOD = 0x01;            /* M0=1 */
	TH0 = 0xB8;				/* 高八10111000 */
	TL0 = 0x0C;				/* 低八00001100 */
	TR0 = 1;				/* Start timer0 */
	while(TF0 == 0);	    /* Wait until timer0 flag set */
	TR0 = 0;				/* Stop timer0 */
	TF0 = 0;				/* Clear timer0 flag */
}

void timer_delay10us(){     /* Timer0 delay function */
	TMOD = 0x01;			/* M0=1 */
	TH0 = 0xFF;			    /* 高八11111111 */
	TL0 = 0xF6;			    /* 低八11110110 */
	TR0 = 1;				/* Start timer0 */
	while(TF0 == 0);		/* Wait until timer0 flag set */
	TR0 = 0;				/* Stop timer0 */
	TF0 = 0;				/* Clear timer0 flag */
}

void timer_delay30us(){     /* Timer0 delay function */
	TMOD = 0x01;			/* M0=1 */
	TH0 = 0xFF;			    /* 高八11111111 */
	TL0 = 0xE2;			    /* 低八11110001 */
	TR0 = 1;				/* Start timer0 */
	while(TF0 == 0);		/* Wait until timer0 flag set */
	TR0 = 0;				/* Stop timer0 */
	TF0 = 0;				/* Clear timer0 flag */
}

void delay(uint count){
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
}
/*
 * 启动DHT
 * 
*/
void DHT_INIT()	{
    DHT_DATA=1;
	timer_delay10us();
	DHT_DATA=0;
	timer_delay20ms();
	DHT_DATA=1;
	timer_delay30us();
}

/*
 * set display panel
*/
void write_com(uchar cmd){		
		RS_CLR;
		timer_delay10us();
		RW_CLR;
		timer_delay10us();
		P0=cmd;
		timer_delay10us();
		EN_SET;
		timer_delay10us();
		EN_CLR;
}

void write_data(uchar dat){
		RS_SET;
		timer_delay10us();
		RW_CLR;
		timer_delay10us();
		P0=dat;
		timer_delay10us();
		EN_SET;
		timer_delay10us();
		EN_CLR;
		timer_delay10us();
}

void LCD_INIT()         
{
	timer_delay20ms();
    write_com(0x38);
	timer_delay20ms();
    write_com(0x0c);
	timer_delay20ms();
    write_com(0x06);
	timer_delay20ms();
    write_com(0x01);    
}

/*
 *  设定显示屏
 *  x为行，y为列
*/
void select_str(uchar row, uchar col){
		uchar addr;
	
		if(col==0){
			addr = 0x00 + row;
		}else{
			addr = 0x40 + row;
		}
		write_com(addr|0x80);
}

void write_str(uchar row, uchar col, uchar *str) {

	select_str(row, col);
    while(*str != '\0'){
        write_data(*str++);
    }

}

/*
 * 返回一个字节函数
 * 在30us内保持高电平为0;
 * 30us<timer_delay<70us保持高电平为1
 */
uchar DHT_READ_BYTE(){
	uchar i,byte=0;

	for(i=0;i<8;i++){
		while(DHT_DATA==0);
		timer_delay30us();
		if(DHT_DATA==1){
			byte = (byte<<1)|(0x01);
		}else{
			byte = (byte<<1);
		}
		while(DHT_DATA==1);
	}
	return byte;
}


/*
 *  读取数据
 *  不打算使用校验与小数点后位
 *  校验不成功会显示ERROR
*/
void DHT_READ_DATA()
{
	uchar R_H,R_L,T_H,T_L;

	DHT_INIT();
	DHT_DATA=1;
	if(DHT_DATA==0){
		while(DHT_DATA==0);
		
        bin_buf[0]=DHT_READ_BYTE();    
        bin_buf[1]=DHT_READ_BYTE();    
        bin_buf[2]=DHT_READ_BYTE();    
        bin_buf[3]=DHT_READ_BYTE();    
        bin_buf[4]=DHT_READ_BYTE();

        if((R_H+R_L+T_H+T_L)!=CheckSum){
            write_str(6, 0, "Error");
			write_str(6, 0, "Error");
/*       }else{
			bin_buf[0]=R_H;
			bin_buf[1]=R_L;
			bin_buf[2]=T_H;
			bin_buf[3]=T_L;
			bin_buf[4]=CheckSum;
		}
*/
        delay(100);
	}	
}

void main(){
	P1=0xf0;

	LCD_INIT();
	EA = 1;        
	while(1){
		delay(150);
		DHT_READ_DATA();
		BIN2HEX();
		delay(100);
        //
		write_str(0,0,shidu_hex);
		write_str(0,1,wendu_hex);
        write_com(0xdf);
        write_str(12,0," %");
		write_str(12,1," C");	
        memset(C,0,20);
        write_str(14,1,C);
	}
}
