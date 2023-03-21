#include "modbus.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
int main(void){
	uint16_t tab_reg [64] = {0};

	int i,regs =0;
	modbus_t *ctx = NULL;

	ctx = modbus_new_rtu("/dev/ttyS1",9600,'N',8,1);
	modbus_set_slave(ctx,1);
//	modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS485);
//	modbus_rtu_set_rts(ctx,MODBUS_RTU_RTS_UP);

    modbus_set_debug(ctx, TRUE);

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }


	modbus_set_response_timeout(ctx,0,1000000);
	while(1){
		memset(tab_reg,0,sizeof(tab_reg));
		regs= modbus_read_registers(ctx,0,2,tab_reg);
		if(regs == -1){
			fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
			return -1;
		}

		for(i=0;i<2;++i){
			printf("tab_reg[%d]=(0x%d)\n",i,tab_reg[i]);
		}
		printf("\n");
		sleep(1);
	}

	//return 0;
}
