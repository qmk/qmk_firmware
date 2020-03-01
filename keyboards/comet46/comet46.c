#include "comet46.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void matrix_init_kb(void) {
	uart_init();
}
