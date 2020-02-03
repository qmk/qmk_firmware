#include QMK_KEYBOARD_H
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_wrapper(
		KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL,
		KC_TABESC, _______________COLEMAK1____________________, KC_BSPC, KC_NO, KC_NO,
		KC_CTLTB,  _______________COLEMAK2____________________, KC_QUOT, KC_NO,
		KC_LSFT,   _______________COLEMAK3____________________, KC_RSFT, KC_NO,
	  KC_LGUI, KC_LALT, KC_NUM_SPC, KC_NAV_ENT, MO(_FKEY)),

	[_NUM_SYM] = LAYOUT_wrapper(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_NO, KC_NO,KC_NO,KC_NO,
		KC_GRV,  __________________NUM_1____________________, KC_BSPC, KC_NO, KC_NO,
		KC_TILD, __________________NUM_2____________________, KC_PIPE, KC_NO,KC_NO,
		KC_DEL,  KC_NO, __________________NUM_3____________________, KC_DOT, KC_SLSH, KC_NO,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_NAV] = LAYOUT(
		KC_GESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_ENT, KC_TRNS, KC_TRNS)
};
