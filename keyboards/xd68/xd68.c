#include "xd68.h"

void matrix_init_kb(void) {
	led_init_ports();
}

void led_init_ports(void) {
    // * Set our LED pins as output
    setPinOutput(B2);
    writePinHigh(B2);
}

bool led_update_kb(led_t led_state) {
    writePin(B2, !led_state.caps_lock);
    return true;
}

