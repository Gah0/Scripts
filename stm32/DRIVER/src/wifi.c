#include <wifi.h>



void WIFI_Rst(void){
  USART_SendString(USART1,"RST module...\r\n");
  USART_SendString(USART3,"AT+RST\r\n");
  Delay_us(3000);
  Delay_us(3000);
  CLR_Buf3();
  Flag_usart3_receive_OK=0;
}

void WIFI_Init(void){		
    WIFI_Rst();
}
