#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x4(
        KC_PSLS, KC_PMNS, KC_PAST, KC_MPLY,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_TAB,
        LT(2,KC_P0), KC_PCMM, KC_PDOT, LT(1,KC_PENT)),
    [1] = LAYOUT_ortho_5x4(
        KC_NUM,  KC_UNDS, KC_NO,   KC_NO,
        KC_AMPR, KC_ASTR, KC_LPRN, KC_EQL,
        KC_DLR,  KC_PERC, KC_CIRC, KC_NO,
        KC_EXLM, KC_AT,   KC_HASH, KC_NO,
        KC_RPRN, KC_NO,   KC_PSLS, KC_NO),
    [2] = LAYOUT_ortho_5x4(
        KC_NUM,  KC_NO,   KC_NO,   KC_NO,
        MS_BTN1, MS_UP,   MS_BTN2, KC_NO,
        MS_LEFT, MS_DOWN, MS_RGHT, KC_TAB,
        MS_WHLU, KC_NO,   MS_WHLD, KC_NO,
        KC_NO,   KC_NO,   KC_DEL,  KC_ESC)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(MS_WHLU); /*mouse wheel up*/
    } else {
      tap_code(MS_WHLD); /*mouse wheel down */
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_VOLD); /*volume down*/
    } else {
      tap_code(KC_VOLU); /*volume up*/
    }
  }
    return true;
}
