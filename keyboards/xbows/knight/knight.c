#include "knight.h"

void matrix_init_kb(void) {
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(D1);
    writePinHigh(D1);
    setPinOutput(C7);
    writePinHigh(C7);
}
bool led_update_kb(led_t led_state) {
    writePin(C7, !led_state.caps_lock);
    writePin(D1, !led_state.num_lock);
    return true;
}
