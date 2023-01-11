#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "backlight.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_all(
      QK_LEAD, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,  KC_BSPC,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,          KC_BSLS,   \
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_DOT,           KC_ENT,    \
      SC_LSPO, KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   SC_RSPC, KC_RGUI,      \
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                          MO(1),   KC_LEFT,  KC_DOWN, KC_UP,   KC_RIGHT),

  // 1: Function Layer
  LAYOUT_all(
      QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13, KC_F14,    \
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO, \
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO, \
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,      \
      KC_NO,   KC_NO,   KC_NO,                            KC_NO,                           MO(1),   KC_NO,    KC_NO,   KC_NO,  KC_NO),

};

// Loop
void matrix_scan_user(void) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = get_highest_layer(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
    case 0:
      rgblight_mode(1);
      rgblight_setrgb(0xFF, 0xFF, 0xFF);
      break;
    case 1:
      rgblight_mode(18);
      rgblight_setrgb(0x00, 0xFF, 0xFF);
      break;
    }

    old_layer = new_layer;
  }
};
