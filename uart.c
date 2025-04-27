#include <avr/io.h>

void uart_put (char c)
{
	while ( !( UCSR0A & (1<<UDRE0)) ); 
	UDR0 = c;	
}

void uart_puts (const char *c)
{
	while (*c) {
		while ( !( UCSR0A & (1<<UDRE0)) ); 
		UDR0 = *c;
		c++;
	}
}

char uart_get ()
{
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

uint8_t uart_get_hex ()
{
	char c;
	uint8_t b;

	c = uart_get();
	uart_put (c);
	if (c < 'a') b = (c - '0') << 4;
	else b = (c - 'a' + 10) << 4;

	c = uart_get();
	uart_put (c);
	if (c < 'a') b |= c - '0';
	else b |= c - 'a' + 10;

	return b;
}

int8_t uart_get_dec ()
{
	char c;
	int8_t b;

	c = uart_get();
	uart_put (c);
	b = (c - '0') * 10;
	c = uart_get();
	uart_put (c);
	b += c - '0';
	return b;
}

void uart_put_hex (uint8_t h)
{
	uint8_t c, l;

	l = h >> 4;
	if (l < 10) c = l + '0';
	else c = l - 10 + 'a';
	uart_put (c);
	l = h & 0xf;
	if (l < 10) c = l + '0';
	else c = l - 10 + 'a';
	uart_put (c);
}

void uart_put_dec (uint8_t h)
{
	uint8_t c, l;

	l = h / 10;
	c = l + '0';
	uart_put (c);

	l = h % 10;
	c = l + '0';
	uart_put (c);
}
