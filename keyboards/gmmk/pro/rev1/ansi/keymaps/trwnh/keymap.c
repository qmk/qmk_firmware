// Copyright 2021 a (@trwnh on Github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),

	[1] = LAYOUT(
		KC_KB_POWER, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_INS,
		_______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PAUS,
		_______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_SCRL,
		KC_MSTP, RGB_MOD, RGB_RMOD,_______, _______, _______, NK_TOGG, _______, _______, _______, _______,                   _______, KC_PGUP, KC_APP,
		KC_MPRV, KC_MPLY, KC_MNXT,                            QK_BOOT,                              MO(2),   _______, _______, KC_HOME, KC_PGDN, KC_END
	),

	[2] = LAYOUT(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_BTN3,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_BTN1,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_BTN2, KC_MS_U, _______,
		_______, _______, _______,                            _______,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
	),


};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP) },
    [2] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
};
#endif
// clang-format on

// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08

#ifdef RGB_MATRIX_ENABLE
	static void set_rgb_caps_leds_on(void);
	static void set_rgb_scroll_leds_on(void);
	static void set_rgb_caps_leds_off(void);
	static void set_rgb_scroll_leds_off(void);

	static void set_rgb_caps_leds_on(void) {
		// Set alpha and capslock to red

		rgb_matrix_set_color( 3, 255, 0, 0);	// Caps

		rgb_matrix_set_color( 8, 255, 0, 0);	// Q
		rgb_matrix_set_color(14, 255, 0, 0);	// W
		rgb_matrix_set_color(20, 255, 0, 0);	// E
		rgb_matrix_set_color(25, 255, 0, 0);	// R
		rgb_matrix_set_color(30, 255, 0, 0);	// T
		rgb_matrix_set_color(36, 255, 0, 0);	// Y
		rgb_matrix_set_color(41, 255, 0, 0);	// U
		rgb_matrix_set_color(46, 255, 0, 0);	// I
		rgb_matrix_set_color(52, 255, 0, 0);	// O
		rgb_matrix_set_color(58, 255, 0, 0);	// P

		rgb_matrix_set_color( 9, 255, 0, 0);	// A
		rgb_matrix_set_color(15, 255, 0, 0);	// S
		rgb_matrix_set_color(21, 255, 0, 0);	// D
		rgb_matrix_set_color(26, 255, 0, 0);	// F
		rgb_matrix_set_color(31, 255, 0, 0);	// G
		rgb_matrix_set_color(37, 255, 0, 0);	// H
		rgb_matrix_set_color(42, 255, 0, 0);	// J
		rgb_matrix_set_color(47, 255, 0, 0);	// K
		rgb_matrix_set_color(53, 255, 0, 0);	// L

		rgb_matrix_set_color(10, 255, 0, 0);	// Z
		rgb_matrix_set_color(16, 255, 0, 0);	// X
		rgb_matrix_set_color(22, 255, 0, 0);	// C
		rgb_matrix_set_color(27, 255, 0, 0);	// V
		rgb_matrix_set_color(32, 255, 0, 0);	// B
		rgb_matrix_set_color(38, 255, 0, 0);	// N
		rgb_matrix_set_color(43, 255, 0, 0);	// M
	}

	static void set_rgb_caps_leds_off(void) {
		// Set alpha and capslock to black

		rgb_matrix_set_color( 3, 0, 0, 0);	// Caps

		rgb_matrix_set_color( 8, 0, 0, 0);	// Q
		rgb_matrix_set_color(14, 0, 0, 0);	// W
		rgb_matrix_set_color(20, 0, 0, 0);	// E
		rgb_matrix_set_color(25, 0, 0, 0);	// R
		rgb_matrix_set_color(30, 0, 0, 0);	// T
		rgb_matrix_set_color(36, 0, 0, 0);	// Y
		rgb_matrix_set_color(41, 0, 0, 0);	// U
		rgb_matrix_set_color(46, 0, 0, 0);	// I
		rgb_matrix_set_color(52, 0, 0, 0);	// O
		rgb_matrix_set_color(58, 0, 0, 0);	// P

		rgb_matrix_set_color( 9, 0, 0, 0);	// A
		rgb_matrix_set_color(15, 0, 0, 0);	// S
		rgb_matrix_set_color(21, 0, 0, 0);	// D
		rgb_matrix_set_color(26, 0, 0, 0);	// F
		rgb_matrix_set_color(31, 0, 0, 0);	// G
		rgb_matrix_set_color(37, 0, 0, 0);	// H
		rgb_matrix_set_color(42, 0, 0, 0);	// J
		rgb_matrix_set_color(47, 0, 0, 0);	// K
		rgb_matrix_set_color(53, 0, 0, 0);	// L

		rgb_matrix_set_color(10, 0, 0, 0);	// Z
		rgb_matrix_set_color(16, 0, 0, 0);	// X
		rgb_matrix_set_color(22, 0, 0, 0);	// C
		rgb_matrix_set_color(27, 0, 0, 0);	// V
		rgb_matrix_set_color(32, 0, 0, 0);	// B
		rgb_matrix_set_color(38, 0, 0, 0);	// N
		rgb_matrix_set_color(43, 0, 0, 0);	// M
	}

	static void set_rgb_scroll_leds_on(void) {
		rgb_matrix_set_color(72, 255, 255, 255); // Under Rotary (HOME)
	}

	static void set_rgb_scroll_leds_off(void) {
		rgb_matrix_set_color(72, 0, 0, 0); // Under Rotary (HOME)
	}

	bool rgb_matrix_indicators_user(void) {
		// Left side rainbow
		rgb_matrix_set_color(67, 255,   0,   0);	// Left LED 01
		rgb_matrix_set_color(70, 255, 127,   0);	// Left LED 02
		rgb_matrix_set_color(73, 255, 255,   0);	// Left LED 03
		rgb_matrix_set_color(76,   0, 255,   0);	// Left LED 04
		rgb_matrix_set_color(80,   0,   0, 255);	// Left LED 05
		rgb_matrix_set_color(83,  46,  43,  95);	// Left LED 06
		rgb_matrix_set_color(87, 139,   0, 255);	// Left LED 07
		rgb_matrix_set_color(91, 255, 255, 255);	// Left LED 08

		// Right side rainbow
		rgb_matrix_set_color(68, 255,   0,   0);	// Right LED 12
		rgb_matrix_set_color(71, 255, 127,   0);	// Right LED 13
		rgb_matrix_set_color(74, 255, 255,   0);	// Right LED 14
		rgb_matrix_set_color(77,   0, 255,   0);	// Right LED 15
		rgb_matrix_set_color(81,   0,   0, 255);	// Right LED 16
		rgb_matrix_set_color(84,  46,  43,  95);	// Right LED 17
		rgb_matrix_set_color(88, 139,   0, 255);	// Right LED 18
		rgb_matrix_set_color(92, 255, 255, 255);	// Right LED 19

		if (host_keyboard_led_state().caps_lock) {
			set_rgb_caps_leds_on();
		} else {
			if (rgb_matrix_get_flags() == LED_FLAG_NONE){
			set_rgb_caps_leds_off();
			}
		}
		if (host_keyboard_led_state().scroll_lock) {
			set_rgb_scroll_leds_on();
		} else {
			if (rgb_matrix_get_flags() == LED_FLAG_NONE){
			set_rgb_scroll_leds_off();
			}
		}
    return false;
	}

#endif // RGB_MATRIX_ENABLE
