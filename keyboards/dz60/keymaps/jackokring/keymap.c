#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//ANSI lock mode 0 =================================================================================== ANSI lock mode 0
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI,          KC_RCTL, MO(4)),//zero index start

	//Navigation lock mode 1 ============================================================================= Navigation lock mode 1
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, MO(5)),

	//Numpad lock mode 2 ================================================================================= Numpad lock mode 2
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_P7,   KC_P8,   KC_P9,   KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_P4,   KC_P5,   KC_P6,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_NLCK,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_P1,   KC_P2,   KC_P3,   KC_SCLN, KC_QUOT, KC_PENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_P0,   KC_COMM, KC_PDOT, KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, OSL(6)),//lock Fn

	//Macro lock mode 3 ================================================================================== Macro lock mode 3
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI,          KC_RCTL, MO(7)),

	//ANSI shift mode 4 ================================================================================== ANSI shift mode 4
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_WHOM, KC_PWR,  KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          UC(937), KC_MUTE, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, UC(181), KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		DF(1),   DF(3),            DF(2),                     DF(0),                              KC_LEFT, KC_DOWN,          KC_RIGHT, KC_TRNS),
	
	//Navigation shift mode 5 ============================================================================ Navigation shift mode 5
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_ESC,
		KC_TRNS,          UC(937), KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, UC(181), KC_PGUP, KC_PGDN, KC_QUES,          KC_TRNS,
		DF(1),   DF(3),            DF(2),                     DF(0),                              KC_RALT, KC_SLSH,          KC_RCTL, KC_TRNS),
	
	//Numpad shift mode 6 ================================================================================ Numpad shift mode 6
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, KC_TRNS, KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		DF(1),   DF(3),            DF(2),                     DF(0),                              KC_LEFT, KC_DOWN,          KC_RIGHT, TG(6)),
	
	//Macro shift mode 7 ================================================================================= Macro shift mode 7
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, KC_TRNS, KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		DF(1),   DF(3),            DF(2),                     DF(0),                              KC_LEFT, KC_DOWN,          KC_RIGHT, KC_TRNS)
};

