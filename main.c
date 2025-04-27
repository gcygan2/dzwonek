#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "tm1637.h"
#include "i2c_master.h"
#include "uart.h"

//#define EMU
#define I2C
#define MAX_MENU_INI 60
#define MIN_MENU_INI 6

#define ARD_PCF8583 0xd0

#define DZWONEK_PIN 2
#define DZWONEK_PORT PORTD
#define DZWONEK_DDR DDRD

#define L_DZWONKOW 32

#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 


#define KN_PIN PINB
#define KN_PORT PORTB
#define KN_DDR DDRB
#define KN_SW 4
#define KN_DT 3
#define KN_CLK 2
#define KN_INIT() (KN_PORT |= (1<<KN_CLK)|(1<<KN_DT)|(1<<KN_SW))

#define MENU_SET_AUTO 0
#define MENU_SET_MAN 1
#define MENU_SET_LIMIT 2
#define MENU_SET_LCD 3
#define MENU_SET_HOUR 4
#define MENU_SET_MIN 5
#define MENU_SET_WEEK 6
#define MENU_VIEW 7
#define MENU_ADD 10
#define MENU_CHG 12
#define MENU_ERASE 14
#define MENU_SET_MAX 14

#define EMU

volatile int8_t kn_val, kn_press;
volatile int8_t rtc_d, rtc_h, rtc_m, rtc_s;

int8_t mode_auto;//tryb automatyki 0 - wyl, 1 - od pon do piatku, 2 - caly tydzien
int8_t dzwonek_czas;
int8_t lcd_kontrast;

volatile int8_t rfr, dzwonek_recznie;

struct DZWONKI {uint8_t h; uint8_t m;};

struct DZWONKI dzwonki[32];

void ustaw_kontrast ()
{
	TM1637_START();
	tm1637_write(0x88|lcd_kontrast);
	tm1637_stop();
}

int sort (const void *a, const void *b)
{
	if (((struct DZWONKI *)a)->h*0x60+((struct DZWONKI *)a)->m < ((struct DZWONKI *)b)->h*0x60+((struct DZWONKI *)b)->m) return -1;
	if (((struct DZWONKI *)a)->h*0x60+((struct DZWONKI *)a)->m == ((struct DZWONKI *)b)->h*0x60+((struct DZWONKI *)b)->m) return 0;
	return 1;
}

void term()
{
	uint8_t cmd;
	int8_t i;
	static uint8_t hist;

	//cmd = uart_get();
	if ( !(UCSR0A & (1<<RXC0)) ) return;
	cmd = UDR0;

	if (cmd == 'a') {
		//uart_puts ("\n\rNr dzwonka (00-31) ");
		//i = uart_get_dec ();
		for (i = 0; i < L_DZWONKOW; i++) {
			if (dzwonki[i].h == 0xff) break;
		}
		if (i < L_DZWONKOW) {
			uart_puts ("\n\rGodzina ");
			cmd = uart_get_hex ();
			dzwonki[i].h = cmd;
			uart_puts ("\n\rMinuta ");
			cmd = uart_get_hex ();
			dzwonki[i].m = cmd;
			qsort (dzwonki, L_DZWONKOW, 2, sort);
			eeprom_update_block (dzwonki, (void *)0, sizeof (dzwonki));
			uart_puts ("\n\r>");
		} else {
			uart_puts ("\n\rZa duzy numer\n\r>");
		}	
	} else if (cmd == 'x') {
		uart_puts ("\n\rNr dzwonka (00-31) ");
		i = uart_get_dec ();
		if (i < L_DZWONKOW) {
			dzwonki[i].h = 0xff;
			dzwonki[i].m = 0xff;
			qsort (dzwonki, L_DZWONKOW, 2, sort);
			eeprom_update_block (dzwonki, (void *)0, sizeof (dzwonki));
			uart_puts ("\n\r>");
		} else {
			uart_puts ("\n\rZa duzy numer dzwonka\n\r>");
		}	
	} else if (cmd == 'd') {
		uart_puts ("Na pewno wszystko usunac? Wcisnij klawisz 't'.\n\r>");
		hist = cmd;
	} else if (cmd == 't' && hist == 'd') {
		for (i = 0; i < L_DZWONKOW; i++) {
			dzwonki[i].h = -1;
			dzwonki[i].m = -1;
		}
		eeprom_update_block (dzwonki, (void *)0, sizeof (dzwonki));
		uart_puts ("\n\rUsunieto");
	} else if (cmd == 'l') {
		uart_puts ("Lista dzwonkow\n\r");
		for (i = 0; i < L_DZWONKOW; i++) {
			if (dzwonki[i].h != 0xff) {
				uart_put_dec (i);
				uart_put ('>');
				uart_put_hex (dzwonki[i].h);
				uart_put (':');
				uart_put_hex (dzwonki[i].m);
				uart_puts ("\n\r");
			}
		}
		uart_puts (">");
	} else {
		uart_puts ("\n\rl - pokaz liste dzwonkow\n\ra - wprowadz / zmodyfikuj dzwonek\n\rx - usun jeden dzwonek\n\rd - usun wszystkie dzwonki\n\r>");
	}
}


