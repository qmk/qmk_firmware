#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
  _LAYER0,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _LAYER4,
  _LAYER5,
  _LAYER6,
  _LAYER7,
  _LAYER8,
  _LAYER9
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER1] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER2] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER3] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER4] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER5] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER6] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER7] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER8] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J),
  [_LAYER9] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_NO, KC_NO, KC_J)
};

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    backlight_level(0);
  #endif
}
