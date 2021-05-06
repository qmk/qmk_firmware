#include "axon.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(//Layer 0
		KC_ESC,  KC_Q,    KC_W,     KC_E,  KC_R,    KC_T,   KC_Y, KC_U, KC_I,     KC_O,   KC_P,   KC_BSPC,
		KC_TAB,  KC_A,    KC_S,     KC_D,  KC_F,    KC_G,   KC_H, KC_J, KC_K,     KC_L,   KC_ENT,
		KC_LSFT, KC_Z,    KC_X,     KC_C,  KC_V,    KC_B,   KC_N, KC_M, KC_COMMA, KC_DOT, MO(2),
		         KC_LALT, KC_LCTL,         KC_SPACE,        MO(1),      KC_RCTL,  KC_RALT
	),

	KEYMAP(//Layer 1
		KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_DEL,
		KC_TAB,  KC_MINS, KC_EQL,  KC_SCLN,  KC_QUOT, KC_HOME, KC_END, KC_NO,   KC_UP,   KC_TRNS,  KC_ENTER,
		KC_LSFT, KC_LBRC, KC_RBRC, KC_SLSH,  KC_NUBS, KC_NO,   KC_NO,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,
		         KC_LALT, KC_LGUI,           KC_SPACE,         KC_TRNS,         KC_RGUI, KC_RALT
	),

	KEYMAP(//Layer 2
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,  KC_F7, KC_F8, KC_F9, KC_F10,  KC_F11,  KC_F12,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_VOLU, KC_TRNS,
		       KC_NO, KC_NO,        KC_NO,         KC_NO,        KC_NO, KC_VOLD
	),

};