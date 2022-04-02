#include <wifi.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include <stdlib.h>

extern	char Flag_usart3_receive_OK;
extern	char Flag_usart3_receive;
extern	char USART3_RX_BUF[USART3_REC_LEN];

void WIFI_Init(void){		
  WIFI_Rst();
  Setting_Connect_Work("3");
  wait_OK();

  Login_URL();
  wait_OK();

  WIFI_Connect("\"Gah0\"","\"122345678\"");
  wait_OK();

  USER_Connect();
  wait_OK();

  Client_Connect();
  wait_OK();

  Connect_Aliyun_Server();
  wait_OK();

  Client_Subscribe();
  wait_OK();
}

void WIFI_Rst(void){
  USART_SendString(USART1,"RST module...\r\n");
  USART_SendString(USART3,"AT+RST\r\n");
  Delay_ms(1000);
  Delay_ms(1000);
  Delay_ms(1000);
  Delay_ms(1000);
  Delay_ms(1000);
  Delay_ms(1000);
  CLR_Buf3();
  Flag_usart3_receive_OK=0;
}

void Setting_Connect_Work(char *type)
{
	char wifi_buf[13]={"AT+CWMODE=x\r\n"};
	wifi_buf[10]=*type;
	USART_SendString(USART1,"SET WORKMODE...\r\n");
  USART_SendString(USART3, wifi_buf);
}

void Login_URL(void){
	char login_url[80]={"AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n"};
	USART_SendString(USART1,"connected aliyun cloud...\r\n");
  USART_SendString(USART3, login_url);
}


void WIFI_Connect(char *name,char *password){
	char wifi_connect_buf[50] = {"AT+CWJAP="};
	strcat(wifi_connect_buf,name);
	strcat(wifi_connect_buf,",");
	strcat(wifi_connect_buf,password);
	strcat(wifi_connect_buf,"\r\n");
	USART_SendString(USART1,"connect wifi...\r\n");
  USART_SendString(USART3, wifi_connect_buf);
}

void USER_Connect(void){
	char user_connect_buf[100] = {"AT+MQTTUSERCFG=0,1,\"NULL\",\"device&*********\",\"**********************************\",0,0,\"\"\r\n"};
	USART_SendString(USART1, "connect user device\r\n");
  USART_SendString(USART3, user_connect_buf);
}

void Client_Connect(void){
	char client_connect_buf[100] = {"AT+MQTTCLIENTID=0,\"device|securemode=3\\,signmethod=hmacsha1|\"\r\n"};
	USART_SendString(USART1, "connect client\r\n");
  USART_SendString(USART3, client_connect_buf);
}

void Connect_Aliyun_Server(void){
	char connect_server_buf[100]= {"AT+MQTTCONN=0,\"*********.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n"};
	USART_SendString(USART1, "connected aliyun\r\n");
  USART_SendString(USART3, connect_server_buf);
}

void Client_Subscribe(void){
	char client_subscribe_buf[100]={"AT+MQTTSUB=0,\"/sys/*********/device/thing/service/property/set\",0\r\n"};
	USART_SendString(USART1, "subscribe\r\n");
	USART_SendString(USART3, client_subscribe_buf);
}


void Client_Pub(float temp){
  char str[20];
  char client_subscribe_buf[200]={"AT+MQTTPUB=0,\"/sys/**********/device/thing/event/property/post\",\"{\\\"params\\\":{\\\"temperture\\\""};
  USART_SendString(USART1, "publish\r\n");
  sprintf(str,":%0.1f}}\"",temp);
  strcat(client_subscribe_buf,str);
  strcat(client_subscribe_buf,",0,0\r\n");

  USART_SendString(USART3, client_subscribe_buf);
	USART_SendString(USART1, client_subscribe_buf);
  wait_OK();
}

void wait_OK(void){
  while(!Flag_usart3_receive_OK);
  Flag_usart3_receive_OK = 0;
  CLR_Buf3();
}

void wait_SUB(void)
{
	int len;
	int vol;
	char *ret;
	char str[10];
	len = strlen(USART3_RX_BUF);//������ĳ���
	if(len>10)
	{
		USART_SendString(USART1, USART3_RX_BUF);
		
		ret = strstr(USART3_RX_BUF,"light");
		if(ret != NULL)
		{
			printf("\nthis is %s",ret);
			
			str[0]=*(ret+7);
			str[1]=*(ret+8);
			str[2]='\0';
			printf("this is str %s\n",str);
			
			vol = atoi(str);
			printf("this is str %d\n",vol);
			
		}
		
		CLR_Buf3();     //�������3���ջ���
	}
	
}


