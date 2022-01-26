#include QMK_KEYBOARD_H
#include "action_layer.h"
// #include "../common/remote_kb.h"
// #include "../common/bitc_led.h"

#define _BASE	0
#define _MUSIC	1
#define _FN		2
#define _FN2	3
#define _NAV	4
#define _FUNC	5


enum custom_keycodes {
	PROG = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Base layer (numpad)
	[_BASE] = LAYOUT(
				KC_KP_SLASH,	KC_KP_ASTERISK,	KC_KP_MINUS, \
	TO(_MUSIC),		KC_KP_7,		KC_KP_8,		KC_KP_9,\
	KC_ESC,		KC_KP_4,		KC_KP_5,		KC_KP_6,\
	KC_KP_ENTER,	KC_KP_1,		KC_KP_2,		KC_KP_3,\
	KC_KP_ENTER,	KC_KP_PLUS,		KC_KP_0,		KC_KP_DOT\
	),
	[_MUSIC] = LAYOUT(
				KC_F22,	KC_F23,	KC_F24, \
	TO(_FN),		KC_F19,	KC_F20,	KC_F21,\
	KC_ESC,		KC_MPRV,	KC_MPLY,	KC_MNXT,\
	KC_KP_ENTER,	KC_F13,	KC_F14,	KC_F15,\
	KC_MPLY,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	[_FN] = LAYOUT(
				KC_F10,	KC_F11,	KC_F12, \
	TO(_FN2),		KC_F7,	KC_F8,	KC_F9,\
	KC_ESC,		KC_F4,	KC_F5,	KC_F6,\
	KC_KP_ENTER,	KC_F1,	KC_F2,	KC_F3,\
	KC_KP_ENTER,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	[_FN2] = LAYOUT(
				KC_F22,	KC_F23,	KC_F24, \
	TO(_NAV),		KC_F19,	KC_F20,	KC_F21,\
	KC_ESC,		KC_F16,	KC_F17,	KC_F18,\
	KC_KP_ENTER,	KC_F13,	KC_F14,	KC_F15,\
	KC_KP_ENTER,	KC_LALT,	KC_LCTL,	KC_LGUI\
	),
	[_NAV] = LAYOUT(
			KC_CUT,		KC_COPY,	KC_PASTE,\
	TO(_FUNC),	KC_HOME,		KC_UP,	KC_PGUP,\
	KC_LGUI,	A(KC_LEFT),		A(KC_BSPC),	A(KC_RIGHT),\
	KC_LALT,	KC_END,		KC_DOWN,	KC_PGDN,\
	KC_LSFT,	KC_TAB,		KC_SPC,	KC_ENT
	),
	// Function layer (numpad)
	[_FUNC] = LAYOUT(
				        KC_NO,	RGB_TOG,	KC_NO,
		TO(_BASE),		KC_NO,	RGB_MOD,	KC_NO,
		KC_ESC,	   	 KC_NO,	RGB_HUI,	KC_NO,
		KC_KP_ENTER,	KC_NO,	RGB_SAI,	KC_NO,
		PROG,		    KC_NO,	RGB_VAI,	TO(_BASE)
	),
};


// ENCODERS
bool encoder_update_user(uint8_t index, bool clockwise) {
	/* With an if statement we can check which encoder was turned. */
	switch (get_highest_layer(layer_state)) {
	case 1:
		if (index == 0) {
			if (clockwise) {
				tap_code(KC_VOLU);
			} else {
				tap_code(KC_VOLD);
			}
		}
		else { /* Second encoder */
			if (clockwise) {
				tap_code16(KC_MNXT);
			} else {
				tap_code16(KC_MPRV);
			}
		}
		break;
	default:
		if (index == 0) { /* First encoder */
			if (clockwise) {
				tap_code(KC_UP);
			} else {
				tap_code(KC_DOWN);
			}
		} else { /* Second encoder */
			if (clockwise) {
				tap_code16(KC_RIGHT);
			} else {
				tap_code16(KC_LEFT);
			}
		}
	}
	return true;
// ENCODERS END
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }


static void print_status_narrow(void) {

	// Print current layer
	// enum layers { NUM, NAV, FN };

	switch (get_highest_layer(layer_state)) {
		case 0:
			oled_write_ln_P(PSTR("Num"), false);
			oled_write_P(PSTR("/|*|-"), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			oled_write_P(PSTR("A|C|G\n"), false);

			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);

			break;
		case 1:
			oled_write_ln_P(PSTR("Mus"), true);
			oled_write_ln_P(PSTR(" | | "), false);
			oled_write_ln_P(PSTR(" | | "), false);
			oled_write_ln_P(PSTR("<|P|>"), false);
			oled_write_ln_P(PSTR(" | | "), false);
			oled_write_ln_P(PSTR(" | | "), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			break;
		case 2:
			oled_write_ln_P(PSTR("Fn"), true);
			oled_write_P(PSTR("10-12"), false);
			oled_write_P(PSTR("7|8|9"), false);
			oled_write_P(PSTR("4|5|6"), false);
			oled_write_P(PSTR("1|2|3"), false);
			oled_write_P(PSTR("A|C|G"), false);


			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_P(PSTR("ENTER"), false);

			break;
		case 3:
			oled_write_ln_P(PSTR("Fn2"), true);
			oled_write_ln_P(PSTR("22-24"), false);
			oled_write_ln_P(PSTR("19-21"), false);
			oled_write_ln_P(PSTR("16-18"), false);
			oled_write_ln_P(PSTR("13-15"), false);
			oled_write_ln_P(PSTR("A|C|G"), false);

			oled_write_ln_P(PSTR("ESC"), false);
			oled_write_ln_P(PSTR("ENTER"), false);

			break;
		case 4:
			oled_write_ln_P(PSTR("Nav\n"), true);
			oled_write_ln_P(PSTR("H|^|u"), false);
			oled_write_ln_P(PSTR("L|x|R"), false);
			oled_write_ln_P(PSTR("E|v|V"), false);
			oled_write_ln_P(PSTR("->_E"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);

			break;
		 case 5:
			oled_write_ln_P(PSTR("RGB\n"), true);
			oled_write_P(PSTR("*Togg"), false);
			oled_write_P(PSTR("8Mode"), false);
			oled_write_ln_P(PSTR("6Hue"), false);
			oled_write_ln_P(PSTR("2Sat"), false);
			oled_write_ln_P(PSTR("0Val"), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			oled_write_ln_P(PSTR(""), false);
			break;
		default:
			oled_write_ln_P(PSTR("Undef"), false);
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
	process_record_remote_kb(keycode, record);
	switch(keycode) {
		case PROG:
			if (record->event.pressed) {
				set_bitc_LED(LED_DIM);
				rgblight_disable_noeeprom();
				bootloader_jump(); //jump to bootloader
			}
		break;

		default:
		break;
	}
	return true;
}


// layer_state_t layer_state_set_user(layer_state_t state) {
// 		switch (get_highest_layer(state)) {
// 		case _FUNC:
// 				unregister_code(KC_NLCK);
// 				break;
// 		default: //	for any other layers, or the default layer
// 				register_code(KC_NLCK);
// 				break;
// 		}
// 	return state;
// }




void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_NUM_LOCK))
		set_bitc_LED(LED_DIM);
	else
		set_bitc_LED(LED_OFF);
}



enum combo_events {
	RST,
	PRT,
	COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM reset_combo[] = {KC_KP_ENTER, KC_ESC, COMBO_END};
const uint16_t PROGMEM prt_combo[] = {KC_KP_1,KC_KP_2, COMBO_END};


combo_t key_combos[] = {

	[RST] = COMBO_ACTION(reset_combo),
	[PRT] = COMBO_ACTION(prt_combo)

	// Lock computer combo!
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {

		case RST:
			if (pressed) {
				set_bitc_LED(LED_DIM);
				rgblight_disable_noeeprom();
				bootloader_jump(); //jump to bootloader
			}
			break;
		case PRT:
			if (pressed) {
				SEND_STRING("hello");
			}
			break;
	}
}
