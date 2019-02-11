#include QMK_KEYBOARD_H

#define ______ KC_TRNS
#define XXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_all(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, XXXXXX, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_CAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_RSFT, XXXXXX,
		MO(2), KC_LGUI, KC_LALT, KC_SPC, TT(1), KC_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT, MO(3)),

	LAYOUT_all(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXX, KC_DEL,
		______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, KC_PSCR, ______, ______, RESET,
		______, ______, ______, ______, ______, ______, ______, ______, KC_MPLY, ______, ______, ______, ______,
		______, ______, ______, ______, BL_DEC, BL_TOGG, BL_INC, BL_STEP, ______, ______, ______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, XXXXXX,
		______, ______, ______, KC_TAB, ______, KC_BSPC, ______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, ______),

	LAYOUT_all(
		______, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), XXXXXX, KC_DEL,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_PGUP, ______, XXXXXX,
		______, ______, ______, KC_TAB, ______, KC_BSPC, ______, KC_HOME, KC_PGDOWN, KC_END, ______),

  	LAYOUT_all(
  		______, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), KC_BRID, KC_BRIU, XXXXXX, KC_DEL,
  		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
  		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
  		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_PGUP, ______, XXXXXX,
  		______, ______, ______, KC_TAB, ______, KC_BSPC, ______, KC_HOME, KC_PGDOWN, KC_END, ______),                                  
};
