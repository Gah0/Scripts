CC = ~/arm-linux-musleabi-cross/bin/arm-linux-musleabi-gcc
CFLAGS = -O2 -Wall

c = port.c
#$(MODBUS_INC) $(MODBUS) $
c:port.c
	$(CC) $(c) -o serialtest

#main: main.c
#	$(CC) $(main) $(MQTT_INC) $(MQTT_LIB) -o main -lm

clean:
	rm -f *.o *~ $(PROGRAM)