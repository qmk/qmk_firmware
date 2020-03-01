#include "wonderland.h"

__attribute__ ((weak))
void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	led_init_ports();
};

__attribute__ ((weak))
void led_init_ports(void) {
    // * Set our LED pins as output
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
}

bool led_update_kb(led_t led_state) {
    writePin(B1, !led_state.num_lock);
    writePin(B2, !led_state.caps_lock);
    writePin(B3, !led_state.scroll_lock);
    return true;
}
