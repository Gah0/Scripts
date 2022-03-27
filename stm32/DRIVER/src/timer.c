#include "stm32f10x.h"
#include "digital.h"
char T=0;
extern unsigned int temperature;

void TIM3_Init(uint32_t per,uint32_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;		
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = per; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
		
	
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler (void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET) 
	{ 
//		GPIOC->ODR^=GPIO_Pin_13;
	
		Digital_Display(temperature,T);
		if(T<3)
		T++;
		else T=0;
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}

}
