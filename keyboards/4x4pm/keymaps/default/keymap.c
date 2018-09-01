
#include QMK_KEYBOARD_H

#define PAD 0

// Readability keycodes
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Single 4x4 board only
 * .-----------------------------------.
 * |   7    |   8    |   9    |   /    |
 * |--------+--------+--------+--------|
 * |   4    |   5    |   6    |   *    |
 * |--------+--------+--------+--------|
 * |   1    |   2    |   3    |   -    |
 * |--------+--------+--------+--------|
 * |   0    | RESET  |   .    |   +    |
 * '-----------------------------------'
 */

  [PAD] = LAYOUT_ortho_4x4(
  KC_KP_7, KC_KP_8, KC_KP_9,   KC_PSLS,
  KC_KP_4, KC_KP_5, KC_KP_6,   KC_PAST,
  KC_KP_1, KC_KP_2, KC_KP_3,   KC_PMNS,
  KC_KP_0, RESET, KC_KP_DOT, KC_PPLS
  ),

};


const uint16_t PROGMEM fn_actions[] = {

};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  keyevent_t event = record->event;
    (void)event;

  switch (id) {

  }
  return MACRO_NONE;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
