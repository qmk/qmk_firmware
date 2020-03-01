#include "chimera_ortho.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void led_init(void) {
	DDRD  |= (1<<1);
	PORTD |= (1<<1);
	DDRF  |= (1<<4) | (1<<5);
	PORTF |= (1<<4) | (1<<5);
}


void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	uart_init();
	led_init();
}
