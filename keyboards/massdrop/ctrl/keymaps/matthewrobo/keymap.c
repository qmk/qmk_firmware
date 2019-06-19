#include QMK_KEYBOARD_H

enum ctrl_layers {
	_QWERTY,
	_NAV,
	_FNC
};

enum ctrl_keycodes {
	U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
	U_T_AGCR,              //USB Toggle Automatic GCR control
	DBG_TOG,               //DEBUG Toggle On / Off
	DBG_MTRX,              //DEBUG Toggle Matrix Prints
	DBG_KBD,               //DEBUG Toggle Keyboard Prints
	DBG_MOU,               //DEBUG Toggle Mouse Prints
	MD_BOOT,               //Restart into bootloader after hold timeout
	MAS_TOG,
	MAS_CRM,
	MAS_PRP,
	MAS_RED,
	MAS_GRN,
	MAS_BLU,
	MAS_CYN,
	MAS_MGT,
	MAS_YEL,
	MAS_KEY,
	MAS_WHT,
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode
#define LT_CAPS LT(_NAV, KC_CAPS)
#define _V_V_V_ KC_TRNS
extern bool autoshift_enabled;


keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
		LT_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
		KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,                              KC_UP, \
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FNC), KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
	),
	[_NAV] = LAYOUT(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PMNS, KC_PPLS, _______,   _______, _______, _______, \
		_______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PSLS, _______, _______, KC_EQL,    _______, _______, _______, \
		_V_V_V_, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_PPLS, _______, \
		_______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_P0,   KC_PDOT, KC_PSLS, _______,                              _______, \
		_______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______  \
	),
	[_FNC] = LAYOUT(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, KC_MSEL, KC_ASTG, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MSTP, KC_MPLY, KC_VOLU, \
		_______, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, MAS_MGT, MAS_BLU, MAS_WHT, RGB_RMOD, RGB_MOD, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
		_______, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, _______, MAS_RED, MAS_KEY, MAS_CYN, MAS_PRP, _______, _______, \
		MAS_TOG, RGB_TOG, _______, _______, _______, MD_BOOT, TG_NKRO, MAS_YEL, MAS_GRN, MAS_CRM, _______, _______,                              RGB_VAI, \
		_______, _______, _______,                   _______,                            _______, _V_V_V_, _______, _______,            RGB_SPD, RGB_VAD, RGB_SPI  \
	),
	/*
	[X] = LAYOUT(
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
	    _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
	),
	[X] = LAYOUT(
	    0,       1,       2,       3,       4,       5,       6,       7,       8,       9,       10,      11,      12,                 13,      14,      15,      \
	    16,      17,      18,      19,      20,      21,      22,      23,      24,      25,      26,      27,      28,      29,        30,      31,      32,      \
	    33,      34,      35,      36,      37,      38,      39,      40,      41,      42,      43,      44,      45,      46,        47,      48,      49,      \
	    50,      51,      52,      53,      54,      55,      56,      57,      58,      59,      60,      61,      62,      \
	    63,      64,      65,      66,      67,      68,      69,      70,      71,      72,      73,      74,                                   75,      \
	    76,      77,      78,                        79,                                 80,      81,      82,      83,                 84,      85,      86      \
	),
	*/
};


