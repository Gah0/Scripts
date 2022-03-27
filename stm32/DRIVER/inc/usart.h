#ifndef __USART_H
#define __USART_H
#include "stdint.h"
#include "stm32f10x.h"
void USART1_Init(uint32_t bound);
void USART_SendString(USART_TypeDef* USARTx, char *str);
#endif
