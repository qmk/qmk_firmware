#include QMK_KEYBOARD_H;

// Increase reaeabolity of transparent keys
#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_default(
	// Main Layer
	KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_HOME, KC_MPLY, KC_VOLD, KC_VOLU, KC_F24, \
	KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_W, KC_PSLS, KC_PAST, KC_PMNS, \
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_7, KC_8, KC_9, KC_PPLS, \
	KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_4, KC_5, KC_6, \
	KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, KC_1, KC_2, KC_3, KC_ENT, \
	KC_LCTL, LT(1,KC_LGUI), KC_LALT, KC_SPC, LT(1,KC_RALT), KC_NO, LT(1,KC_RCTL), KC_LEFT, KC_DOWN, KC_RGHT, KC_0, KC_E
	),

	[1] = LAYOUT_default(
	// Holding CTRL Layer
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_PSCR, KC_END, KC_MUTE, KC_MPRV, KC_MNXT, KC_F23, \
	____, ____, ____, ____, UC(0xC2), ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_NLCK, ____, ____, ____, \
	____, LCTL(KC_X), LCTL(KC_COMM), LCTL(KC_D), LCTL(KC_O), LCTL(KC_K), LCTL(KC_T), LCTL(KC_F), LCTL(KC_G), LCTL(KC_S), LCTL(KC_R), ____, ____, ____, KC_P7, KC_P8, KC_P9, ____, \
	____, LCTL(KC_A), LCTL(KC_SCLN), LCTL(KC_H), LCTL(KC_Y), LCTL(KC_U), LCTL(KC_J), LCTL(KC_C), LCTL(KC_V), LCTL(KC_P), ____, ____, ____, KC_P4, KC_P5, KC_P6, \
	____, LCTL(KC_SLSH), LCTL(KC_B), LCTL(KC_I), LCTL(KC_DOT), LCTL(KC_N), LCTL(KC_L), LCTL(KC_M), ____, ____, ____, ____, ____, KC_P1, KC_P2, KC_P3, ____, \
	MO(2), ____, ____, ____, ____, KC_NO, ____, ____, ____, ____, KC_P0, KC_PDOT
	),
	
	[2] = LAYOUT_default(
	// Holding LGUI Layer
	RESET, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
	____, LGUI(KC_X), LGUI(KC_COMM), LGUI(KC_D), LGUI(KC_O), LGUI(KC_K), LGUI(KC_T), LGUI(KC_F), LGUI(KC_G), LGUI(KC_S), LGUI(KC_R), ____, ____, ____, ____, ____, ____, \
	____, ____, LGUI(KC_A), LGUI(KC_SCLN), LGUI(KC_H), LGUI(KC_Y), LGUI(KC_U), LGUI(KC_J), LGUI(KC_C), LGUI(KC_V), LGUI(KC_P), ____, ____, ____, ____, ____, ____, \
	____, LGUI(KC_SLSH), LGUI(KC_B), LGUI(KC_I), LGUI(KC_DOT), LGUI(KC_N), LGUI(KC_L), LGUI(KC_M), ____, ____, ____, ____, ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
	)

};
