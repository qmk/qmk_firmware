#include QMK_KEYBOARD_H

#define _QW 0
#define _NV 1
#define _NM 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QW] = LAYOUT_ortho_5x15(
  KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_GRV , KC_BSPC,
  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
  MO(_NV), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , MO(_NM), KC_PGUP,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______, KC_RSFT, KC_UP  , KC_PGDN,
  KC_LCTL, KC_LGUI, KC_LALT, KC_SPC , KC_SPC , KC_SPC , KC_SPC , KC_SPC , KC_SPC , KC_RALT, KC_RGUI, KC_APP , KC_LEFT, KC_DOWN, KC_RGHT
 ),
 [_NV] = LAYOUT_ortho_5x15(
  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______,
  _______, _______, _______, _______, KC_DEL , KC_BSPC, _______, KC_HOME, KC_UP  , KC_END , KC_INS , _______, _______, _______, _______,
  _______, _______, _______, KC_LSFT, KC_LCTL, KC_ENT , _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_NM] = LAYOUT_ortho_5x15(
  _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )
};
