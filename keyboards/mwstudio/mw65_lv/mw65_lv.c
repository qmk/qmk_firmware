#include "mw65_lv.h"

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

led_config_t g_led_config = { {
  { 0,      1,      2,      3,      4 },
  { 5,      6,      7,      8,      9 },
  { 10,     11,     12,     13,     14 },
  { 15,     16,     17 }
}, {
    { 95, 54 }, { 109, 54 }, { 123, 54 }, { 137, 54 }, { 151, 54 },
    { 15, 10 }, { 15, 20 }, { 15, 30 }, { 15, 40 }, { 15, 50 },
    { 220, 50 }, { 220, 40 }, { 220, 30 }, { 220, 20 }, { 220, 10 },
    { 7, 6 },{ 116, 30 }, { 217, 54 },
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