void rgb_matrix_indicators_user(void)
{
	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
		case _NAV:
			if (this_led & (1 << USB_LED_NUM_LOCK)) {
				rgb_matrix_set_color(41, 0xFF, 0x00, 0x00);
			} else {
				rgb_matrix_set_color(41, 0x00, 0x00, 0x00);
			}

			// layer indicator
			rgb_matrix_set_color(50, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(101, 0xFF, 0xFF, 0xFF);
			// ESDF
			rgb_matrix_set_color(36, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(52, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(53, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(54, 0xFF, 0x00, 0x00);
			// home/end
			rgb_matrix_set_color(35, 0x00, 0xFF, 0x00);
			rgb_matrix_set_color(37, 0x00, 0xFF, 0x00);
			// pgup/dn
			rgb_matrix_set_color(34, 0x00, 0x00, 0xFF);
			rgb_matrix_set_color(51, 0x00, 0x00, 0xFF);
			// numpad
			rgb_matrix_set_color(23, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(24, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(25, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(40, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(42, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(57, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(58, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(59, 0xFF, 0xFF, 0x00);
			// zero
			rgb_matrix_set_color(69, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(70, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(71, 0xFF, 0x00, 0x00);
			// dot
			rgb_matrix_set_color(72, 0x00, 0x00, 0xFF);
			// math shit
			rgb_matrix_set_color(26,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(27,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(28,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(43,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(46,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(60,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(61,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(73,  0x00, 0x00, 0xFF);
			break;

		case _FNC: {
			HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
			HSV hui = hsv;
			HSV hud = hsv;
			HSV sai = hsv;
			HSV sad = hsv;
			HSV vai = hsv;
			HSV vad = hsv;
			hui.h = hsv.h + 8;
			hud.h = hsv.h - 8;
			sai.s = hsv.s + 16 > 255 ? 255u : hsv.s + 16;
			sad.s = hsv.s - 16 < 0   ?   0 : hsv.s - 16;
			vai.v = hsv.v + 16 > 255 ? 255 : hsv.v + 16;
			vad.v = hsv.v - 16 < 0   ?   0 : hsv.v - 16;
			RGB rgb = hsv_to_rgb(hsv);
			RGB rgbHUI = hsv_to_rgb(hui);
			RGB rgbHUD = hsv_to_rgb(hud);
			RGB rgbSAI = hsv_to_rgb(sai);
			RGB rgbSAD = hsv_to_rgb(sad);
			RGB rgbVAI = hsv_to_rgb(vai);
			RGB rgbVAD = hsv_to_rgb(vad);
			rgb_matrix_set_color(81, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(91, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(93, 0x00, 0x00, 0x00);
			rgb_matrix_set_color(94, rgb.r, rgb.g, rgb.b);
			rgb_matrix_set_color(95, rgb.r, rgb.g, rgb.b);
			rgb_matrix_set_color(96, 0x00, 0x00, 0x00);
			rgb_matrix_set_color(68, 0xFF, 0x00, 0x00); // MD_BOOT
			rgb_matrix_set_color(69, 0xFF, 0x00, 0x40); // TG_NKRO
			rgb_matrix_set_color(32, 0x00, 0x80, 0xFF); // KC_VOLU
			rgb_matrix_set_color(49, 0x00, 0x80, 0xFF);
			rgb_matrix_set_color(13, 0xFF, 0x00, 0x00); // KC_MUTE
			rgb_matrix_set_color(30, 0xFF, 0x00, 0x00); // KC_MSTP
			rgb_matrix_set_color(47, 0xFF, 0x40, 0x00); // KC_MPRV
			rgb_matrix_set_color(48, 0xFF, 0x40, 0x00);
			rgb_matrix_set_color(14, 0x00, 0xFF, 0x00); // KC_MSEL
			rgb_matrix_set_color(31, 0x00, 0xFF, 0x00); // KC_MPLY

			if (this_led & (1 << !autoshift_enabled)) {
				rgb_matrix_set_color(15, 0xFF, 0x00, 0x00); // KC_ASTG
			} else {
				rgb_matrix_set_color(15, 0xFF, 0xFF, 0x00);
			}

			rgb_matrix_set_color(44, 0xFF, 0x80, 0x00); //RGB_MOD
			rgb_matrix_set_color(45, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(34, 0xFF, 0x80, 0x00); //RGB_MOD
			rgb_matrix_set_color(51, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(63, 0xFF, 0x40, 0x00); //RGB_TOG
			rgb_matrix_set_color(64, rgb.r, rgb.g, rgb.b); //MAS_TOG
			rgb_matrix_set_color(36, rgbHUI.r, rgbHUI.g, rgbHUI.b); //RGB_HUI
			rgb_matrix_set_color(53, rgbHUD.r, rgbHUD.g, rgbHUD.b);
			rgb_matrix_set_color(37, rgbSAI.r, rgbSAI.g, rgbSAI.b); //RGB_SAI
			rgb_matrix_set_color(54, rgbSAD.r, rgbSAD.g, rgbSAD.b);
			rgb_matrix_set_color(38, rgbVAI.r, rgbVAI.g, rgbVAI.b); //RGB_VAI
			rgb_matrix_set_color(55, rgbVAD.r, rgbVAD.g, rgbVAD.b);
			rgb_matrix_set_color(79, rgb.r, rgb.g, rgb.b); // config display
			rgb_matrix_set_color(75, rgbVAI.r, rgbVAI.g, rgbVAI.b); //RGB_VAI
			rgb_matrix_set_color(85, rgbVAD.r, rgbVAD.g, rgbVAD.b);
			rgb_matrix_set_color(35, 0x80, 0x80, 0x80); //RGB_SPI
			rgb_matrix_set_color(52, 0x80, 0x80, 0x80);
			rgb_matrix_set_color(84, 0x80, 0x80, 0x80); //RGB_SPI
			rgb_matrix_set_color(86, 0x80, 0x80, 0x80);
			rgb_matrix_set_color(41, 0xF0, 0x00, 0xFF); //MAS_MGT
			rgb_matrix_set_color(42, 0x00, 0x02, 0xFF); //MAS_BLU
			rgb_matrix_set_color(57, 0xFF, 0x00, 0x00); //MAS_RED
			rgb_matrix_set_color(58, 0x00, 0x00, 0x00); //MAS_KEY
			rgb_matrix_set_color(59, 0x00, 0xFF, 0xF7); //MAS_CYN
			rgb_matrix_set_color(70, 0xFF, 0xDA, 0x00); //MAS_YEL
			rgb_matrix_set_color(71, 0x00, 0xFF, 0x01); //MAS_GRN
			rgb_matrix_set_color(72, 0xFF, 0xA5, 0x18); //MAS_CRM
			rgb_matrix_set_color(60, 0x81, 0x3C, 0xFF); //MAS_PRP
			rgb_matrix_set_color(43, 0xFF, 0xFF, 0xFF); //MAS_WHT
		}
		break;
		}
	}
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void)
{
	autoshift_disable();
	rgb_matrix_sethsv(128, 255, 255);
	// rgb_matrix_sethsv(192, 112, 255);
	// rgb_matrix_mode(4);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
	static uint32_t key_timer;

	switch (keycode) {
	case U_T_AUTO:
		if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
			TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
		}

		return false;

	case U_T_AGCR:
		if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
			TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
		}

		return false;

	case DBG_TOG:
		if (record->event.pressed) {
			TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
		}

		return false;

	case DBG_MTRX:
		if (record->event.pressed) {
			TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
		}

		return false;

	case DBG_KBD:
		if (record->event.pressed) {
			TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
		}

		return false;

	case DBG_MOU:
		if (record->event.pressed) {
			TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
		}

		return false;

	case MD_BOOT:
		if (record->event.pressed) {
			key_timer = timer_read32();
		} else {
			if (timer_elapsed32(key_timer) >= 500) {
				reset_keyboard();
			}
		}

		return false;

	case MAS_TOG:
		if (record->event.pressed) {
			switch (rgb_matrix_get_flags()) {
			case LED_FLAG_ALL: {
				rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
				rgb_matrix_set_color_all(0, 0, 0);
			}
			break;

			case LED_FLAG_KEYLIGHT: {
				rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
				rgb_matrix_set_color_all(0, 0, 0);
			}
			break;

			case LED_FLAG_UNDERGLOW: {
				rgb_matrix_set_flags(LED_FLAG_NONE);
				rgb_matrix_disable_noeeprom();
			}
			break;

			default: {
				rgb_matrix_set_flags(LED_FLAG_ALL);
			}
			break;
			}
		}

		return false;

	case MAS_CRM:
		if (record->event.pressed) {
			rgb_matrix_sethsv(32, 160, 255);
		}

		return false;

	case MAS_PRP:
		if (record->event.pressed) {
			rgb_matrix_sethsv(192, 112, 255);
		}

		return false;

	case MAS_RED:
		if (record->event.pressed) {
			rgb_matrix_sethsv(0, 255, 255);
		}

		return false;

	case MAS_GRN:
		if (record->event.pressed) {
			rgb_matrix_sethsv(88, 255, 255);
		}

		return false;

	case MAS_BLU:
		if (record->event.pressed) {
			rgb_matrix_sethsv(168, 255, 255);
		}

		return false;

	case MAS_CYN:
		if (record->event.pressed) {
			rgb_matrix_sethsv(128, 255, 255);
		}

		return false;

	case MAS_MGT:
		if (record->event.pressed) {
			rgb_matrix_sethsv(216, 255, 255);
		}

		return false;

	case MAS_YEL:
		if (record->event.pressed) {
			rgb_matrix_sethsv(40, 255, 255);
		}

		return false;

	case MAS_KEY:
		if (record->event.pressed) {
			rgb_matrix_sethsv(0, 0, 0);
		}

		return false;

	case MAS_WHT:
		if (record->event.pressed) {
			rgb_matrix_sethsv(128, 0, 255);
		}

		return false;

	default:
		return true; //Process all other keycodes normally
	}
}

