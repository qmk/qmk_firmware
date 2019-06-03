#include QMK_KEYBOARD_H

/*
 * This keymap simulates the key limitations of an Iris on an ErgoDox. See the
 * matching iris layout (/keyboards/iris/keymaps/nstickney) for further
 * information.
 */

// Layers
#define BASE 0 // Base layer
#define SYMB 1 // Symbols
#define SYSH 2 // Symbols, shifted
#define NUMP 4 // Numpad
#define FCTN 8 // Function

// Tap Dancing
void dance_lock (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count){
		case 1: // Press once for LGUI
			tap_code(KC_LGUI);
			break;
		case 2: // Press twice for NUMLOCK
			tap_code(KC_NLCK);
			break;
		case 3: // Press thrice for CAPSLOCK
			tap_code(KC_CAPS);
			break;
		case 4: // Press four times for SCROLLOCK
			tap_code(KC_SLCK);
			break;
		default:
			break;
	}
};

void dance_layer (qk_tap_dance_state_t *state, void *user_data) {
	switch (state -> count) {
		case 1: // Press once for MENU
			tap_code(KC_APP);
			break;
		case 2: // Press twice for NUMPAD
			layer_invert(NUMP);
			break;
		case 3: // Press thrice for SYMBOLS
			layer_invert(SYMB);
			break;
		case 4: // Press four times for SYMBOLS, SHIFTED
			layer_invert(SYSH);
			break;
		default:
			break;
	}
};

enum tap_dances {LOCKS = 0, LAYERS = 1};
qk_tap_dance_action_t tap_dance_actions[] = {
	[LOCKS] = ACTION_TAP_DANCE_FN(dance_lock),
	[LAYERS] = ACTION_TAP_DANCE_FN(dance_layer)
};

