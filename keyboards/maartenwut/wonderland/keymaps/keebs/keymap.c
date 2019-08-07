#include QMK_KEYBOARD_H

#define ___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  KC_ESC, KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, \
  KC_F10, KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
 RGB_HUI, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,          KC_ENT, \
          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1), \
          KC_LCTL,       KC_LAPO, KC_LGUI, RGUI(KC_SPC), KC_SPC, KC_RAPC,                     KC_RCTRL \
   ),
[1] = LAYOUT(
         RGB_TOG, VLK_TOG, KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9, KC_F10, KC_F11, KC_F12, ___, RESET, \
RGB_MODE_FORWARD, ___,   ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,    ___,    ___,    ___, ___, \
RGB_MODE_REVERSE, ___,   ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,    ___,  KC_UP,         ___, \
              KC_LSFT, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ___,  ___,  ___,KC_LEFT,KC_DOWN,KC_RIGHT,___, \
              KC_LCTL,     KC_LALT, KC_BSPC, KC_LGUI,      KC_SPC,  KC_RALT,                          KC_RCTRL \
   )
};


