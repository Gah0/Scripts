#include "stm32f10x.h"
#include "digital.h"
//#include "18b20.h"	

struct counter{
	char digital_ctr;
	unsigned int ctr;
}flag={0,0};

extern unsigned int temperature;
char TenSensorflag=0;

void TIM3_Init(uint32_t per,uint32_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = per; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
	
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
	
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET) 
	{ 
//		GPIOC->ODR^=GPIO_Pin_13;
		Digital_Display(temperature,flag.digital_ctr);
		if(flag.digital_ctr<3)
			flag.digital_ctr++;
		else 
			flag.digital_ctr=0;
		
		if(flag.ctr<2000)
			flag.ctr++;
		else 
		{
			flag.ctr=0;
			TenSensorflag=1;
		}
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}


}
