#include QMK_KEYBOARD_H
#include "action_layer.h"
// #include "../common/remote_kb.h"
// #include "../common/bitc_led.h"

#define _NUM	0
#define _NAV	1
#define _WNAV	2
#define _FN		3
#define _FN2	4
#define _MUSIC	5
#define _RGB	6

enum sol_keycodes {
	// Disables touch processing
	SELECT = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Base layer (numpad)
	[_NUM] = LAYOUT(
							KC_ESC,			KC_BSPC,	KC_EQL, \
	KC_KP_SLASH,			KC_KP_7,		KC_KP_8,	KC_KP_9,\
	KC_KP_ASTERISK,			KC_KP_4,		KC_KP_5,	KC_KP_6,\
	KC_KP_MINUS,			KC_KP_1,		KC_KP_2,	KC_KP_3,\
	LT(_NAV,KC_KP_PLUS),	KC_KP_ENTER,	KC_KP_0,	KC_KP_DOT\
	),
	[_NAV] = LAYOUT(
						KC_ESC,		G(KC_Z),	S(G(KC_Z)),\
	KC_BSPC,			A(KC_LEFT),	KC_UP,		A(KC_RIGHT),\
	G(KC_X),			KC_LEFT,	KC_DOWN,	KC_RIGHT,\
	G(KC_C),			S(KC_TAB),	SELECT,		KC_TAB,\
	LT(_NUM, G(KC_V)),	KC_ENT,		KC_SPC,		KC_BSPC
	),
	[_WNAV] = LAYOUT(
						KC_ESC,		C(KC_Z),	S(C(KC_Z)),\
	KC_BSPC,			C(KC_LEFT),	KC_UP,		C(KC_RIGHT),\
	C(KC_X),			KC_LEFT,	KC_DOWN,	KC_RIGHT,\
	C(KC_C),			S(KC_TAB),	SELECT,		KC_TAB,\
	LT(_NUM, C(KC_V)),	KC_ENT,		KC_SPC,		KC_BSPC
	),
	[_FN] = LAYOUT(
					KC_F10,			KC_F11,		KC_F12, \
	KC_F13,			KC_F7,			KC_F8,		KC_F9,\
	KC_F14,			KC_F4,			KC_F5,		KC_F6,\
	KC_F15,			KC_F1,			KC_F2,		KC_F3,\
	KC_F16,			KC_KP_ENTER,	KC_F10,		KC_ESC\
	),
	[_FN2] = LAYOUT(
					KC_F22,			KC_F23,		KC_F24, \
	KC_NO,			KC_F19,			KC_F20,		KC_F21,\
	KC_ESC,			KC_F16,			KC_F17,		KC_F18,\
	KC_KP_ENTER,	KC_F13,			KC_F14,		KC_F15,\
	KC_NO,			KC_KP_ENTER,	KC_F22,		KC_ESC\
	),

	[_MUSIC] = LAYOUT(
					KC_NO,		KC_MUTE,	KC_NO, \
	KC_MSEL,		KC_NO,		KC_VOLU,	KC_NO,\
	KC_ESC,			KC_MPRV,	KC_MPLY,	KC_MNXT,\
	KC_KP_ENTER,	KC_NO,		KC_VOLD,	KC_NO,\
	KC_MUTE,		KC_KP_ENTER,	KC_LCTL,	KC_LGUI\
	),
	// Function layer (numpad)
	[_RGB] = LAYOUT(
				KC_NO,		RGB_TOG,	RGB_TOG,
	RGB_MOD,	RGB_MOD,	RGB_RMOD,	RGB_RMOD,
	RGB_HUI,	RGB_HUI,	RGB_HUD,	RGB_HUD,
	RGB_SAI,	RGB_SAI,	RGB_SAD,	RGB_SAD,
	RGB_VAI,	RGB_VAI,	RGB_VAD,	RGB_VAD
	)
};

// ENCODERS
bool encoder_update_user(uint8_t index, bool clockwise) {
	/* With an if statement we can check which encoder was turned. */

		switch (get_highest_layer(layer_state)) {
		case 0:
			if (clockwise) {
				layer_move(get_highest_layer(layer_state)+1);
			} else {
				layer_move(6);
			}
			break;
		case 6:
			if (clockwise) {
				layer_move(0);
			} else {
				layer_move(get_highest_layer(layer_state)-1);
			}

			break;
		default:
			if (clockwise) {
				layer_move(get_highest_layer(layer_state)+1);
			} else {
				layer_move(get_highest_layer(layer_state)-1);
			}
			break;
		}
	return true;
};
// ENCODERS END



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

