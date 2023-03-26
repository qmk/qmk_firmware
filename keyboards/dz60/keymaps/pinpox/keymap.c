#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Qwerty
	[0] = LAYOUT_60_ansi(
			KC_GRV,     KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,  KC_BSPC,
			KC_TAB,     KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,   KC_RBRC, KC_BSLS,
			KC_ESC,     KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,   KC_ENT,
			KC_LSFT,    KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
			KC_LCTL,    KC_LGUI, MO(1),    KC_SPC,  KC_ALGR, KC_RGUI, KC_LALT, KC_RCTL
			),

	// Special keys
	[1] = LAYOUT_60_ansi(
			KC_SLEP, KC_F1,   KC_F2,    KC_F3,   KC_F3,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,    KC_F12,   KC_DEL,
			KC_NO,   RGB_MOD, RGB_RMOD, KC_NO,   KC_NO,   KC_NO,   KC_DOWN, KC_RGHT, KC_NO,   KC_NO,  KC_NO,   KC_PGUP,   KC_PGDN,  KC_NO,
			KC_CAPS, BL_TOGG, RGB_TOG,  KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,     KC_MFFD,
			KC_NO,   BL_UP,   BL_DOWN,  BL_BRTG, KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_HOME, KC_END, KC_NO,   KC_PSCR,
			KC_NO,   KC_NO,   KC_TRNS,  KC_MPLY, KC_NO,   KC_NO,   KC_TRNS, KC_NO
			)
};
