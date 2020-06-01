
#include QMK_KEYBOARD_H

#define _MAIN 0
#define _RAISE 1
#define _LOWER 2

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
    _______, _______, _______, RESET
  )

};
