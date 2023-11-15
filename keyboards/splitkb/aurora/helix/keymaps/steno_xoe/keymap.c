#include QMK_KEYBOARD_H
#include "keymap_steno.h"

enum my_helix_layers {
	_QWERTY,
	_STENO,
	_SILENT,
	_NUMBER,
	_SYMBOL
};

#define QWERTY DF(_QWERTY)
#define STENO DF(_STENO)
#define SILENT DF(_SILENT)
#define NUMBER MO(_NUMBER)
#define SYMBOL MO(_SYMBOL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
		KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,								KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_DEL,
        KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,								KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSPC,
        KC_CAPS,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,								KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
        KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_KB_MUTE,	SILENT,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_ENT ,
        KC_ESC,		XXXXXXX,	KC_LCTL,	KC_LALT,	KC_LGUI, 	KC_SPC,		NUMBER,		SYMBOL,		KC_SPC,		KC_RSFT,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RGHT
		),

	[_STENO] = LAYOUT(
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,
		XXXXXXX,	STN_N1,		STN_N2,		STN_N3,		STN_N4,		XXXXXXX,							XXXXXXX,	STN_N5,		STN_N6,		STN_N7,		STN_N8,		STN_N9,
		XXXXXXX,	STN_S1,		STN_TL,		STN_PL,		STN_HL,		STN_ST1,							STN_ST3,	STN_FR,		STN_PR,		STN_LR,		STN_TR,		STN_DR,
		KC_LSFT,	STN_S2,		STN_KL,		STN_WL,		STN_RL,		STN_ST2,	KC_KB_MUTE,	SILENT,		STN_ST4,	STN_RR,		STN_BR,		STN_GR,		STN_SR,		STN_ZR,
		KC_ESC,		XXXXXXX,	XXXXXXX,	KC_LALT,	STN_A,		STN_O,		NUMBER,		SYMBOL,		STN_E,		STN_U,		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX
		),

	[_SILENT] = LAYOUT(
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_KB_MUTE,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	NUMBER,		SYMBOL,		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX
		),

	[_NUMBER] = LAYOUT(
		XXXXXXX,	RGB_HUI,	RGB_SAI,	RGB_VAI,	RGB_MOD,	XXXXXXX,							XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_DEL,
		XXXXXXX,	RGB_HUD,	RGB_SAD,	RGB_VAD,	RGB_RMOD,	KC_PGUP,							XXXXXXX,	KC_P7,		KC_P8,		KC_P9,		XXXXXXX,	KC_BSPC,
		XXXXXXX,	KC_END,		KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_PGDN,							XXXXXXX,	KC_P4,		KC_P5,		KC_P6,		XXXXXXX,	XXXXXXX,
		KC_LSFT,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_P1,		KC_P2,		KC_P3,		XXXXXXX,	KC_ENT,
		XXXXXXX,	XXXXXXX,	KC_LCTL,	KC_LALT,	KC_LGUI,	XXXXXXX,	_______,	STENO,		KC_SPC,		KC_P0,		XXXXXXX,	KC_PDOT,	XXXXXXX,	XXXXXXX
		),

	[_SYMBOL] = LAYOUT(
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	KC_UP,		XXXXXXX,	XXXXXXX,	KC_DEL,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_LBRC,	KC_BSPC,
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,							XXXXXXX,	XXXXXXX,	KC_RBRC,	KC_MINUS,	KC_EQL,		KC_BSLS,
		KC_LSFT,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	EE_CLR,		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_LBRC,	KC_ENT,
		XXXXXXX,	XXXXXXX,	KC_LCTL,	KC_LALT,	KC_LGUI,	KC_SPC,		QWERTY,		_______,	KC_SPC,		KC_RSFT,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX
		)
};

#ifdef OLED_ENABLE
	// bool oled_task_user(void) {
	// 	// if(is_keyboard_master()){
	// 	// 	oled_write_P(PSTR("Layer\n-----\n\n"), false);
	// 	// }

	// 	// if (is_keyboard_master()) {
	// 	// 	oled_write_P(PSTR("Layer:\n"), false);

	// 	// 	switch(get_highest_layer(layer_state)) {
	// 	// 	case _QWERTY:
	// 	// 		oled_write_P(PSTR("QWERTY\n"), false);
	// 	// 		break;
	// 	// 	case _STENO:
	// 	// 		oled_write_P(PSTR("STENO\n"), false);
	// 	// 		break;
	// 	// 	case _SILENT:
	// 	// 		oled_write_P(PSTR("Silent\n"), false);
	// 	// 		break;
	// 	// 	default:
	// 	// 		oled_write_P(PSTR("Undefined\n"), false);
	// 	// 	}
	// 	// }

	// 	return false;
	// }

layer_state_t default_layer_state_set_user(layer_state_t state) {
	if (is_keyboard_master()){
		//oled_write_P(PSTR("Layer\n-----\n\n"), false);
		switch(get_highest_layer(state)){
			case _QWERTY:
				oled_write_P(PSTR("qwer\n"), false);
				break;
			case _STENO:
				oled_write_P(PSTR("sten\n"), false);
				break;
			case _SILENT:
				oled_write_P(PSTR("off\n"), false);
				break;
			case _NUMBER:
				oled_write_P(PSTR("numb\n"), false);
				break;
			case _SYMBOL:
				oled_write_P(PSTR("symb\n"), false);
				break;
			default:
				oled_write_P(PSTR("???\n"), false);
		}
	}
	return state;
}

	layer_state_t layer_state_set_user(layer_state_t state) {
	if (is_keyboard_master()){
		//oled_write_P(PSTR("Layer\n-----\n\n"), false);
		switch(get_highest_layer(state)){
			case _QWERTY:
				oled_write_P(PSTR("qwer\n"), false);
				break;
			case _STENO:
				oled_write_P(PSTR("sten\n"), false);
				break;
			case _SILENT:
				oled_write_P(PSTR("off\n"), false);
				break;
			case _NUMBER:
				oled_write_P(PSTR("numb\n"), false);
				break;
			case _SYMBOL:
				oled_write_P(PSTR("symb\n"), false);
				break;
			default:
				oled_write_P(PSTR("???\n"), false);
		}
	}
	// if (is_keyboard_master()) {
	// 	if (layer_state_cmp(state, _QWERTY)) {
	// 		oled_write_P(PSTR("Qwerty\n"), false);
	// 	} else if (layer_state_cmp(state, _STENO)) {
	// 		oled_write_P(PSTR("Steno\n"), false);
	// 	} else if (layer_state_cmp(state, _SILENT)) {
	// 		oled_write_P(PSTR("Off\n"), false);	
	// 	}
	// }

    return state;	
}
#endif

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}