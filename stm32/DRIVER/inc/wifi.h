#ifndef _WIFI_H
#define _WIFI_H

#include "stm32f10x.h"
#include <usart.h>
#include <stdio.h>
#include <string.h>
#include <delay.h>

void wait_OK(void);
void WIFI_Init(void);
void WIFI_Rst(void);
void Setting_Connect_Work(char *type);
void Login_URL(void);
void WIFI_Connect(char *name,char *password);
void USER_Connect(void);
void Client_Connect(void);
void Connect_Aliyun_Server(void);
void Client_Subscribe(void);
void Client_Pub(float temp);
void wait_SUB(void);
#endif
