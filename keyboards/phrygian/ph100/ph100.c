#include "ph100.h"

void keyboard_pre_init_user(void) {
    setPinOutput(B14); //Numlock led
    setPinOutput(B15); //Capslock led

    writePin(B15, 0);
    writePin(B14, 0);
}

void matrix_init_kb(void) {
    matrix_init_user();
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    writePin(B14, led_state.num_lock);
    writePin(B15, led_state.caps_lock);
    return res;
}
