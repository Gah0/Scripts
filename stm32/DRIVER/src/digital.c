#include "stm32f10x.h"

// 0	 1  2   3	4	5  6  7	8	 9	  A	   b	C    d	  E    F  
unsigned char DIGITAL[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};



unsigned char DIGITALP[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x66,0x21,0x06};
void Digital_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
}
void Show_One(char temp)
{
	GPIO_SetBits(GPIOA,DIGITAL[temp]&0x00ff);

	GPIO_ResetBits(GPIOA,~DIGITAL[temp]&0x00ff);

}
void Show_OneP(char temp)
{
	GPIO_SetBits(GPIOA,DIGITALP[temp]&0x00ff);

	GPIO_ResetBits(GPIOA,~DIGITALP[temp]&0x00ff);

}

void Digital_Display(int temp, char number)
{
	char  temp_thou=temp/1000;
	char  temp_hund=(temp/100)%10;
	char  temp_tens=(temp%100)/10;
	char  temp_ones=temp%10;
  switch(number)
	{
		case 0:
	  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	  Show_One(temp_ones);
		break;
		case 1:
		if(temp>=10)
		{
	  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	  Show_OneP(temp_tens);
		}
		break;
		case 2:
		if(temp>=100)
		{
	  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	  Show_One(temp_hund);
		}
		break;
		case 3:
		if(temp>=1000)
		{			
		GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	  Show_One(temp_thou);
		}
		break;
	}

}