#include "stm32f10x.h"

void LED_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure; 
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
GPIO_Init(GPIOC, &GPIO_InitStructure);

GPIO_SetBits(GPIOC, GPIO_Pin_13);	

}