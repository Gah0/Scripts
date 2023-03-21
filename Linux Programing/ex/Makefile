CC = /home/gah0/arm-buildroot-linux-musleabi_sdk-buildroot/bin/arm-buildroot-linux-musleabi-gcc
CFLAGS = -O2 -Wall

c = gpio.c
#$(MODBUS_INC) $(MODBUS) $
c:gpio.c
	$(CC) $(c) -o p

#main: main.c
#	$(CC) $(main) $(MQTT_INC) $(MQTT_LIB) -o main -lm

clean:
	rm -f *.o *~ $(PROGRAM)
