/* author Gah0
/* Ultrasonic ranging module HC - SR04 provides 2cm - 400cm non-contact
/* measurement function, the ranging accuracy can reach to 3mm. The modules
/* includes ultrasonic transmitters, receiver and control circuit. The basic principle
/* of work:
/* (1) Using IO trigger for at least 10us high level signal,
/* (2) The Module automatically sends eight 40 kHz and detect whether there is a
/* pulse signal back.
/* (3) IF the signal back, through high level , time of high output IO duration is
/* the time from sending ultrasonic to returning.
/* Test distance = (high level time×velocity of sound (340M/S) / 2,
*/

#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <intrins.h>

#define CRYSTAL_FREQUENCY 11.0592
#define uchar unsigned char
#define uint unsigned int

#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR E=0
#define EN_SET E=1

sbit BEEP = P3^7;
sbit Echo = P3^2;
sbit Trig = P3^3;
sbit RS = P3^4;
sbit RW = P3^5;
sbit E = P3^6;

/*
 *  delay();
 *  18419us=18.42ms=1011100000001100   47116=X
 *  30us=1111111111100010              65506=X
 *  us=(65536-X)*1us [12mhz]
 *  keil compiler??
*/
void timer_delay10us(){ /* Timer0 delay function */
	TMOD = 0x01;					/* M0=1 */
	TH0 = 0xFF;						/* ��811111111 */
	TL0 = 0xF6;						/* ��811110110 */
	TR0 = 1;						/* Start timer0 */
	while(TF0 == 0);				/* Wait until timer0 flag set */
	TR0 = 0;						/* Stop timer0 */
	TF0 = 0;						/* Clear timer0 flag */
}

void udelay(void)		//100微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

/*tweet*/
void tweet1(){
	BEEP=1;
	udelay();
	BEEP=0;
}

void tweet2(){
	BEEP=1;
	udelay();
	BEEP=0;
	udelay();
	BEEP=1;
	udelay();
	BEEP=0;	
}

void tweet3(){
	BEEP=1;
	udelay();
	BEEP=0;
	udelay();
	BEEP=1;
	udelay();
	BEEP=0;
	udelay();
	BEEP=1;
	udelay();
	BEEP=0;
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
 *  �趨��ʾ��
 *  x y
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

void HC_ENDWAIT(){
	timer_delay10us();
	if(Trig==1){
		while(Trig == 0){
			Trig = 0;
		}
	tweet1();
	}
}

void HC_init(){
	Trig = 1;
	HC_ENDWAIT();
}

void HC_echo(){
	while(!Echo);
	TR0=1;
	while(Echo);
	tR0=0;
	return (TH0 * 256 * TL0) * (12 / CRYSTAL_FREQUENCY);
}

float HC_distance(){
	float dis;
	dis = HC_echo();
	dis *= 0.017;
	if(dis > 450){ 
		write_str(0,0,"overflow");
	}
	return dis;
}

int main(){
	float dis;

	LCD_INIT();
	HC_init();
	tweet2();

	while(1){
		dis = HC_distance();
		if(Echo = 0){
			while( Echo == 0 ){
				Echo = 1;
				tweet3();
			}
			snprintf(buf,"reflush now\n");
			write_str(0,0,"reflush now\n");
		}
		snprintf(buf,"distance=%fcm\n",dis);
		write_str(0,0,"distance:");
		write_str(0,11,dis);
		write_str(0,14,"cm");
		write_str(0,1,"Gah0.github.io");
	}
}