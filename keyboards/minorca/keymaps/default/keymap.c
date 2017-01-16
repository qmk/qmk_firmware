#include "minorca.h"

enum layers {
	MINORCA = 0,
	MINORCA_ORIG,
	COLEMAK,
	DVORAK,
	HHKB,
	OSX,
	ARROW,
	NUMFUNC,
	LAYOUT_SELECT,
	NUMFUNC_V2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[MINORCA] =
		KEYMAP(
			KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,    KC_U, KC_I,    KC_O,   KC_P, KC_BSPC, \
			KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,    KC_J, KC_K,    KC_L,   KC_ENT, \
			KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH, \
			KC_LSFT, KC_LALT,KC_FN2, KC_SPC, KC_SPC, KC_FN0, KC_QUOT, KC_FN1),
	[MINORCA_ORIG] =
		KEYMAP(
			KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,    KC_U, KC_I,    KC_O,   KC_P, KC_BSPC, \
			KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,    KC_J, KC_K,    KC_L,   KC_ENT, \
			KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH, \
			KC_LCTL, KC_LALT,KC_FN2, KC_SPC, KC_SPC, KC_FN0, KC_QUOT, KC_FN1),
	[COLEMAK] =
		KEYMAP(
			KC_ESC,  KC_Q,    KC_W,   KC_F,   KC_P,    KC_G,   KC_J,    KC_L, KC_U,    KC_Y,   KC_RGUI, KC_BSPC, \
			KC_BSPC, KC_A,    KC_R,   KC_S,   KC_T,    KC_D,   KC_H,    KC_N, KC_E,    KC_I,   KC_O, \
			KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,    KC_B,   KC_K,    KC_M, KC_COMM, KC_DOT, KC_SLSH, \
			KC_LCTL, KC_LALT, KC_FN2, KC_SPC, KC_CAPS, KC_FN0, KC_QUOT, KC_FN1),
	[DVORAK] =
		KEYMAP(
			KC_GRV,  KC_QUOT, KC_COMM, KC_DOT, KC_P,   KC_Y,   KC_F,    KC_G, KC_C, KC_R, KC_L, KC_BSPC, \
			KC_TAB,  KC_A,    KC_O,    KC_E,   KC_U,   KC_I,   KC_D,    KC_H, KC_T, KC_N, KC_S, \
			KC_LSFT, KC_SCLN, KC_Q,    KC_J,   KC_K,   KC_X,   KC_B,    KC_M, KC_W, KC_V, KC_Z, \
			KC_LCTL, KC_LALT, KC_FN2,  KC_SPC, KC_DEL, KC_FN0, KC_QUOT, KC_FN1),
	[HHKB] =
		KEYMAP(
			KC_GRV,  KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,   KC_Y,    KC_U, KC_I,    KC_O,   KC_P, KC_DEL, \
			KC_TAB,  KC_A,    KC_S,   KC_D,    KC_F,   KC_G,   KC_H,    KC_J, KC_K,    KC_L,   KC_ENT, \
			KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,   KC_B,   KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH, \
			KC_LSFT, KC_LALT, KC_FN2, KC_CAPS, KC_SPC, KC_FN0, KC_QUOT, KC_FN1),
	[OSX] =
		KEYMAP(
			KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U, KC_I,    KC_O,   KC_P, KC_BSPC, \
			KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J, KC_K,    KC_L,   KC_ENT, \
			KC_LGUI, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH, \
			KC_LSFT, KC_LCTL, KC_LALT, KC_SPC, KC_SPC, KC_FN0, KC_QUOT, KC_FN14),
	[ARROW] =
		KEYMAP(
			KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_LEFT, KC_UP,   KC_RIGHT, \
			KC_TRNS, KC_TRNS, KC_FN2,  KC_FN9,  KC_TRNS, KC_FN0, KC_DOWN, KC_FN1),
	[NUMFUNC] =
		KEYMAP(
			KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL, \
			KC_CAPS, KC_HOME, KC_TRNS, KC_TRNS, KC_PGUP, KC_HOME, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_ENT, \
			KC_TRNS, KC_END,  KC_FN9,  KC_INS,  KC_PGDN, KC_END,  KC_SCLN, KC_BSLS, KC_LEFT, KC_UP,   KC_RIGHT, \
			KC_TRNS, KC_TRNS, KC_FN2,  KC_LCTL, KC_SPC,  KC_FN0,  KC_DOWN, KC_RSFT),
	[LAYOUT_SELECT] =
		KEYMAP(
			KC_FN5,  KC_FN6,  KC_FN7, KC_FN8,  KC_FN3,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_HOME, RESET, \
			KC_PGUP, KC_FN5,  KC_FN8, KC_LSFT, KC_RSFT, KC_PAUS, KC_FN29, KC_FN28, KC_PGDN, KC_END,  KC_INS, \
			KC_PGDN, KC_FN11, KC_FN7, KC_FN6,  KC_LGUI, KC_L,    KC_TRNS, KC_TRNS, KC_LEFT, KC_UP,   KC_RIGHT, \
			KC_FN30, KC_FN31, KC_FN2, KC_FN3,  KC_FN13, KC_FN14, KC_DOWN, KC_TRNS),
	[NUMFUNC_V2] =
		KEYMAP(
			KC_UP,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL, \
			KC_RIGHT, KC_HOME, KC_PGUP, KC_TRNS, KC_PGUP, KC_HOME, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_ENT, \
			KC_LEFT,  KC_END,  KC_PGDN, KC_INS,  KC_PGDN, KC_END,  KC_SCLN, KC_BSLS, KC_LEFT, KC_UP,   KC_RIGHT, \
			KC_DOWN,  KC_FN31, KC_FN2,  KC_LCTL, KC_SPC,  KC_FN0,  KC_DOWN, KC_FN1),
};

const uint16_t PROGMEM fn_actions[] = {
    /* Minorca Layout */
    [0] = ACTION_LAYER_MOMENTARY(NUMFUNC), // to numfunc overlay
    [1] = ACTION_LAYER_TOGGLE(ARROW), // toggle arrow overlay
    [2] = ACTION_LAYER_MOMENTARY(LAYOUT_SELECT), // to Layout selector
    [9] = ACTION_LAYER_TOGGLE(MINORCA_ORIG), // toggle ctrl/shift switch overlay
    [14] = ACTION_LAYER_TOGGLE(OSX), // toggle OSX overlay
    [3] = ACTION_LAYER_SET_CLEAR(MINORCA), // back to original minorca layout
    [5] = ACTION_DEFAULT_LAYER_SET(MINORCA), // set minorca layout
    [6] = ACTION_DEFAULT_LAYER_SET(COLEMAK), // set colemak layout
    [7] = ACTION_DEFAULT_LAYER_SET(DVORAK), // set dvorak layout
    [8] = ACTION_DEFAULT_LAYER_SET(HHKB), // set hhkb layout
    [11] = ACTION_DEFAULT_LAYER_SET(MINORCA_ORIG), // set minorca layout
    [13] = ACTION_LAYER_SET_CLEAR(MINORCA_ORIG), // back to original minorca layout
    [30] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_DEL), // lock screen
    [31] = ACTION_LAYER_MOMENTARY(NUMFUNC_V2), // go up to the other numfunc layer
	};
