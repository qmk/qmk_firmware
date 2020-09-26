#include "comet46.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	uart_init();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {

}
