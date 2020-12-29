#include "nguyenvietyen.h"

void matrix_init_kb(void) {
    led_init_ports();
    matrix_init_user();
}

void led_init_ports() {
    // * Set our LED pins as output
    setPinOutput(D7);  // Keypad LED
    setPinOutput(C6);  // ScrLock LED
    setPinOutput(D4);  // NumLock LED
    setPinOutput(E6);  // CapsLock LED

    // turn all LEDs off by default
    writePinHigh(D7);
    writePinHigh(C6);
    writePinHigh(D4);
    writePinHigh(E6);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(D7, !led_state.compose);
        writePin(C6, !led_state.scroll_lock);
        writePin(D4, !led_state.num_lock);
        writePin(E6, !led_state.caps_lock);
    }
    return res;
}
