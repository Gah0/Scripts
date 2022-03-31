#include "stm32f10x.h"
#include "usart.h"
#include "stdio.h"

extern uint8_t RxBuffer[256];
extern uint16_t RxCounter;

void USART1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	 
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	 
/* Configure the Priority Grouping with 1 bit */ 
	
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

}	

void USART3_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStruct;  
	USART_InitTypeDef USART_InitStruct;   
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;  
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   
	GPIO_Init(GPIOB,&GPIO_InitStruct);   
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;   
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   
	GPIO_Init(GPIOB,&GPIO_InitStruct);   
	
	
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;   
	USART_InitStruct.USART_Parity=USART_Parity_No;  
	USART_InitStruct.USART_BaudRate=bound;   
	USART_InitStruct.USART_StopBits=USART_StopBits_1;  
	USART_InitStruct.USART_WordLength=USART_WordLength_8b; 
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   

	USART_Init(USART3,&USART_InitStruct);  
	USART_Cmd(USART3,ENABLE);   
	USART_ITConfig(USART3, USART_IT_RXNE,ENABLE);
	/* Enable TIM3 global interrupt with Preemption Priority 0 and Sub 
	Priority as 2 */ 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

void USART_SendString(USART_TypeDef* USARTx, char *str)
{ uint32_t k=0;
	while(*(str+k)!='\0')
	{
		USART_SendData(USARTx, *(str+k));
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
		k++;
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
}

int fputc(int ch, FILE *stream)
{
	USART_SendData(USART1,(uint8_t) ch);	
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	return ch;
}
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET)
	{
	 RxBuffer[RxCounter++]=USART_ReceiveData(USART1);
	
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);



}	

