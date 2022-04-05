#ifndef __USART_H
#define __USART_H
#include "stdint.h"
#include "stm32f10x.h"
//#include "stdio.h"
#define USART3_REC_LEN  512
void USART1_Init(uint32_t bound);
void USART3_Init(uint32_t bound);
void USART_SendString(USART_TypeDef* USARTx, char *str);
//int fputc(int ch, FILE *stream);
void CLR_Buf3(void);
#endif
