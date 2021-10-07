#include "mw65_r2.h"

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
  { 0,      1,      2,      3,      4,      5,      6,      7 },
  { 8,      9,      10,     11,     12,     13,     14,    15 }
}, {
    { 175, 45 }, { 130, 45 }, { 85, 45 }, { 50, 45 }, {  15, 45 }, { 15, 35 }, { 15, 25 }, { 15, 10 }, { 50, 10 }, { 85, 10 }, { 130, 10 }, { 175, 10 }, { 210, 10 }, { 210, 25 }, { 210, 35 }, { 210, 45 },
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
