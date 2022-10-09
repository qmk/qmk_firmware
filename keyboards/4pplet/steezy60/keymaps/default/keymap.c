#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(
  KC_ESC,   KC_1,    KC_2,   KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,  KC_BSPC,
  KC_TAB,  	KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
  KC_LCTRL, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO, KC_ENT, 
  KC_LSFT, 	KC_NO,   KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO, KC_RSFT,  KC_NO,
  KC_LCTL, 	KC_LGUI, KC_NO,  KC_LALT, KC_NO,   KC_SPC, KC_NO, 			    KC_RALT, KC_RGUI, KC_NO,   KC_APP,  MO(1)),

[1] = LAYOUT_all(
  QK_BOOT,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  _______, KC_DEL, 
  _______, KC_BSPC, KC_UP,   KC_ENT,   _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,    _______, _______, 
  KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MUTE, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT, _______, _______,
  _______, _______, KC_MPRV, KC_MPLY,  KC_MNXT, KC_VOLD, KC_VOLU, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,  _______, _______, _______,
  _______, _______, _______, _______,  _______, _______, _______, KC_BRID, KC_BRIU, _______, _______, _______ )
};