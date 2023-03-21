CC = musl-gcc
INCDIR = `pkg-config libmodbus --cflags --libs`
CFLAGS = -O2 -Wall
#CFLAGS = -g -O2 -Wall $(INCDIR)
#DEST = /usr/local/bin
LDFLAGS = -L/usr/local/lib

ctimer = /home/gah0/lichee/libtimer/timer.c
cjson = /home/gah0/lichee/cJSON/cJSON.c
cmodbus = /home/gah0/lichee/modbusmaster.c
libc = $(ctimer) $(cjson) $(cmodbus)


MODBUSI=-I/home/gah0/lichee/libmodbus/include/modbus
MQTTI=-I/home/gah0/lichee/libmqtt/include
MI = $(MQTTI) $(MODBUSI)

MODBUSLIB=-L/home/gah0/lichee/libmodbus/lib
MQTTLIB=-L/home/gah0/lichee/libmqtt/lib
MLIB = $(MODBUSLIB) $(MQTTLIB)

MODBUS = $(MODBUSI) $(MODBUSLIB)
MQTT = $(MQTTI) $(MQTTLIB)

libflag = -lpaho-mqtt3a -lpaho-mqtt3c -lmodbus -lpthread -lm

#GDB用オプションを有効にするならCFLAGの-O2を-O0に変更して最適化を無効にしたほうがよい
GDB = -g3

#all: $(PROGRAM)

#modbusmaster.o: modbusmaster.c
#	$(CC) modbuss.c $(MODBUSI) -o $(MODBUSLIB) -lmodbus

#modbus.o: modbus.c
#	$(CC) modbuss.c  -o $(pkg-config --cflags --libs libmodbus) mod

c25.o: c25.c
   $(CC) -g c25.c $(libc) $(MI) -o c25 $(MLIB) $(lib)

#mqtt.o: mqtt.c
#   $(CC) -g mqtt.c $(MQTT) -o mqtt -lpaho-mqtt3a -lpaho-mqtt3c -lm

clean:
	rm -f *.o *~ $(PROGRAM)
