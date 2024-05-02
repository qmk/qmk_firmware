#include "quantum.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	gpio_set_pin_output(C6);
	gpio_write_pin_low(C6);
	
	gpio_set_pin_output(D4);
	gpio_write_pin_low(D4);
	
	matrix_init_user();
	
}
