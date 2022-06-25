#include <modbus.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(){
	uint16_t tab_reg [64] = {0};

	int i,regs =0;
	modbus_t *ctx = NULL;




	ctx = modbus_new_rtu("/dev/ttyS7",9600,'N',8,1);
	modbus_set_slave(ctx,1);	
	modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS485);
	modbus_rtu_set_rts(ctx,MODBUS_RTU_RTS_UP);

	if(modbus_connect(ctx)==-1){
		fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}


	modbus_set_response_timeout(ctx,0,1000000);
	while(1){


		memset(tab_reg,0,sizeof(tab_reg));
		regs= modbus_read_registers(ctx,0,20,tab_reg);
		if(regs == -1){
			fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
			continue;
		}

		for(i=0;i<20;++i){
			printf("tab_reg[%d]=(0x%x)\n",i,tab_reg[i]);
		}
		printf("\n");
		sleep(1);
	}
	
	return 0;
}