// Make layering more clear
enum custom_keycodes {
	__________ = KC_TRNS,
	XXX = KC_NO,
	CC_ESC = LCTL_T(KC_ESC),
	CC_QUOT = RCTL_T(KC_QUOT),
	AC_SLSH = LALT_T(KC_SLSH),
	AC_EQL = RALT_T(KC_EQL),
	FC_BSLS = LT(FCTN, KC_BSLS),
	FC_MINS = LT(FCTN, KC_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_ergodox(
		// left hand
		KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       XXX,
		KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       XXX,
		CC_ESC,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
		KC_LSPO,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       XXX,
		XXX,        XXX,        XXX,        XXX,        AC_SLSH,
		                                                            TD(LOCKS),  XXX,
		                                                                        XXX,
		                                                FC_BSLS,    KC_SPC,     XXX,
		// right hand
		XXX,        KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
		XXX,        KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
		            KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    CC_QUOT,
		XXX,        KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSPC,
		                        AC_EQL,     XXX,        XXX,        XXX,        XXX,
		XXX,        TD(LAYERS),
		XXX,
		XXX,        KC_ENT,     FC_MINS
	),

	[SYMB] = LAYOUT_ergodox(
		// left hand
		UC(0x00EF), UC(0x00A1), UC(0x00B2), UC(0x00B3), UC(0x00A4), UC(0x20AC), __________,
		__________, UC(0x00E4), UC(0x00E5), UC(0x00E9), UC(0x00AE), UC(0x00FE), __________,
		__________, UC(0x00E1), UC(0x00DF), UC(0x00F0), UC(0x00EC), UC(0x00ED),
		__________, UC(0x00E6), UC(0x00E8), UC(0x00A9), UC(0x00EA), UC(0x00EB), __________,
		__________, __________, __________, __________, UC(0x00BF),
		                                                            __________, __________,
		                                                                        __________,
		                                                UC(0x00AC), __________, __________,
		// right hand
		__________, UC(0x00BC), UC(0x00BD), UC(0x00BE), UC(0x2018), UC(0x2019), __________,
		__________, UC(0x00FC), UC(0x00FA), UC(0x00ED), UC(0x00F3), UC(0x00F6), __________,
		            UC(0x00EE), UC(0x00E0), UC(0x00E2), UC(0x00F8), UC(0x00B6), UC(0x00B4),
		__________, UC(0x00F1), UC(0x00FD), UC(0x00E7), UC(0x00F4), UC(0x00BF), __________,
		                        UC(0x00D7), __________, __________, __________, __________,
		__________, __________,
		__________,
		__________, __________, UC(0x00B1)
	),

	[SYSH] = LAYOUT_ergodox(
		// left hand
		UC(0x00CF), UC(0x00B9), UC(0x2200), UC(0x2201), UC(0x00A3), UC(0x00A5), __________,
		__________, UC(0x00C4), UC(0x00C5), UC(0x00C9), UC(0x2122), UC(0x00DE), __________,
		__________, UC(0x00C1), UC(0x00A7), UC(0x00D0), UC(0x00CC), UC(0x00CD),
		__________, UC(0x00C6), UC(0x00C8), UC(0x00A2), UC(0x00CA), UC(0x00CB), __________,
		__________, __________, __________, __________, UC(0x203D),
		                                                            __________, __________,
		                                                                        __________,
		                                                UC(0x00A6), __________, __________,
		// right hand
		__________, UC(0x00B5), UC(0x00AB), UC(0x00BB), UC(0x201C), UC(0x201D), __________,
		__________, UC(0x00DC), UC(0x00DA), UC(0x00CD), UC(0x00D3), UC(0x00D6), __________,
		            UC(0x00CE), UC(0x00C1), UC(0x00C2), UC(0x00D8), UC(0x00B0), UC(0x00A8),
		__________, UC(0x00D1), UC(0x00DD), UC(0x00C7), UC(0x00D4), UC(0x203D), __________,
		                        UC(0x00F7), __________, __________, __________, __________,
		__________, __________,
		__________,
		__________, __________, UC(0x00AA)
	),

	[NUMP] = LAYOUT_ergodox(
		// left hand
		__________, __________, KC_P7,      KC_P8,      KC_P9,      KC_PSLS,    __________,
		__________, __________, KC_P4,      KC_P5,      KC_P6,      KC_PAST,    __________,
		__________, __________, KC_P1,      KC_P2,      KC_P3,      KC_PMNS,
		__________, __________, KC_P0,      KC_PCMM,    KC_PDOT,    KC_PPLS,    __________,
		__________, __________, __________, __________, __________,
		                                                            __________, __________,
		                                                                        __________,
		                                                __________, __________, __________,
		// right hand
		__________, __________, KC_P7,      KC_P8,      KC_P9,      KC_PSLS,    __________,
		__________, __________, KC_P4,      KC_P5,      KC_P6,      KC_PAST,    __________,
		            __________, KC_P1,      KC_P2,      KC_P3,      KC_PMNS,    __________,
		__________, __________, KC_P0,      KC_PCMM,    KC_PDOT,    KC_PPLS,    __________,
		                        __________, __________, __________, __________, __________,
		__________, __________,
		__________,
		__________, KC_PENT,    __________
	),

	[FCTN] = LAYOUT_ergodox(
		// left hand
		KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      __________,
		KC_PSCR,    RGB_TOG,    KC_HOME,    KC_UP,      KC_END,     KC_PGUP,    __________,
		KC_PAUS,    __________, KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,
		__________, KC_MPRV,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MNXT,    __________,
		__________, __________, __________, __________, __________,
		                                                            KC_F11,     __________,
		                                                                        __________,
		                                                __________, __________, __________,
		// right hand
		__________, KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_SYSREQ,
		__________, UC(0x2014), KC_LBRC,    KC_RBRC,    S(KC_LBRC), S(KC_RBRC), KC_INS,
		            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_BRIU,    KC_CLR,
		__________, KC_MSTP,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_BRID,    __________,
		                        __________, __________, __________, __________, __________,
		__________, KC_F12,
		__________,
		__________, __________, __________
	),
};

void eeconfig_init_user(void) {
	set_unicode_input_mode(UC_LNX); // Linux
	//set_unicode_input_mode(UC_OSX); // Mac OSX
	//set_unicode_input_mode(UC_WIN); // Windows (with registry key, see wiki)
	//set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
	ergodox_board_led_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

	if (IS_LAYER_ON(SYMB) || IS_LAYER_ON(SYSH)) {
		ergodox_right_led_1_on();
	} else {
		ergodox_right_led_1_off();
	}

	if (IS_LAYER_ON(NUMP)) {
		ergodox_right_led_2_on();
	} else {
		ergodox_right_led_2_off();
	}

	if (IS_LAYER_ON(FCTN)) {
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}

};
