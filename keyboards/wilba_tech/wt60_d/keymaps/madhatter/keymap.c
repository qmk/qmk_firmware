// Default layout for WT60-D
#include QMK_KEYBOARD_H

enum my_layers {
  _QWERTY,
  _FNMS,
};

#define FNMS MO(_FNMS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default layer
[_QWERTY] = LAYOUT_all(
	KC_GESC, KC_1,    KC_2,   KC_3,  KC_4, KC_5, KC_6,  KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
	KC_TAB,  KC_Q,    KC_W,   KC_E,  KC_R, KC_T, KC_Y,  KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
	KC_GRV,  KC_A,    KC_S,   KC_D,  KC_F, KC_G, KC_H,  KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_NO,   KC_Z,   KC_X,  KC_C, KC_V, KC_B,  KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FNMS,
	KC_LCTL, KC_LALT, KC_LCMD,                   KC_SPC,                     KC_SPC,  FNMS,    KC_RALT, KC_RCTL),

// Fn1 Layer
[_FNMS] = LAYOUT_all(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSLS,  KC_TRNS,
	KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, QK_BOOT,
	AG_TOGG, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RGHT, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};
