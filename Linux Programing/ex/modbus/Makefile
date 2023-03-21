CC = ~/arm-linux-musleabi-cross/bin/arm-linux-musleabi-gcc
INCDIR = `pkg-config libmodbus --cflags`
CFLAGS = -O2 -Wall
#CFLAGS = -g -O2 -Wall $(INCDIR)
#DEST = /usr/local/bin
#LDFLAGS = -L/usr/local/lib
LIBS = `pkg-config libmodbus --libs`
OBJS = modbus.o
PROGRAM = mod

#GDB用オプションを有効にするならCFLAGの-O2を-O0に変更して最適化を無効にしたほうがよい
GDB = -g3

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
$(CFLAGS) $(OBJS) $(LIBS) $(GDB) -o $(PROGRAM)
#       $(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

modbus.o: modbus.c
	$(CC) $(INCDIR) -c modbus.c

clean:
	rm -f *.o *~ $(PROGRAM)
