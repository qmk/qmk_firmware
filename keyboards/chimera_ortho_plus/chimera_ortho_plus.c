#include "chimera_ortho_plus.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void led_init(void) {
    setPinOutput(D1);
    setPinOutput(F4);
    setPinOutput(F5);
    writePinHigh(D1);
    writePinHigh(F4);
    writePinHigh(F5);
}


void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	uart_init();
	led_init();
}
