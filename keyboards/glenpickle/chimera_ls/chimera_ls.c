#include "chimera_ls.h"

void led_init(void) {
	gpio_set_pin_output(CHIMERA_LS_GREEN_LED_PIN);
	gpio_write_pin_high(CHIMERA_LS_GREEN_LED_PIN);
	gpio_set_pin_output(CHIMERA_LS_BLUE_LED_PIN);
	gpio_write_pin_high(CHIMERA_LS_BLUE_LED_PIN);
	gpio_set_pin_output(CHIMERA_LS_RED_LED_PIN);
	gpio_write_pin_high(CHIMERA_LS_RED_LED_PIN);
}


void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init();
}
