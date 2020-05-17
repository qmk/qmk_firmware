#include "wm1.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

  setPinOutput(B1); // Top Indicator LED
  setPinOutput(B0); // Middle Indicator LED
  setPinOutput(C5); // Bottom Indicator LED
  matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B1, led_state.caps_lock);
        writePin(B0, led_state.num_lock);
        writePin(C5, led_state.scroll_lock);
    }
    return true;
}