#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X0 LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
    KC_F, KC_X0, KC_LCTL,
    KC_R, KC_D,  KC_M
  ),

  [_FN] = LAYOUT(
    KC_F,    KC_TRNS, RGB_HUI,
    RGB_TOG, RGB_MOD, RGB_HUD
  )
};
