#include "sq80.h"

void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
};

void led_init_ports(void) {
	setPinOutput(D0);
	setPinOutput(D1);
	setPinOutput(D2);
	writePinHigh(D0);
	writePinHigh(D1);
	writePinHigh(D2);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(D0, !led_state.caps_lock);
        writePin(D1, !led_state.scroll_lock);
        writePin(D2, !led_state.num_lock);
    }
    return res;
}
