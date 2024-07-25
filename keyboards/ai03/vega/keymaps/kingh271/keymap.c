#include QMK_KEYBOARD_H
#include "kingh271.h"
enum layer_names {
    _COLEMAK,
    _GAME,
    _FN1,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT_all(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_PSCR, 
		KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,          KC_BSPC,  KC_DEL,  
		KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,             DF(1), 
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,     MO(2), 
		KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT,   MO(2),          KC_LEFT, KC_DOWN, KC_RGHT 
	),

	[_GAME] = LAYOUT_all(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_PSCR, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC,  KC_DEL,  
		KC_F9,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,             DF(0), 
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,     MO(2), 
		KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT,   MO(2),          KC_LEFT, KC_DOWN, KC_RGHT 
	),

	[_FN1] = LAYOUT_all(
		QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_CATG,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,           KC_END, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, _______, 
		_______, _______, _______,          _______,          KC_MPLY,          _______,          _______, _______,          _______, KC_VOLD, _______  
	),

	[_FN2] = LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, 
		_______, _______, _______,          _______,          _______,          _______,          _______, _______,          _______, _______, _______  
	),

};

#ifdef KEY_CANCELLATION_ENABLE
const key_cancellation_t PROGMEM key_cancellation_list[] = {
    // on key down
    //       |    key to be released
    //       |     |
    [0] = {KC_D, KC_A},
    [1] = {KC_A, KC_D}
};
#endif
