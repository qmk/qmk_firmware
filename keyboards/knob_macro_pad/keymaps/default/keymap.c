#include "knob_macro_pad.h"
#include "knob_v2.h"

#define _DEFAULT 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_Q,\
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Q,\
      KC_Q  ,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_Q,\
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_Q,\
      KC_LCTL, KC_LGUI, KC_LGUI, KC_LALT, KC_Q,    KC_SPC,  KC_Q,\
                                                   KC_SPC, KC_BSPC\
    ),
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
