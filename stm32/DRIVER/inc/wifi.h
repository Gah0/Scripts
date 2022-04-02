#ifndef __WIFI_H
#define __WIFI_H

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "string.h"

void WIFI_Init(void);
void WIFI_Rst(void);
void Setting_Connect_Work(char *type);
void Login_URL(void);
void WIFI_Connect(char *name,char *password);
void USER_Connect(void);
void Client_Connect(void);
void Connect_Aliyun_Server(void);
void Client_Subscribe(void);
void wait_OK(void);
void Client_Pub(float temp);
void wait_SUB(void);

#endif
