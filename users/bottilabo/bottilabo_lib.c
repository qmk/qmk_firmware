#include QMK_KEYBOARD_H
#include "bottilabo.h"

__attribute__((weak))
void matrix_init_local(void) {
}
__attribute__((weak))
void matrix_scan_local(void) {
}
__attribute__((weak))
bool process_record_local(uint16_t keycode, keyrecord_t *record) {
  return true;
}

