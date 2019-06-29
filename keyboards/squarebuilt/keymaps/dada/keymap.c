#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_Q,          KC_W,    KC_E,    KC_R,          KC_T,                      KC_Y,         KC_U,          KC_I,    KC_O,   KC_P,
	    KC_A,          KC_S,    KC_D,    KC_F,          KC_G,                      KC_H,         KC_J,          KC_K,    KC_L,   KC_SCLN,
	    KC_Z,          KC_X,    KC_C,    KC_V,          KC_B,                      KC_N,         KC_M,          KC_COMM, KC_DOT, KC_SLSH,
	    KC_ESC,        KC_LGUI, KC_LALT, LT(2,KC_CAPS), LCTL_T(KC_BSPC),           RSFT(KC_SPC), LT(1,KC_TAB),  TG(4),   KC_DEL, KC_ENT
	),
	[1] = LAYOUT(
        KC_EXLM,       KC_AT,   KC_HASH, KC_DLR,        KC_PERC,                   KC_PLUS,      KC_7,          KC_8,    KC_9,    KC_0,
	    KC_CIRC,       KC_AMPR, KC_UNDS, KC_DQUO,       KC_QUOT,                   KC_MINS,      KC_4,          KC_5,    KC_6,    KC_EQL,
	    KC_PIPE,       KC_BSLS, KC_TILD, KC_GRV,        KC_CALC,                   KC_ASTR,      KC_1,          KC_2,    KC_3,    KC_SLSH,
	    KC_TRNS,       KC_TRNS, KC_TRNS, LT(3,KC_TRNS), KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT(
        LGUI(KC_PSCR), KC_HOME, KC_UP,   KC_END,        KC_PGUP,                   KC_LPRN,      KC_RPRN,       KC_VOLD, KC_VOLU, KC_MUTE,
	    LGUI(KC_TAB),  KC_LEFT, KC_DOWN, KC_RGHT,       KC_PGDN,                   KC_LBRC,      KC_RBRC,       KC_NO,   KC_NO,   KC_NO,
	    KC_MAIL,       KC_MYCM, KC_SLCK, KC_INS,        KC_PSCR,                   KC_LCBR,      KC_RCBR,       KC_NO,   KC_NO,   KC_NO,
	    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      LT(3,KC_TRNS), KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT(
        RGB_HUI,       RGB_SAI, RGB_SPI, RGB_VAI,       RGB_MOD,                   RESET,        KC_F7,         KC_F8,   KC_F9,   KC_F10,
	    RGB_HUD,       RGB_SAD, RGB_SPD, RGB_VAD,       RGB_RMOD,                  KC_SLEP,      KC_F4,         KC_F5,   KC_F6,   KC_F11,
	    RGB_M_P,       RGB_M_R, RGB_M_K, RGB_M_B,       RGB_TOG,                   LCA(KC_DEL),  KC_F1,         KC_F2,   KC_F3,   KC_F12,
	    KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
	),
	[4] = LAYOUT(
		KC_WREF,       KC_ACL0, KC_ACL1, KC_ACL2,       KC_WSTP,                   KC_BTN3,      KC_WH_U,       KC_VOLD, KC_VOLU, KC_MUTE,
	 	KC_NO,         KC_NO,   KC_NO,   KC_NO,         KC_NO,                     KC_MS_L,      KC_MS_D,       KC_MS_U, KC_MS_R, KC_BTN1,
		KC_UNDO,       KC_CUT,  KC_COPY, KC_PSTE,       KC_FIND,                   KC_WH_L,      KC_WH_D,       KC_WH_R, KC_BTN4, KC_BTN2,
		KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,                   KC_TRNS,      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
	)
};
