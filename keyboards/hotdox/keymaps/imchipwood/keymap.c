#include QMK_KEYBOARD_H
#include "quantum.h"
#include "version.h"

// Layer names
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys


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
[BASE] = LAYOUT_ergodox(
	// Left hand
	KC_EQL, 			KC_1, 		KC_2, 		KC_3, 				KC_4, 				KC_5, 		KC_ESC, 
	KC_TAB, 			KC_Q, 		KC_W, 		KC_E, 				KC_R, 				KC_T, 		TG(1), 
	KC_BSLS, 			KC_A, 		KC_S, 		KC_D, 				KC_F, 				KC_G, 
	KC_LSFT, 			KC_Z, 		KC_X, 		KC_C, 				KC_V, 				KC_B, 		MO(2), 
	KC_LCTL, 			KC_LALT, 	KC_LGUI, 	KC_LOME, 			KC_REND, 	
									KC_DEL, 	KC_INS, 			KC_HOME, 
									KC_ENT, 	MO(1), 				KC_END, 
	// Right hand
	KC_GRV, 			KC_6, 		KC_7, 		KC_8, 				KC_9, 				KC_0, 		KC_MINS, 
	TG(2), 				KC_Y, 		KC_U, 		KC_I, 				KC_O, 				KC_P, 		KC_LBRC, 
						KC_H, 		KC_J, 		KC_K, 				KC_L, 				KC_SCLN, 	KC_QUOT, 
	MO(1), 				KC_N, 		KC_M, 		KC_COMM, 			KC_DOT, 			KC_SLSH, 	KC_RCAP, 
									KC_UP, 		KC_DOWN, 			KC_LEFT, 			KC_RGHT, 	KC_PSCR, 
									KC_LCTL, 	KC_LALT, 			KC_PGUP, 	
									KC_PGDN, 	KC_BSPC, 			KC_SPC
	),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   7  |   8  |   9  |   *  |   /  |    ]   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------|   4  |   5  |   6  |   +  |   -  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   1  |   2  |   3  |   =  |  up  |  enter |
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
[SYMB] = LAYOUT_ergodox(
	// Left hand
	KC_TRNS, 			KC_F1, 		KC_F2, 		KC_F3, 				KC_F4, 				KC_F5, 		KC_TRNS, 
	KC_TRNS, 			KC_EXLM, 	KC_AT, 		KC_LCBR, 			KC_RCBR, 			KC_PIPE, 	KC_TRNS, 
	KC_TRNS, 			KC_HASH, 	KC_DLR, 	KC_LPRN, 			KC_RPRN, 			KC_GRV, 
	KC_TRNS, 			KC_PERC, 	KC_CIRC, 	KC_LBRC, 			KC_RBRC, 			KC_TILD, 	KC_TRNS,
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_PGUP, 			KC_PGDN, 
									KC_TRNS, 	KC_TRNS, 			KC_TRNS, 
									KC_ENT, 	KC_TRNS, 			KC_TRNS, 
	// Right hand
	KC_F12, 			KC_F6, 		KC_F7, 		KC_F8, 				KC_F9, 				KC_F10, 	KC_F11,
	KC_TRNS, 			KC_7, 		KC_8, 		KC_9, 				KC_PAST, 			KC_PSLS, 	KC_RBRC, 
						KC_4, 		KC_5, 		KC_6, 				KC_PPLS, 			KC_PMNS, 	KC_TRNS, 
	KC_TRNS, 			KC_1, 		KC_2, 		KC_3, 				KC_PEQL, 			KC_UP, 		KC_PENT, 
									KC_0, 		KC_PDOT, 			KC_LEFT, 			KC_DOWN, 	KC_RGHT, 
									KC_TRNS, 	KC_TRNS, 			KC_TRNS, 
									KC_TRNS, 	KC_DEL, 			KC_ESC
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
[MDIA] = LAYOUT_ergodox(
	// Left hand
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 			KC_TRNS, 	KC_TRNS, 
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_MS_U, 			KC_TRNS, 			KC_TRNS, 	KC_TRNS, 
	KC_TRNS, 			KC_TRNS, 	KC_MS_L, 	KC_MS_D, 			KC_MS_R, 			KC_TRNS, 
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 			KC_TRNS, 	KC_TRNS, 
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_BTN1, 			KC_BTN2, 
									RESET, 		KC_TRNS, 			KC_TRNS, 
									KC_TRNS, 	KC_TRNS, 			KC_TRNS, 
	// Right hand								
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 			KC_TRNS, 	KC_TRNS, 
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 			KC_TRNS, 	KC_TRNS, 
						KC_TRNS, 	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 			KC_TRNS, 	KC_MPLY, 
	KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_MPRV, 			KC_MNXT, 			KC_TRNS, 	KC_TRNS, 
									KC_VOLU, 	KC_VOLD, 			KC_MUTE, 			KC_TRNS, 	KC_TRNS, 
									KC_TRNS, 	KC_TRNS, 			KC_TRNS, 
									KC_TRNS, 	KC_TRNS, 			KC_WBAK
	)
};
