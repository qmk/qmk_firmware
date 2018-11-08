#include "knob_macro_pad.h"
#include "knob_v2.h"

#define _DEFAULT 0
#define _RST 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_ortho_1x3(
        LT(_RST, KC_MRWD), KC_MPLY, KC_MFFD
    ),

    [_RST] = LAYOUT_ortho_1x3(
        KC_TRNS, KC_TRNS, RESET
    )
};

void matrix_init_user(void) {
  knob_init();
}

void matrix_scan_user(void) {
  knob_report_t knob_report = knob_report_read();
  knob_report_reset();
  if (knob_report.phase) { // I check for phase to avoid handling the rotation twice (on 90 and 270 degrees).
    while (knob_report.dir > 0) {
      register_code(KC_VOLU);
      unregister_code(KC_VOLU);
      knob_report.dir--;
    }
    while (knob_report.dir < 0) {
      register_code(KC_VOLD);
      unregister_code(KC_VOLD);
      knob_report.dir++;
    }
  }
}