ISR (TIMER0_OVF_vect)
{
	static uint8_t hist, hist2;

	if (KN_PIN & (1<<KN_DT)) {
		if (!hist) { //zbocze narastajace
			if (KN_PIN & (1<<KN_CLK)) {
				kn_val--;
			} else {
				kn_val++;

			}
		}
		hist = 1;
	} else {
		hist = 0;
	}


	if (KN_PIN & (1<<KN_SW)) {
		if (!hist2) { //zbocze narastajace
			kn_press = 1;
		}
		hist2 = 1;
	} else {
		hist2 = 0;
	}

}

void main_loop ()
{
	uint8_t wlacz, i;

	static int8_t menu = 0, menu_pos = 1, param = 0, param2 = 0;

	static int8_t menu_del = 0, rtc_s_hist;

	if (menu_del == 1) {
		menu = 0;
		menu_pos = 1;
		dzwonek_recznie = 0;
	}

	if (kn_press) {
		kn_press = 0;
		if (menu == 0) {
			menu = 1;
			menu_del = MAX_MENU_INI;
			//menu_pos = 0;
		} else if (menu == 1) {
			menu = 2;
			menu_del = MAX_MENU_INI;
			if (menu_pos == MENU_SET_AUTO) {
				param = mode_auto;
			} else if (menu_pos == MENU_SET_MAN) {
				param = 0;
				dzwonek_recznie = 1;
			} else if (menu_pos == MENU_SET_LIMIT) {
				param = dzwonek_czas;
			} else if (menu_pos == MENU_SET_LCD) {
				param = lcd_kontrast;
			} else if (menu_pos == MENU_SET_HOUR) {//ustaw_godzine
				param = rtc_h;
			} else if (menu_pos == MENU_SET_MIN) {
				param = rtc_m;
			} else if (menu_pos == MENU_SET_WEEK) {
				param = rtc_d;
			} else if (menu_pos == MENU_VIEW || menu_pos == MENU_CHG || menu_pos == MENU_ERASE) {
				menu_del = MIN_MENU_INI;
				param = 0;
			} else if (menu_pos == MENU_ADD) {
				menu_del = MIN_MENU_INI;
				menu = 3;//przeskocz jeden poziom
				for (i = 0; i < L_DZWONKOW; i++) {
					if (dzwonki[i].h == 0xff) break;
				}
				param = i;
				param2 = dzwonki[param].h;
			}
		} else if (menu == 2) {
			menu = 0;
			if (menu_pos == MENU_SET_AUTO) {
				mode_auto = param;
				eeprom_update_block (&mode_auto, (void *)64, 1);
			} else if (menu_pos == MENU_SET_MAN) {
				dzwonek_recznie = 0;
			} else if (menu_pos == MENU_SET_LIMIT) {
				dzwonek_czas = param;
				eeprom_update_block (&dzwonek_czas, (void *)65, 1);
			} else if (menu_pos == MENU_SET_LCD) {
				lcd_kontrast = param;
				eeprom_update_block (&lcd_kontrast, (void *)66, 1);
				ustaw_kontrast ();
			} else if (menu_pos == MENU_SET_MIN) {
				rtc_m = param;
				rtc_s = 0;
#ifdef I2C
				i2c_start(ARD_PCF8583);
				i2c_write(0);
				i2c_write(0);
				i2c_write(rtc_m);
				i2c_stop();
#endif
			} else if (menu_pos == MENU_SET_HOUR) {
				rtc_h = param;
#ifdef I2C
				i2c_start(ARD_PCF8583);
				i2c_write(2);
				i2c_write(rtc_h);
				i2c_stop();
#endif
			} else if (menu_pos == MENU_SET_WEEK) {
				rtc_d = param;
#ifdef I2C
				i2c_start(ARD_PCF8583);
				i2c_write(3);
				i2c_write(rtc_d);
#endif
			} else if (menu_pos == MENU_CHG) {
				menu = 3;
				menu_del = MIN_MENU_INI;
				param2 = dzwonki[param].h;
			} else if (menu_pos == MENU_ERASE) {
				menu = 1;
				dzwonki[param].h = 0xff;
				dzwonki[param].m = 0xff;
				qsort (dzwonki, L_DZWONKOW, 2, sort);
				eeprom_update_block (dzwonki, (void *)0, sizeof (dzwonki));
			}
		} else if (menu == 3) {
			if (menu_pos == MENU_CHG || menu_pos == MENU_ADD) {
				menu = 4;
				menu_del = MIN_MENU_INI;
				dzwonki[param].h = param2;
				param2 = dzwonki[param].m;
			}
		} else if (menu == 4) {
			if (menu_pos == MENU_CHG || menu_pos == MENU_ADD) {
				menu = 1;
				dzwonki[param].m = param2;
				qsort (dzwonki, L_DZWONKOW, 2, sort);
				eeprom_update_block (dzwonki, (void *)0, sizeof (dzwonki));
			}
		}
		rfr = 1;
	}

	if (kn_val) {
		if (menu == 3) {
			menu_del = MIN_MENU_INI;
			if (menu_pos == MENU_CHG || menu_pos == MENU_ADD) {
				if (kn_val < 0) {
					param2 -= ((param2 & 0x0f) == 0)? 7:1;
					param2 -= ((param2 & 0xf0) == 0xf0)? 0x60:0;
					if (param2 < 0) param2 = 0x23;
				} else if (kn_val > 0){
					param2 += ((param2 & 0x0f) == 9)? 7:1;
					param2 += ((param2 & 0xf0) > 0x90)? 0x60:0;
					if (param2 > 0x23) param2 = 0;
				}
			}
		} else if (menu == 4) {
			menu_del = MIN_MENU_INI;
			if (menu_pos == MENU_CHG || menu_pos == MENU_ADD) {
				if (kn_val < 0) {
					param2 -= ((param2 & 0x0f) == 0)? 7:1;
					param2 -= ((param2 & 0xf0) == 0xf0)? 0x60:0;
					if (param2 < 0) param2 = 0x59;
				} else if (kn_val > 0){
					param2 += ((param2 & 0x0f) == 9)? 7:1;
					param2 += ((param2 & 0xf0) > 0x90)? 0x60:0;
					if (param2 > 0x59) param2 = 0;
				}
			}
		} else if (menu == 1) {
			menu_del = MAX_MENU_INI;
			menu_pos += kn_val;
			if (menu_pos > MENU_SET_MAX) menu_pos = MENU_SET_MAX;
			else if (menu_pos < 0) menu_pos = 0;
		} else if (menu == 2) {
			menu_del = MAX_MENU_INI;
			if (menu_pos == MENU_SET_AUTO) { //rodzaj automatyki
				param += kn_val;
				if (param > 2) param = 2;
				else if (param < 0) param = 0;
			} if (menu_pos == MENU_SET_MAN) {
			} if (menu_pos == MENU_SET_LIMIT) { //czas dzwonka (1 - 9)s
				param += kn_val;
				if (param > 9) param = 9;
				else if (param < 1) param = 1;
			} else if (menu_pos == MENU_SET_LCD) {
				param += kn_val;
				if (param > 4) param = 4;
				else if (param < 0) param = 0;
			} else if (menu_pos == MENU_SET_HOUR) {//godziny
				if (kn_val < 0) {
					param -= ((param & 0x0f) == 0)? 7:1;
					param -= ((param & 0xf0) == 0xf0)? 0x60:0;
					if (param < 0) param = 0x23;
				} else if (kn_val > 0){
					param += ((param & 0x0f) == 9)? 7:1;
					param += ((param & 0xf0) > 0x90)? 0x60:0;
					if (param > 0x23) param = 0;
				}
			} else if (menu_pos == MENU_SET_MIN) {//minuty
				if (kn_val < 0) {
					param -= ((param & 0x0f) == 0)? 7:1;
					param -= ((param & 0xf0) == 0xf0)? 0x60:0;
					if (param < 0) param = 0x59;
				} else if (kn_val > 0){
					param += ((param & 0x0f) == 9)? 7:1;
					param += ((param & 0xf0) > 0x90)? 0x60:0;
					if (param > 0x59) param = 0;
				}
			} else if (menu_pos == MENU_SET_WEEK) { //dni tygodnia
				param += kn_val;
				if (param > 7) param = 1;
				else if (param < 1) param = 7;
			} else if (menu_pos == MENU_VIEW || menu_pos == MENU_ERASE || menu_pos == MENU_CHG) {
				menu_del = MIN_MENU_INI;
				param += kn_val;
				if (dzwonki[param].h == 0xff) param--;
				if (param < 0) param = 0;
			}
		}
		kn_val = 0;
		rfr = 1;
	}


	wlacz = 0;
	for (i = 0; i < L_DZWONKOW; i++) {
		if (dzwonki[i].h == rtc_h && dzwonki[i].m == rtc_m && rtc_s >= 0 && rtc_s <= dzwonek_czas) {
			wlacz = 1;
		}
	}

	if ((((mode_auto == 1 && rtc_d <= 5) || mode_auto == 2) && wlacz) || dzwonek_recznie) DZWONEK_PORT |= (1<<DZWONEK_PIN);
	else DZWONEK_PORT &= ~(1<<DZWONEK_PIN);

#ifdef I2C
	i2c_start(ARD_PCF8583);
	i2c_write(0);
	i2c_stop();
	i2c_start(ARD_PCF8583|1);
	rtc_s = i2c_read_ack();
	rtc_m = i2c_read_ack();
	rtc_h = i2c_read_ack();
	rtc_d = i2c_read_nack();
	i2c_stop();
#endif

	if (rtc_s != rtc_s_hist) {
		rtc_s_hist = rtc_s;
		rfr = 1;
		if (menu_del > 0) menu_del--;
	}

	if (rfr) {
		rfr = 0;
		if (menu == 0) {
			printf ("\r%02x%02x",rtc_h,rtc_m);
		} else if (menu == 1) {
			printf ("\r:%x  ", menu_pos);
		} else if (menu == 2) {
			if (menu_pos == MENU_VIEW || menu_pos == MENU_CHG || menu_pos == MENU_ERASE) {
				printf ("\r%02x%02x", dzwonki[param].h, dzwonki[param].m);
			} else {
				printf ("\r:%x%02x", menu_pos, param);
			}
		} else if (menu == 3 || menu == 4) {
			if (menu_pos == MENU_CHG) {
				printf ("\rc %02x", param2);
			} else if (menu_pos == MENU_ADD) {
				printf ("\ra %02x", param2);
			}
		}
	}

	term();

}


