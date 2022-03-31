#include <wifi.h>



void WIFI_Rst(void){
	USART_SendString(USART1,"RST module...\r\n");
    USART_SendString(USART3,"AT+RST\r\n");
}

void WIFI_Init(void){		
    WIFI_Rst();
}
