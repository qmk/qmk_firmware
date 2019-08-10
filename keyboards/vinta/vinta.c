#include "vinta.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    return process_record_user(keycode, record);
}