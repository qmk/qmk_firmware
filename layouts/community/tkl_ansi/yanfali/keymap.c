#include QMK_KEYBOARD_H

enum _layer {
 BASE,
 FN
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_tkl_ansi( \
		KC_ESC,          KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS, \
		KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP, \
		KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,  KC_DEL, KC_END, KC_PGDN, \
		MT(MOD_LCTL, KC_ESC),    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,          \
		KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,          KC_UP,           \
		KC_LCTL, KC_LALT,KC_LGUI,                       KC_SPC,                          KC_RGUI,KC_RGUI,MO(FN) ,KC_RCTL,  KC_LEFT,KC_DOWN,KC_RGHT),
	[FN] = LAYOUT_tkl_ansi( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   KC_WAKE,KC_PWR, KC_SLEP, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,EEP_RST,   _______,_______,KC_VOLU, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,QK_BOOT,   _______,_______,KC_VOLD, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                            \
		_______,_______,_______,_______,_______,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,                _______,           KC_MPLY,         \
		_______,_______,_______,                        _______,                        _______,_______,MO(FN) ,_______,   KC_MPRV,KC_MSTP,KC_MNXT)
};
// clang-format on
