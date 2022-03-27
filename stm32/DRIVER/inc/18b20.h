
#ifndef   __18B20_H
#define   __18B20_H
 
#include "stm32f10x.h"
#include "delay.h"
#include <sys.h>

#define DS18B20_DQ_OUT PAout(8)
#define DS18B20_DQ_IN PAin(8)

 
u8 DS18B20_GPIO_Config(void);
void  DS18B20_start(void) ;
unsigned int   DS18B20_Temper(void) ;

 
 
#endif