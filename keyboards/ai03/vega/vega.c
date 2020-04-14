#include "vega.h"

void matrix_init_kb(void) {
	// Initialize indicator LEDs to output
    
    setPinOutput(B7); // Caps
	setPinOutput(A5); // Slck

	matrix_init_user();
}

bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);

    if(res) {
        writePin(B7, !led_state.caps_lock);
        writePin(A5, !led_state.scroll_lock);
    }
    return res;
}