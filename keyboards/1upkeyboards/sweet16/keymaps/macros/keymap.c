#include QMK_KEYBOARD_H

#define RGB MO(_RGB)

enum layers {
 _BASE,
 _RGB
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_4x4(
  C(G(KC_Q)), _______, _______, RGB,
  _______,    _______, _______, _______,
  KC_VOLD,    KC_VOLU, _______, _______,
  KC_MPLY,    KC_MNXT, _______, RESET
),
[_RGB] = LAYOUT_ortho_4x4(
  _______, _______, _______,  _______,
  RGB_HUI, RGB_SAI, RGB_VAI,  _______,
  RGB_HUD, RGB_SAD, RGB_VAD,  _______,
  RGB_TOG, RGB_MOD, RGB_RMOD, _______
)

/*
[_NEW]=LAYOUT_ortho_4x4(
_______, _______, _______, _______,
_______, _______, _______, _______,
_______, _______, _______, _______,
_______, _______, _______, _______
)
*/
};
