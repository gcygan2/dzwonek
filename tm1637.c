#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "tm1637.h"

void tm1637_stop(void)
{
	TM1637_CLK_PORT &= ~(1<<TM1637_CLK);
	TM1637_DIO_PORT &= ~(1<<TM1637_DIO);
	TM1637_CLK_PORT |= (1<<TM1637_CLK);
	TM1637_DIO_PORT |= (1<<TM1637_DIO);
}

uint8_t tm1637_write(uint8_t value)
{
	uint8_t i, ack;

	for (i = 0; i < 8; ++i, value >>= 1) {
		TM1637_CLK_PORT &= ~(1<<TM1637_CLK);
		if (value & 0x01) {
			TM1637_DIO_PORT |= (1<<TM1637_DIO);
		} else {
			TM1637_DIO_PORT &= ~(1<<TM1637_DIO);
		}

		TM1637_CLK_PORT |= (1<<TM1637_CLK);
	}
	TM1637_CLK_PORT &= ~(1<<TM1637_CLK);

	TM1637_DIO_DDR &= ~(1<<TM1637_DIO);
	TM1637_DIO_PORT |= (1<<TM1637_DIO);
	ack = TM1637_DIO_PIN & (1<<TM1637_DIO);
	TM1637_DIO_DDR |= (1<<TM1637_DIO);

	if (ack) {
		TM1637_DIO_PORT &= ~(1<<TM1637_DIO);
	}

	TM1637_CLK_PORT |= (1<<TM1637_CLK);
	TM1637_CLK_PORT &= ~(1<<TM1637_CLK);

	return ack;
}

static const uint8_t char27pos [] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0x71  // F
};

static int my_putchar(char c, FILE *stream)
{
	static uint8_t pos = 0, l;
	if (c == '\r') {
		pos = 0;
	} else if (isxdigit (c) || c == ':' || c == ' ') {
		TM1637_START();
		tm1637_write(0xc0 + pos);
		if (c == ' ') {
			l = 0;
		} else if (c == 'a') {
			l = 0x77;
		} else if (c == 'b') {
			l = 0x7c;
		} else if (c == 'c') {
			l = 0x39;
		} else if (c == 'd') {
			l = 0x5e;
		} else if (c == 'e') {
			l = 0x79;
		} else if (c == 'f') {
			l = 0x71;
		} else {
			l = char27pos[c-'0'];
		}
		l |= (pos == 1)? 0x80 : 0;
		tm1637_write(l);
		tm1637_stop();
		pos++;
		//if (pos > 3) pos = 0;
	}
	return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(my_putchar, NULL, _FDEV_SETUP_WRITE);

void stdio_tm1637_init (void)
{
	TM1637_DIO_DDR |= (1<<TM1637_DIO);
	TM1637_CLK_DDR |= (1<<TM1637_CLK);
	TM1637_DIO_PORT |= (1<<TM1637_DIO);
	TM1637_CLK_PORT |= (1<<TM1637_CLK);

	TM1637_START();
	//tm1637_write(0x8f);//wlacz wyswietlacz z maks moca
	tm1637_write(0x88);//
	tm1637_write(0x85);//
	tm1637_stop();
	stdout = &mystdout;
}

/*
int main(void)
{
	TM1637_DIO_DDR |= (1<<TM1637_DIO);
	TM1637_CLK_DDR |= (1<<TM1637_CLK);
	TM1637_DIO_PORT |= (1<<TM1637_DIO);
	TM1637_CLK_PORT |= (1<<TM1637_CLK);

	TM1637_START();
	tm1637_write(0xc0);
	tm1637_write(0x01);
	tm1637_write(0x03);
	tm1637_write(0x07);
	tm1637_write(0x0f);
	tm1637_stop();

	TM1637_START();
	tm1637_write(0x8f);//wlacz wyswietlacz z maks moca
	tm1637_stop();

	for (;;);
	return 0;
}
*/