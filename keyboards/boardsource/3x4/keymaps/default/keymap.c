#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _RAISE,
    _LOWER,
};

// Readability keycodes
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT(
  KC_0,  KC_1,    KC_4,    KC_7, 
  KC_ENT,  KC_2,    KC_5,    KC_8, 
  RAISE,  KC_3,    KC_6,    KC_9
  ),
  [_RAISE] = LAYOUT(
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, QK_BOOT
  )

};
