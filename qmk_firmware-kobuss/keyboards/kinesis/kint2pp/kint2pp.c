#include "kint2pp.h"

void matrix_init_kb(void) {
	led_init_ports();


	matrix_init_user();
}
void led_init_ports() {
  // * Set our LED pins as output
  setPinOutput(C3); // Keypad LED
  setPinOutput(C4); // ScrLock LED
  setPinOutput(C5); // NumLock LED
  setPinOutput(C1); // CapsLock LED
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(C3, !led_state.compose);
        writePin(C4, !led_state.scroll_lock);
        writePin(C5, !led_state.num_lock);
        writePin(C1, !led_state.caps_lock);
    }
    return res;
}
