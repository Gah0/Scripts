#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "key.h"
#include "timer.h"
#include "digital.h"
#include "18b20.h"

uint8_t RxBuffer[256]="";
uint16_t RxCounter=0;
unsigned int temperature=0;

int main(void)
{ uint16_t RxData;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	Delay_Init();
	USART1_Init(9600);
	KEY_Init();
	TIM3_Init(49,7199);
	Digital_Init();
	DS18B20_GPIO_Config();
	
	while(1)
	{ 
		Delay_ms(2000);
		DS18B20_start();
		temperature=DS18B20_Temper(); 
	}
}
				
