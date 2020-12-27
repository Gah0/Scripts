OBJ = ultrasonic
CFLAG = --debug --model-small --stack-after-data
CC = /usr/bin/sdcc $(CFLAG) 

$(OBJ).rel : $(OBJ).c
	$(CC) -c $(OBJ).c

$(OBJ).ihx : $(OBJ).rel
    $(CC) $(OBJ).rel

$(OBJ).hex : $(OBJ).ihx
    packihx $(OBJ).ihx > $(OBJ).hex

clean: 
	rm -f *.hex *.ihx *.map *.asm *.lk *.lst *.mem *.rel *.rst *sym