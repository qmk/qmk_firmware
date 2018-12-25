#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 
#define SYMB 1 
#define PAD  2 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	KEYMAP(
		LT(1, KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_SPC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_PIPE, 
		MT(MOD_LCTL, KC_BSPC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_TRNS, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_DQUO, 
		KC_RSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
		KC_LALT, KC_LGUI, KC_SPC, LT(1, KC_ESC), KC_TRNS, KC_PGUP, LT(2, KC_ENT), KC_SPC, KC_TAB, KC_EXLM),

	KEYMAP(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_ASTR, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, 
		KC_CIRC, KC_EXLM, KC_AT, KC_LPRN, KC_RPRN, KC_PIPE, KC_PLUS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, 
		KC_HASH, KC_PERC, KC_DLR, KC_LCBR, KC_RCBR, KC_TILD, KC_MINS, KC_SLSH, KC_AMPR, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS, 
		KC_LBRC, KC_RBRC, KC_UNDS, KC_TRNS, KC_END, KC_PGUP, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT),

	KEYMAP(
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOT, KC_0),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;
	switch (id) {
	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
}