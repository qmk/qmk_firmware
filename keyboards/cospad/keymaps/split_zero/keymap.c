#include QMK_KEYBOARD_H

/* 
 *  This keymap is based on the default keymap for the cospad.
 *  It was adapted for the split 0 layout focusing on the "00" key.
 */

enum custom_keycodes {
  DBL_ZRO = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DBL_ZRO:
      if (record->event.pressed) {
        // when keycode DBL_ZRO is pressed
        SEND_STRING("00");
      } else {
        // when keycode DBL_ZRO is released
      }
      break;

  }
  return true;
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BL,
    _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
     * ,-------------------.
     * |Esc |TAB | FN | BS |
     * |----|----|----|----|
     * | NL | /  | *  | -  |
     * |----|----|----|----|
     * | 7  | 8  | 9  |    |
     * |----|----|----| +  |
     * | 4  | 5  | 6  |    |
     * |----|----|----|----|
     * | 1  | 2  | 3  |    |
     * |----|----|----| En |
     * | 0  | 00 | .  |    |
     * `-------------------'
     */
    [_BL] = LAYOUT_numpad_6x4_split_zero(
        KC_ESC,  KC_TAB,  MO(_FL), KC_BSPC,
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   DBL_ZRO, KC_PDOT, KC_PENT
    ),
        
    /* Keymap _FL: Function Layer
     * ,-------------------.
     * |RGBT|    |    |    |
     * |----|----|----|----|
     * |RGBM|RGBP|BTOG|    |
     * |----|----|----|----|
     * |HUD |HUI |BON |    |
     * |----|----|----|    |
     * |SAD |SAI |BOFF|    |
     * |----|----|----|----|
     * |VAD |VAS |BSTP|    |
     * |----|----|----|    |
     * |    |    |RST |    |
     * `-------------------'
    */
    [_FL] = LAYOUT_numpad_6x4_split_zero(
        RGB_TOG, _______, _______, _______,
        RGB_MOD, RGB_M_P, BL_TOGG, _______,
        RGB_HUD, RGB_HUI, BL_ON,
        RGB_SAD, RGB_SAI, BL_OFF,  _______,
        RGB_VAD, RGB_VAI, BL_STEP,
        _______, _______, RESET,   _______
    )
};
