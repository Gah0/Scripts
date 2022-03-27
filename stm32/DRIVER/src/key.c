#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure; 	
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	
	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Line = EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_Init(&NVIC_InitStructure);
	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
{
	Delay_ms(100);
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)==0)
	printf("key1\r\n");
	
	EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
{
	Delay_ms(100);
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)==0)
	printf("key2\r\n");
	
	EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
	Delay_ms(100);
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==0)
	printf("key3\r\n");
	
	EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
	Delay_ms(100);
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)==0)
	printf("key4\r\n");
	
	EXTI_ClearITPendingBit(EXTI_Line6);
	}
}