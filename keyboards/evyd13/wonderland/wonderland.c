#include "wonderland.h"

__attribute__ ((weak))
void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init_ports();
};

__attribute__ ((weak))
void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
};

__attribute__ ((weak))
void led_init_ports(void) {
    // * Set our LED pins as output
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
}

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(B1, !led_state.num_lock);
      writePin(B2, !led_state.caps_lock);
      writePin(B3, !led_state.scroll_lock);
    }
    return runDefault;
}
