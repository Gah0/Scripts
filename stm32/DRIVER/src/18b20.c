#include "18b20.h"

void DS18B20_IO_OUT(void){
		GPIO_InitTypeDef GPIO_InitStructure;
 													   
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DS18B20_IO_IN(void){
		GPIO_InitTypeDef GPIO_InitStructure;
 													   
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
unsigned char DS18B20_Reset(void)               
{
    DS18B20_IO_OUT(); 
    DS18B20_DQ_OUT=0; 
    Delay_us(750);    
    DS18B20_DQ_OUT=1; 
    Delay_us(15);     
}


u8 DS18B20_Check(void)
{   
    u8 retry=0;
    DS18B20_IO_IN();
    while(DS18B20_DQ_IN && retry<200){

        retry++;
        Delay_us(1);
    }
		
    if(retry>=200){
      return 1;
    }
    else{
        retry=0;
    }

    while(!DS18B20_DQ_IN&&retry<240)
    {
        retry++;
        Delay_us(1);
    }
    if(retry>=240)return 1;
    return 0;
}

u8 DS18B20_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);    

    DS18B20_Reset();
    return DS18B20_Check();
}


void DS18B20_Write_Byte(u8 value) 
{
  unsigned char i;
	u8 tmp;
	DS18B20_IO_OUT();
  for (i = 8; i != 0; i--) 
  {
    tmp=value&0x01;
    value=value>>1;
    
    if (tmp) 
    {
			DS18B20_DQ_OUT=0;
			Delay_us(2);                           
			DS18B20_DQ_OUT=1;
			Delay_us(60);     
    }else{
			DS18B20_DQ_OUT=0;
			Delay_us(60);             
			DS18B20_DQ_OUT=1;
			Delay_us(2); 
		}
  }
}

   
unsigned char DS18B20_Read_Bit(void) 
{
	u8 data;
  unsigned char i;
  unsigned char value = 0;
	
	DS18B20_IO_OUT();
	DS18B20_DQ_OUT=0; 
	Delay_us(2);
	DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();
	if(DS18B20_DQ_IN)
	{
		data=1;
	}else{
		data=0;
	}
	Delay_us(50);         
	return data;
}


u8 DS18B20_Read_Byte(void)   
{        
    u8 i,j,dat=0;
    for (i=1;i<=8;i++)
    {
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }
    return dat;
}


void DS18B20_start(void) 
{ 
	DS18B20_Reset();
	DS18B20_Check();
  DS18B20_Write_Byte(0xcc);	         
  DS18B20_Write_Byte(0x44);	          
}
 
unsigned int DS18B20_Temper(void) 
{
   u8 temp;
   u8 TL,TH;
   short tem;
   DS18B20_start();                    // ds1820 start convert
   DS18B20_Reset();
   DS18B20_Check();
   DS18B20_Write_Byte(0xcc);// skip rom
   DS18B20_Write_Byte(0xbe);//convert
   TL=DS18B20_Read_Byte();// LSB   
   TH=DS18B20_Read_Byte();// MSB  
   if(TH>7)//£¨TH>xxxxx111£©negetive
   {
       TH=~TH;
			 TL=~TL;
       temp=0; 
   }
   else { 
		 temp=1;//positive
	 }
   tem=TH;
   tem<<=8;   
   tem+=TL;
   tem=(float)tem*0.625;
   if(temp) return tem; 
   else  return -tem;    
}