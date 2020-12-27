/* Author Gah0
/* Ultrasonic ranging module HC - SR04 provides 2cm - 400cm non-contact
/* measurement function, the ranging accuracy can reach to 3mm. The modules
/* includes ultrasonic transmitters, receiver and control circuit. The basic principle
/* of work:
/* (1) Using IO trigger for at least 10us high level signal, we hava 2 keys control the Trig IO and Echo IO, 
/* press key will give a high level on Trig, pressd key2 will give high level on ECHO refuse the block signal.
/* (2) The Module automatically sends eight 40 kHz and detect whether there is a
/* pulse signal back.
/* (3) IF the signal back, through high level , time of high output IO duration is
/* the time from sending ultrasonic to returning.
/* Test distance = (high level time×velocity of sound (340M/S) / 2,
*/

#include <STC15.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <intrins.h>

#define CRYSTAL_FREQUENCY 110592
#define VALUE 1.7/100
#define uchar unsigned char
#define uint unsigned int

#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR E=0
#define EN_SET E=1

sbit Trig = P3^2;
sbit Echo = P3^3;

sbit RS = P3^4;
sbit RW = P3^5;
sbit E = P3^6;

sbit BEEP = P5^4;

sbit key2_stop = P3^6;
sbit key1_start = P3^7;



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

void timer_delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void tweet1(){
	BEEP=1;
	Delay1000ms();
	BEEP=0;
}

void tweet2(){
	BEEP=1;
	Delay1000ms();
	BEEP=0;
	Delay1000ms();
	BEEP=1;
	Delay1000ms();
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
		P1=cmd;
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
		P1=dat;
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

void HC_WAIT(){
	timer_delay10us();
	if(key1_start==1){
		while(key1_start == 0){
			Trig = 0;
		}
	tweet1();
	}
}

void HC_INIT(){
	Trig = 1;
	HC_WAIT();
}

int HC_Data(){
	while(!Echo);
	TR0=1;
	while(Echo);
	TR0=0;

	return TH0 * 256 * TL0;
}

float HC_distance(){
	float dis;

	dis = HC_Data();
	dis *= VALUE;

	TH0=0;
	TL0=0;

	if(dis > 450)
		write_str(0,0,"overdtsc");
		dis = 0;
	
	return dis;
}


void Time0_INIT(void)			//定时器0配置函数
{
	TMOD=0x01; 
	TH0=0;
	TL0=0;
	ET0=1; 
	TR0=1; 
	EA=1; 
}

void _init(void)
{
	Time0_INIT();
	Trig=0;
	Echo=0;

// fuck stc register
//	EX0=1;
//	ET0=1;             //允许T0中断
}

void stop() 
{
	while(1)
		write_str(0,1,"STOP");
		write_str(1,0,"Gah0.github.io");
		if(key2_stop == 1){
			while( key2_stop == 1 ){
				key2_stop == 0;
		}
	}
}

void check_stop_key(){
	if(key2_stop = 0){
		while( key2_stop == 0 ){
			key2_stop = 1;
			tweet1();
			stop();
		}
	}
}

void LCD_CHAR(){
	write_str(0,0,"distance:");
	write_str(0,14,"cm");
	write_str(1,0,"press key1 on");
}

int main(){
	char dis[1];

	_init();
	LCD_INIT();
	LCD_CHAR();
	HC_INIT();
	tweet2();

	while(1){
		dis[1] = HC_distance();

		check_stop_key();

		write_str(0,11,dis);
	}

}