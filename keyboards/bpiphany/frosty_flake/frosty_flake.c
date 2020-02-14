#include "frosty_flake.h"

void keyboard_pre_init_kb() {
    setPinOutput(B7); // num lock
    writePinHigh(B7);
    setPinOutput(C5); // caps lock
    writePinHigh(C7);
    setPinOutput(C6); // scroll lock
    writePinHigh(C6);

    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

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

bool led_update_kb(led_t usb_led) {
    // user requests no further processing
    if (!led_update_user(usb_led))
        return true;

    writePin(C5, !usb_led.caps_lock);
    writePin(B7, !usb_led.num_lock);
    writePin(C6, !usb_led.scroll_lock);

    return true;
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
}

__attribute__ ((weak))
bool led_update_user(led_t usb_led) {
    return true;
}
