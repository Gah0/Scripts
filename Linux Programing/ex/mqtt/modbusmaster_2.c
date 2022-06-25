#include <modbusmaster_2.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern double temperature

modbus_t *ctx = NULL;

int modbus_init(){
	int regs=0;

	ctx = modbus_new_rtu("/dev/ttyS7",9600,'N',8,1);
	//设置从机地址
	modbus_set_slave(ctx,1);	
//	modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS485);
//	modbus_rtu_set_rts(ctx,MODBUS_RTU_RTS_UP);

	//建立连接
	if(modbus_connect(ctx)==-1){
		fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}

	//设置应答延时
	modbus_set_response_timeout(ctx,0,1000000);

}


int modbusmaster(){
	int rc,i;
	uint16_t tag_reg[64]={0};

	memset(tab_reg,0,sizeof(tab_reg));
	//读寄存器设置：寄存器地址，数量，数据缓冲
	rc= modbus_read_registers(ctx,0,20,tab_reg);
	if(rc == -1){
		printf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
		continue;
	}

	for(i=0;i<20;++i){
		printf("tab_reg[%d]=(%d)\n",i,tab_reg[i]);
	}
	printf("\n");
	temperature = tag_reg[0]*0.1;
	sleep(1);
	
	
	return 0;
}
