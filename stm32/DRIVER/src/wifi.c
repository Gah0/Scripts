#include <wifi.h>



void WIFI_Rst(void){
  USART_SendString(USART1,"RST module...\r\n");
  USART_SendString(USART3,"AT+RST\r\n");
  Delay_us(3000);
  Delay_us(3000);
}

void WIFI_Init(void){		
    WIFI_Rst();
}
