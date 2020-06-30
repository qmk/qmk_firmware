#include "annepro2.h"

void OVERRIDE matrix_init_kb(void) {
    matrix_init_user();
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}
