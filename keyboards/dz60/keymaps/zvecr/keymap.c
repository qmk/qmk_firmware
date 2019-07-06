#include QMK_KEYBOARD_H

/*
* Each layer gets a name for readability.
* The underscores don't mean anything - you can
* have a layer called STUFF or any other name.
* Layer names don't all need to be of the same
* length, and you can also skip them entirely
* and just use numbers.
*
*/
#define BL 0     // Base Layer
#define FL 1     // Function Layer
#define ML 2     // Macro Layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BL] = LAYOUT_60_ansi_split(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,          KC_SPC,  MO(FL),  KC_SPC,                             KC_RALT, KC_RGUI,          MO(ML),  KC_RCTL),

	[FL] = LAYOUT_60_ansi_split(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		_______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,
		_______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, KC_DEL,  KC_END,  KC_PGDN,          _______,
		_______, _______,          _______,          _______, _______, _______,                            _______, _______,          _______, _______),


	[ML] = LAYOUT_60_ansi_split(
		_______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,           _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______, _______,          _______,          _______, _______, _______,                            _______, _______,          _______, _______),

};
