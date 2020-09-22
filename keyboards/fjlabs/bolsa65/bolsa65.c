#include "bolsa65.h"

void matrix_init_kb(void) {
	// Initialize indicator LEDs to output
    setPinOutput(F7); // Caps
	matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F7, led_state.caps_lock);
    }
    return res;
}