#ifndef __USART_H
#define __USART_H
#include "stdint.h"
#include "stm32f10x.h"

#define USART3_REC_LEN 1024

void USART1_Init(uint32_t bound);
void USART3_Init(uint32_t bound);
void USART_SendString(USART_TypeDef* USARTx, char *str);
void CLR_Buf3(void);
#endif
