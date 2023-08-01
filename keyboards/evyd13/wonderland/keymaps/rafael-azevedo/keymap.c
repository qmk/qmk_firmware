#include QMK_KEYBOARD_H

#define CAPSTL CTL_T(KC_CAPS)

enum layers {
  _BASE,
  _GAME,
  _FUNC,
  _RGB
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
  KC_ESC, KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_PGUP,  KC_PGDN,
 KC_HOME, KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
 KC_END,  CAPSTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_DEL,  MO(2),
          TG(1),      SC_LAPO, KC_BSPC, KC_LGUI,     KC_SPC,       SC_RAPC,                   MO(3)
   ),
[_GAME] = LAYOUT(
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_BSPC,  _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,          _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
          _______,          _______, KC_SPC,  _______,          _______,                   _______,                             _______
   ),
[_FUNC] = LAYOUT(
 KC_PSCR, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX,
 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 _______, _______, KC_VOLU, KC_VOLD, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX,
          KC_LSFT, KC_BRIU, KC_BRID, _______,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,
          KC_MPLY,          KC_LALT, _______,  _______,          _______,                   KC_RALT,                            XXXXXXX
   ),
[_RGB] = LAYOUT(
 RGB_TOG, VK_TOGG,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, QK_BOOT,
 RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
RGB_RMOD, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX,
          KC_LSFT, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,
          _______,          KC_LALT, _______, _______,          _______,                   KC_RALT,                            XXXXXXX
   )
};