static void print_status_narrow(void) {

	// Print current layer
	// enum layers { NUM, NAV, FN };

	switch (get_highest_layer(layer_state)) {
		case _NUM:
			oled_write_P(PSTR("Num\n"), false);
			oled_write_P(PSTR("X|<|="), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			oled_write_P(PSTR("E|0|.\n"), false);

			oled_write_ln_P(PSTR("/"), false);
			oled_write_ln_P(PSTR("*"), false);
			oled_write_P(PSTR("-"), false);
			oled_write_ln_P(PSTR("+"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			break;
		case _MUSIC:
			oled_write_P(PSTR("Music"), true);
			oled_write_P(PSTR(" | | "), false);
			oled_write_P(PSTR(" |^| "), false);
			oled_write_P(PSTR("<-P->"), false);
			oled_write_P(PSTR(" |v| "), false);
			oled_write_P(PSTR(" | | \n"), false);
			oled_write_P(PSTR("Media"), false);
			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);
			oled_write_ln_P(PSTR("Vol"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);

			break;
		case _FN:
			oled_write_P(PSTR("Fn\n"), true);
			oled_write_P(PSTR("10-12"), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			oled_write_P(PSTR("A|C|G\n"), false);
			oled_write_ln_P(PSTR("NA"), false);
			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);

			break;
		case _FN2:
			oled_write_P(PSTR("Fn2\n"), true);
			oled_write_P(PSTR("22-24"), false);
			oled_write_P(PSTR("19-21"), false);
			oled_write_P(PSTR("16-18"), false);
			oled_write_P(PSTR("13-15"), false);
			oled_write_P(PSTR("A|C|G\n"), false);
			oled_write_ln_P(PSTR("NA"), false);
			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			break;
		case _NAV:
			oled_write_P(PSTR("Nav\n"), true);
			oled_write_P(PSTR("x|u|r"), false);
			oled_write_P(PSTR("w|^|w"), false);
			oled_write_P(PSTR("<|v|>"), false);
			oled_write_P(PSTR("s|S|t"), false);
			oled_write_P(PSTR("E|_|<\n"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("BSPC"), false);
			oled_write_ln_P(PSTR("CUT"), false);
			oled_write_ln_P(PSTR("COPY"), false);
			oled_write_ln_P(PSTR("PST"), false);

			break;
		case _WNAV:
			oled_write_P(PSTR("WNav\n"), true);
			oled_write_P(PSTR("x|u|r"), false);
			oled_write_P(PSTR("w|^|w"), false);
			oled_write_P(PSTR("<|v|>"), false);
			oled_write_P(PSTR("s|S|t"), false);
			oled_write_P(PSTR("E|_|E\n"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR("BSPC"), false);
			oled_write_ln_P(PSTR("CUT"), false);
			oled_write_ln_P(PSTR("COPY"), false);
			oled_write_ln_P(PSTR("PST"), false);

			break;
		 case _RGB:
			oled_write_P(PSTR("RGB\n"), true);
			oled_write_P(PSTR("Togg"), false);
			oled_write_P(PSTR("Mode"), false);
			oled_write_P(PSTR("Hue\n"), false);
			oled_write_P(PSTR("Sat\n"), false);
			oled_write_ln_P(PSTR("Val\n"), false);
			oled_write_ln_P(PSTR("NA"), false);
			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			break;
		default:
			oled_write_P(PSTR("Undef"), false);
	}
}

void oled_task_user(void) {
	print_status_narrow();
}

#endif


void matrix_init_user(void) {
	matrix_init_remote_kb();
	register_code(KC_NLCK);
}

void matrix_scan_user(void) {
	matrix_scan_remote_kb();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode)
	{
		case SELECT:
			if (record->event.pressed) {
				SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
			}
			return false;	// Skip all further processing of this key
		default:
			break;
	}
	return true;
}


void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_NUM_LOCK))
		set_bitc_LED(LED_DIM);
	else
		set_bitc_LED(LED_OFF);
}




enum combo_events {
	RST,
	TAB,
	SHIFT_TAB,
	COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM reset_combo[] = {KC_KP_ENTER, LT(_NAV,KC_KP_PLUS), KC_KP_0, KC_KP_DOT, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {LT(_NAV,KC_KP_PLUS), KC_KP_MINUS, COMBO_END};
const uint16_t PROGMEM shift_tab_combo[] = {KC_KP_3, KC_KP_DOT, COMBO_END};


combo_t key_combos[] = {
	[TAB] = COMBO_ACTION(tab_combo),
	[SHIFT_TAB] = COMBO_ACTION(shift_tab_combo),
	[RST] = COMBO_ACTION(reset_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {
		case RST:
			if (pressed) {
				set_bitc_LED(LED_DIM);
				rgblight_disable_noeeprom();
				bootloader_jump(); //jump to bootloader
			}
			break;
		case TAB:
			if (pressed) {
				tap_code16(KC_TAB);
			}
			break;
		case SHIFT_TAB:
			if (pressed) {
				tap_code16(S(KC_TAB));
			}
			break;
	}
}
