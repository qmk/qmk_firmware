#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Default layer
	* ,----------------------------------------------------------------------------------------------------------------------------.
	* | GrvEsc|   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   +   |   ´   | Backspace  | MacOS |
	* |----------------------------------------------------------------------------------------------------------------------------|
	* | Tab      |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   Å   |   ¨   |  Enter  | Del   |
	* |-----------------------------------------------------------------------------------------------------------,        |-------|
	* | Mod Layer |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   Ö   |   Ä   |   '   |        | PgUp  |
	* |----------------------------------------------------------------------------------------------------------------------------|
	* | Shift   |   <  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   -   |   Shift   |  Up   | PgDn  |
	* |----------------------------------------------------------------------------------------------------------------------------|
	* | Control | Option | Command |                         Space                 | Cmnd  | Opt   | ModLr | Left  | Down  | Right |
	* `----------------------------------------------------------------------------------------------------------------------------'
	*/

	[_BL] = LAYOUT_iso(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, AG_NORM,  \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
		MO(_FL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, KC_RALT, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT
	),

	/* Modifier layer
	* ,----------------------------------------------------------------------------------------------------------------------------.
	* | Esc   |       |       |       |       |       |       |       |   [   |   ]   |       |       |       |   Delete   |Windows|
	* |----------------------------------------------------------------------------------------------------------------------------|
	* |          |       |       |       |       |       |       | PgUp  |   Up  | PgDn  |       |       |       |         |       |
	* |-----------------------------------------------------------------------------------------------------------,        |-------|
	* |           |       |Scrnsht|Desktop|       |       |       | Left  | Down  | Right |       |       |       |        | VolUp |
	* |----------------------------------------------------------------------------------------------------------------------------|
	* | Shift   |      |       |       |       | BL-   |BL Togg| BL+   |       |       |       |       |   Shift   | Play  | VolDn |
	* |----------------------------------------------------------------------------------------------------------------------------|
	* |         |        |         |                                               |       |       |       | Prev  | Mute  | Next  |
	* `----------------------------------------------------------------------------------------------------------------------------'
	*/

	[_FL] = LAYOUT_iso(
		KC_ESC,  _______, _______,    _______, _______, _______, _______, _______, RALT(KC_8), RALT(KC_9), _______, _______, _______, KC_DEL,   AG_SWAP, \
		_______, _______, _______,    _______, _______, _______, _______, KC_PGUP, KC_UP,      KC_PGDN,    _______, _______, _______,           _______,  \
		_______, _______, SGUI(KC_5), KC_F11,  _______, _______, _______, KC_LEFT, KC_DOWN,    KC_RGHT,    _______, _______, _______, _______,  KC__VOLUP, \
		KC_LSFT, _______, _______,    _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______,    _______,    _______, _______, KC_RSFT, KC_MPLY,  KC__VOLDOWN,  \
		_______, _______, _______,                      _______,                               _______,    _______, _______, KC_MRWD, KC__MUTE, KC_MFFD
	),

};