#ifdef EMU
void co_1s()
{
	rtc_s += ((rtc_s & 0x0f) == 9)? 7:1;
	rtc_s += ((rtc_s & 0xf0) > 0x90)? 0x60:0;
	if (rtc_s > 0x59) {
		rtc_s = 0;
		rtc_m += ((rtc_m & 0x0f) == 9)? 7:1;
		rtc_m += ((rtc_m & 0xf0) > 0x90)? 0x60:0;
		if (rtc_m > 0x59) {
			rtc_m = 0;
			rtc_h += ((rtc_m & 0x0f) == 9)? 7:1;
			rtc_h += ((rtc_m & 0xf0) > 0x90)? 0x60:0;
			if (rtc_h > 0x23) {
				rtc_h = 0;
			}
		}
	}
}


ISR (TIMER2_OVF_vect)
{
	static uint16_t licznik;

	if (licznik++ > 480) {
		licznik = 0;
		co_1s();
	}
}
#endif

void odczyt ()
{
	eeprom_read_block (dzwonki, (void *)0, sizeof (dzwonki));
	eeprom_read_block (&mode_auto, (void *)64, 1);
	eeprom_read_block (&dzwonek_czas, (void *)65, 1);
	eeprom_read_block (&lcd_kontrast, (void *)66, 1);
}

int main(void)
{
	TCCR0B |= (1<<CS01)|(1<<CS00);   //Preskaler = 1024
	TIMSK0 |= (1<<TOIE0);           //Wlacz przerw. dla Timera0

#ifdef EMU
	TCCR2B |= (1<<CS22)|(1<<CS20);   //Preskaler = 1024
	TIMSK2 |= (1<<TOIE2);           //Wlacz przerw. dla Timera2
#endif


	DZWONEK_DDR |= (1<<DZWONEK_PIN);
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UBRR0 = BAUD_PRESCALE;


	stdio_tm1637_init ();
	i2c_init ();
	KN_INIT();

	odczyt();//odczyt pamieci eeprom

	ustaw_kontrast ();
	sei();                           //Wlacz przerwania

	for(;;) main_loop();
	return 0;
}
