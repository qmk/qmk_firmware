#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_default(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,         KC_U,   KC_I,    KC_O,   KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,         KC_J,   KC_K,    KC_L,   LT(3,KC_MINS),
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,         KC_M,   KC_COMM, KC_DOT, LT(4,KC_SLSH), KC_P1,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, LT(2,KC_BSPC), LT(1,KC_SPC), KC_ENT, KC_APP,  KC_DEL, KC_ESC,        KC_P2),
  [1] = LAYOUT_default(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TAB,  KC_NO,   KC_NO,   KC_GRV,  KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_QUOT, KC_MINS,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_EQL,  KC_MINS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [2] = LAYOUT_default(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,   KC_F7, KC_F8,   KC_F9,   KC_F10,
    KC_TAB,  KC_F11,  KC_F12,  KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,
    KC_CAPS, KC_PSCR, KC_SLCK, KC_PAUS, KC_NO, KC_NLCK, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO), KC_TRNS,
  [3] = LAYOUT_default(
    KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,
    KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS),
  [4] = LAYOUT_default(
    KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BTN1, KC_MS_U, KC_BTN2, KC_DEL,
    KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_WH_D, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS)
};
