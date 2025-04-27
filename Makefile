CPU = atmega328p
PORT = COM4
SPEED = 115200
F_CPU = 16000000UL
TARGET = main
CC = avr-gcc
CFLAGS = -Wall -O2 -mmcu=$(CPU) -DF_CPU=$(F_CPU)
OBJS = tm1637.o i2c_master.o uart.o

$(TARGET).hex: $(TARGET).bin
	avr-objcopy -j .text -j .data -O ihex $(TARGET).bin $(TARGET).hex
$(TARGET).bin: $(TARGET).o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
program:
	avrdude -C../../avr/etc/avrdude.conf -c arduino -p $(CPU) \
	-P $(PORT) -b $(SPEED) -V -U flash:w:$(TARGET).hex
flash: program
clean:
	rm -f $(OBJS) $(TARGET).o $(TARGET).bin $(TARGET).hex
.PHONY:
	program flash clean
