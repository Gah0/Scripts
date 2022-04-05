#include "stm32f10x.h"

static temper temp;
temper* temp_ptr(void){
	return &temp;
}

