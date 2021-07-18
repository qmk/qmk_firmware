#include "nstickney.h"

/*
 * This keymap simulates the key limitations of an Iris on an ErgoDox. See the
 * matching iris layout (/keyboards/keebio/iris/keymaps/nstickney) for further
 * information.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_ergodox(
		// left hand
		KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       XXXXXXX,
		KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       XXXXXXX,
		CC_ESC,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
		KC_LSPO,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       XXXXXXX,
		XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    AC_SLSH,
		                                                            TD(LOCKS),  XXXXXXX,
		                                                                        XXXXXXX,
		                                                FC_BSLS,    KC_SPC,     XXXXXXX,
		// right hand
		XXXXXXX,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
		XXXXXXX,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
		            KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    CC_QUOT,
		XXXXXXX,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSPC,
		                        AC_EQL,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
		XXXXXXX,    TD(LAYERS),
		XXXXXXX,
		XXXXXXX,    KC_ENT,     FC_MINS
	),

	[SYMB] = LAYOUT_ergodox(
		// left hand
		UC(0x00EF), UC(0x00A1), UC(0x00B2), UC(0x00B3), UC(0x00A4), UC(0x20AC), _______,
		_______,    UC(0x00E4), UC(0x00E5), UC(0x00E9), UC(0x00AE), UC(0x00FE), _______,
		_______,    UC(0x00E1), UC(0x00DF), UC(0x00F0), UC(0x00EC), UC(0x00ED),
		_______,    UC(0x00E6), UC(0x00E8), UC(0x00A9), UC(0x00EA), UC(0x00EB), _______,
		_______,    _______,    _______,    _______,    UC(0x00BF),
		                                                            _______,    _______,
		                                                                        _______,
		                                                _______,    UC(0x00AC), _______,
		// right hand
		_______,    UC(0x00BC), UC(0x00BD), UC(0x00BE), UC(0x2018), UC(0x2019), _______,
		_______,    UC(0x00FC), UC(0x00FA), UC(0x00ED), UC(0x00F3), UC(0x00F6), _______,
		            UC(0x00EE), UC(0x00E0), UC(0x00E2), UC(0x00F8), UC(0x00B6), UC(0x00B4),
		_______,    UC(0x00F1), UC(0x00FD), UC(0x00E7), UC(0x00F4), UC(0x00BF), _______,
		                        UC(0x00D7), _______,    _______,    _______,    _______,
		_______,    _______,
		_______,
		_______,    UC(0x00B1), _______
	),

	[SYSH] = LAYOUT_ergodox(
		// left hand
		UC(0x00CF), UC(0x00B9), UC(0x2200), UC(0x2201), UC(0x00A3), UC(0x00A5), _______,
		_______,    UC(0x00C4), UC(0x00C5), UC(0x00C9), UC(0x2122), UC(0x00DE), _______,
		_______,    UC(0x00C1), UC(0x00A7), UC(0x00D0), UC(0x00CC), UC(0x00CD),
		_______,    UC(0x00C6), UC(0x00C8), UC(0x00A2), UC(0x00CA), UC(0x00CB), _______,
		_______,    _______,    _______,    _______,    UC(0x203D),
		                                                            _______,    _______,
		                                                                        _______,
		                                                _______,    UC(0x00A6), _______,
		// right hand
		_______,    UC(0x00B5), UC(0x00AB), UC(0x00BB), UC(0x201C), UC(0x201D), _______,
		_______,    UC(0x00DC), UC(0x00DA), UC(0x00CD), UC(0x00D3), UC(0x00D6), _______,
		            UC(0x00CE), UC(0x00C1), UC(0x00C2), UC(0x00D8), UC(0x00B0), UC(0x00A8),
		_______,    UC(0x00D1), UC(0x00DD), UC(0x00C7), UC(0x00D4), UC(0x203D), _______,
		                        UC(0x00F7), _______,    _______,    _______,    _______,
		_______,    _______,
		_______,
		_______,    UC(0x00AA), _______
	),

	[NUMP] = LAYOUT_ergodox(
		// left hand
		_______,    _______,    KC_P7,      KC_P8,      KC_P9,      KC_PSLS,    _______,
		_______,    _______,    KC_P4,      KC_P5,      KC_P6,      KC_PAST,    _______,
		_______,    _______,    KC_P1,      KC_P2,      KC_P3,      KC_PMNS,
		_______,    _______,    KC_P0,      KC_PCMM,    KC_PDOT,    KC_PPLS,    _______,
		_______,    _______,    _______,    _______,    _______,
		                                                            _______,    _______,
		                                                                        _______,
		                                                _______,    _______,    _______,
		// right hand
		_______,    _______,    KC_P7,      KC_P8,      KC_P9,      KC_PSLS,    _______,
		_______,    _______,    KC_P4,      KC_P5,      KC_P6,      KC_PAST,    _______,
		            _______,    KC_P1,      KC_P2,      KC_P3,      KC_PMNS,    _______,
		_______,    _______,    KC_P0,      KC_PCMM,    KC_PDOT,    KC_PPLS,    _______,
		                        _______,    _______,    _______,    _______,    _______,
		_______,    _______,
		_______,
		_______,    KC_PENT,    _______
	),

	[FCTN] = LAYOUT_ergodox(
		// left hand
		KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      _______,
		KC_PSCR,    RGB_TOG,    KC_HOME,    KC_UP,      KC_END,     KC_PGUP,    _______,
		KC_PAUS,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,
		_______,    KC_MPRV,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MNXT,    _______,
		_______,    _______,    _______,    _______,    _______,
		                                                            KC_F11,     _______,
		                                                                        _______,
		                                                _______,    _______,    _______,
		// right hand
		_______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_SYSREQ,
		_______,    UC(0x2014), KC_LBRC,    KC_RBRC,    S(KC_LBRC), S(KC_RBRC), KC_INS,
		            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_BRIU,    KC_CLR,
		_______,    KC_MSTP,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_BRID,    _______,
		                        _______,    _______,    _______,    _______,    _______,
		_______,    KC_F12,
		_______,
		_______,    _______,    _______
	),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user (void) {
	ergodox_board_led_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user (void) {

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