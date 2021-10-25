#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( \
		KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
		SFT_T(KC_A),ALT_T(KC_S),CTL_T(KC_D),GUI_T(KC_F), KC_G,    KC_H, GUI_T(KC_J),CTL_T(KC_K),ALT_T(KC_L),SFT_T(KC_SCLN), \
		KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
		                      LT(2,KC_TAB), KC_ENT,      KC_SPC,  LT(1,KC_BSPC) \
	),
	[1] = LAYOUT( \
		_______, KC_1,    KC_2,    KC_3,    KC_VOLU,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO, \
		_______, KC_4,    KC_5,    KC_6,    KC_VOLD,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, \
		KC_CAPS, KC_7,    KC_8,    KC_9,    KC_0,        _______, _______, _______, _______, _______, \
		                           MO(3),   KC_GESC,     _______, _______ \
	),
	[2] = LAYOUT( \
		_______, KC_LBRC, KC_LCBR, KC_RCBR, _______,     KC_CIRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_TILD, \
		KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_AMPR, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  \
		_______, _______, _______, _______, _______,     KC_ASTR, KC_UNDS, KC_PLUS, KC_PIPE, _______, \
		                           _______, _______,     KC_SPC,  MO(3) \
	),
	[3] = LAYOUT( \
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F10,      _______, KC_WH_U, KC_WH_D, _______, RESET,   \
		_______, KC_F4,   KC_F5,   KC_F6,   KC_F11,      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_INS,  \
		_______, KC_F7,   KC_F8,   KC_F9,   KC_F12,      _______, KC_BTN1, KC_BTN2, _______, KC_DEL,  \
		                           _______, _______,     _______, _______ \
	)
};
