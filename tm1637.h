#ifndef __TM1637_H_
#define __TM1637_H_

#define	TM1637_DIO	0
#define	TM1637_DIO_PORT	PORTB
#define	TM1637_DIO_DDR	DDRB
#define	TM1637_DIO_PIN	PINB

#define	TM1637_CLK	1
#define	TM1637_CLK_PORT	PORTB
#define	TM1637_CLK_DDR	DDRB
#define	TM1637_CLK_PIN	PINB

#define	TM1637_START() (TM1637_DIO_PORT &= ~(1<<TM1637_DIO))

extern void stdio_tm1637_init (void);
extern uint8_t tm1637_write(uint8_t value);
extern void tm1637_stop(void);
#endif
