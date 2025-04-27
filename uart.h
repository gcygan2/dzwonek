extern void uart_put (char c);
extern void uart_puts (const char *c);
extern char uart_get ();
extern uint8_t uart_get_hex ();
extern int8_t uart_get_dec ();
extern void uart_put_hex (uint8_t h);
extern void uart_put_dec (uint8_t h);
