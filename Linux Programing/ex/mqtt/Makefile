CC = gcc
CFLAGS = -O2 -Wall
#MODBUS = ./modbusmaster.c -lmodbus
#MODBUS_INC =  -I~/桌面/C/mqtt/modbus/include/modbus
#MODBUS_LIB =  -L~/桌面/C/mqtt/modbus/lib
MQTT_INC = -I/~/桌面/C/mqtt/include
MQTT_LIB = -L/~/桌面/C/mqtt/lib -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -lpthread
CJSON = ./cJSON.c
TIMER = setitimer.c
main = main.c
maan = maan.c
c = c6_3copy.c
$(MODBUS_INC) $(MODBUS) $
c:c6_3copy.c
	$(CC) $(c) $(MQTT_INC) $(MQTT_LIB) $(CJSON)  -o c7 -lm

#main: main.c
#	$(CC) $(main) $(MQTT_INC) $(MQTT_LIB) -o main -lm

#maan: maan.c
#	$(CC) $(maan) $(MQTT_INC) $(MQTT_LIB) -o maan -lm


clean:
	rm -f *.o *~ $(PROGRAM)