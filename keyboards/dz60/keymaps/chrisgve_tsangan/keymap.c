#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BL = 0,    // Base Layer
  _FN,        // Function Layer
  _DIR,       // Direction layer
  _FULL_DIR,  // Full direction layer
};

#define FN      MO(_FN)
#define NAV     LT(_DIR, KC_D)
#define F_NAV   MO(_FULL_DIR)
#define S_SHIFT SFT_T(KC_S)
#define CPS_CTL CTL_T(KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BL] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  FN,      KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    NAV,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_BSLS,
		KC_LCTL, KC_LALT, KC_LGUI,                                     KC_SPC,                                      KC_RGUI, KC_RALT, KC_RCTL
	),

	[_FN] = LAYOUT_60_tsangan_hhkb(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, _______, _______,
		_______, _______, _______,                                     KC_MPLY,                                     _______, _______, _______
	),

	[_DIR] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, S_SHIFT, _______, F_NAV,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_FULL_DIR] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	)

};
