#include QMK_KEYBOARD_H
#include "hotdox.h"
#include "quantum.h"
#include "version.h"

extern keymap_config_t keymap_config;

#define KC____  KC_TRNS // three underscores "___" for transparent

// Layer names
#define _QWERTY 0 // default layer
#define _NUMB   1 // symbols
#define _MDIA   2 // media keys


enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	NUMB,
	MDIA,
};

// Tap Dance Declarations 
enum {
	TD_RIGHT_END = 0,
	TD_LEFT_HOME,
	TD_RSFT_CAPS,
};

// Tap Dance Definitions 
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
	[TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
	[TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

#define KC_REND TD(TD_RIGHT_END)
#define KC_LOME TD(TD_LEFT_HOME)
#define KC_RCAP TD(TD_RSFT_CAPS)

#define KC_TGNB TG(_NUMB)
#define KC_TGMD TG(_MDIA)
#define KC_MONB MO(_NUMB)
#define KC_MOMD MO(_MDIA)
#define KC_RESET RESET


// Custom per-key tapping term
uint16_t get_tapping_term(uint16_t keycode) {
	switch (keycode) {
		case KC_CAPS:
			return TAPPING_TERM + 125;
		default:
			return TAPPING_TERM;
		}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  |           |BkTick|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |   [    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSlsh |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------| MO(2)|           | MO(1)|------+------+------+------+------+--------|
 * | LSFT   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |RSFT/CAP|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL | LALT | GUI  |L/HOME|R/END |                                       |  Up  | Down | LEFT | RIGHT| PRSCR|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | DEL  | INS  |       | Ctrl |  Alt |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Enter|MO(1) |------|       |------|  Bksp  |Space |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[_QWERTY] = LAYOUT_ergodox_kc(
	// Left hand
	EQL, 	1, 		2, 		3, 		4, 		5, 		ESC, 
	TAB, 	Q, 		W, 		E, 		R, 		T, 		TGNB, 
	BSLS, 	A, 		S, 		D, 		F, 		G, 
	LSFT, 	Z, 		X, 		C, 		V, 		B, 		MOMD, 
	LCTL, 	LALT, 	LGUI, 	LOME, 	REND, 	
											DEL, 	INS, 	
													HOME, 
									ENT, 	MONB, 	
													END, 
	// Right hand
	GRV, 	6, 		7, 		8, 		9, 		0, 		MINS, 
	TGMD,	Y, 		U, 		I, 		O, 		P, 		LBRC, 
			H, 		J, 		K, 		L, 		SCLN, 	QUOT, 
	MONB, 	N, 		M, 		COMM, 	DOT, 	SLSH, 	RCAP, 
					UP, 	DOWN, 	LEFT, 	RGHT, 	PSCR, 
	LCTL, 	LALT, 	
	PGUP, 	
	PGDN, 	BSPC, 	SPC
	),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |   7  |   8  |   9  |   *  |   /  |    ]   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|   4  |   5  |   6  |   +  |   -  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |   1  |   2  |   3  |   =  |  up  |  enter |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |         |      |      | PgUp | PgDn |                                       |   0  |   .  | left | down |right |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      | Del  | Esc  |
 *                                 | Enter|      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_NUMB] = LAYOUT_ergodox_kc(
	// Left hand
	___, 	F1, 	F2, 	F3, 	F4, 	F5, 	___, 
	___, 	___, 	___, 	___, 	___, 	___, 	___, 
	___, 	___, 	___, 	___, 	___, 	___, 
	___, 	___, 	___, 	___, 	___, 	___, 	___,
	___, 	___, 	___, 	PGUP, 	PGDN, 
					___, 	___, 	___, 
					ENT, 	___, 	___, 
	// Right hand
	F12, 	F6, 	F7, 	F8, 	F9, 	F10, 	F11,
	___, 	7, 		8, 		9, 		PAST, 	PSLS, 	RBRC, 
			4, 		5, 		6, 		PPLS, 	PMNS, 	___, 
	___, 	1, 		2, 		3, 		PEQL, 	UP,		PENT, 
					0, 		PDOT, 	LEFT, 	DOWN, 	RGHT, 
					___, 	___, 	___, 
					___, 	DEL, 	ESC
	),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |RESET |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_MDIA] = LAYOUT_ergodox_kc(
	// Left hand
	___, 	___, 	___, 	___, 	___, 	___, 	___, 
	___, 	___, 	___, 	MS_U, 	___, 	___, 	___, 
	___, 	___, 	MS_L, 	MS_D, 	MS_R, 	___, 
	___, 	___, 	___, 	___, 	___, 	___, 	___, 
	___, 	___, 	___, 	BTN1, 	BTN2, 
					RESET, 	___, 	___, 
					___, 	___, 	___, 
	// Right hand								
	___, 	___, 	___, 	___, 	___, 	___, 	___, 
	___, 	___, 	___, 	___, 	___, 	___, 	___, 
			___, 	___, 	___, 	___, 	___, 	MPLY, 
	___, 	___, 	___, 	MPRV, 	MNXT, 	___, 	___, 
					VOLU, 	VOLD, 	MUTE, 	___, 	___, 
					___, 	___, 	___, 
					___, 	___, 	WBAK
	)
};
