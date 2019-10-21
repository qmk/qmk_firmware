#include QMK_KEYBOARD_H

enum dz65rgb_layers {
	_QWERTY,
	_FNM,
	_NAV,
	_FNC
};

enum dz65rgb_keycodes {
	REBOOT = SAFE_RANGE,
	REEPROM,
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

#define TG_NKRO MAGIC_TOGGLE_NKRO
#define _V_V_V_ KC_TRNS
#define LT_CAPS LT(_NAV, KC_CAPS)
extern bool autoshift_enabled;
#define MT_APP  RALT_T(KC_APP)
#define LM_LALT LM(_FNM, MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_65_ansi(
		KC_GESC, KC_1,     KC_2,     KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,  \
		KC_TAB,  KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP, \
		LT_CAPS, KC_A,     KC_S,     KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,  KC_PGDN, \
		KC_LSPO, KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSPC,           KC_UP,   KC_END,  \
		KC_LCTL, KC_LGUI,  LM_LALT,                   KC_SPC,                             KC_RALT, MO(_FNC), KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT  \
	),
	[_FNM]    = LAYOUT_65_ansi(
		_______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,  _______, _______, _______, \
		_______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, \
		_______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______, _______, \
		_______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______, _______, \
		_______, _______,  _V_V_V_,                   _______,                            _______, _______,  _______,  _______, _______, _______  \
	),
	[_NAV]    = LAYOUT_65_ansi(
		KC_NLCK, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,   KC_PAST,  KC_PMNS,  KC_PPLS, _______, _______, \
		_______, KC_PGUP,  KC_HOME, KC_UP,   KC_END,  _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PSLS,  KC_PSCR,  KC_SLCK, KC_INS,  KC_PMNS, \
		_V_V_V_, KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______,  _______,           KC_PENT, KC_PPLS, \
		_______, _______,  _______, _______, _______, _______, KC_P0,   KC_P0,   KC_P0,   KC_PDOT, KC_PSLS,  _______,           _______, _______, \
		_______, _______,  _______,                   _______,                            _______, _______,  _______,  _______, _______, _______  \
	),
	[_FNC]    = LAYOUT_65_ansi(
		_______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______, KC_ASTG, \
		_______, RGB_MOD,  RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, MAS_MGT, MAS_BLU, MAS_WHT,  RGB_RMOD, RGB_MOD, _______, KC_MPRV, \
		_______, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, _______, MAS_RED, MAS_KEY, MAS_CYN, MAS_PRP,  _______,           EEP_RST, KC_MNXT, \
		_______, RGB_TOG,  _______, _______, REEPROM, REBOOT,  TG_NKRO, MAS_YEL, MAS_GRN, MAS_CRM, _______,  _______,           KC_VOLU, KC_MUTE, \
		_______, _______,  _______,                  _______,                             _______, _V_V_V_,  _______,  RGB_SPD, KC_VOLD, RGB_SPI  \
	),
	/*
	[_LEDS]    = LAYOUT_65_ansi(
		17, 16, 15, 14, 13, 12, 11, 10,  9, 18, 19, 20, 21, 22, 23, \
		 7,  6,  5,  4,  3,  2,  1,  0, 26, 27, 28, 29, 30, 31, 24, \
		 8, 48, 47, 46, 45, 44, 43, 51, 52, 53, 54, 55,     56, 25, \
		49, 40, 39, 38, 37, 36, 60, 61, 62, 63, 57, 58,     59, 32, \
		50, 42, 41,         35,             64, 65, 66, 67, 34, 33  \
	),
	*/
};

/*
17,  16,  15,  14,  13,  12,  11,  10,   9,  18,  19,  20,  21,  22,  23
 7,   6,   5,   4,   3,   2,   1,   0,  26,  27,  28,  29,  30,  31,  24
 8,  48,  47,  46,  45,  44,  43,  51,  52,  53,  54,  55,       56,  25
49,  40,  39,  38,  37,  36,  60,  61,  62,  63,  57,  58,       59,  32
50,  42,  41,            35,                 64,  65,  66,  67,  34,  33

ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   -,   =,  BCK, DEL
TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   [,   ],    \,   -
CPS, A,   S,   D,   F,   G,   H,   J,   K,   L,   COL, QOT,  RETURN,   +
SFT, Z,   X,   C,   V,   B,   N,   M,   COM, DOT, SLS, SHIFT,    UP,   0
CTL, GUI, ALT,        SPACEBAR,              ALT, FN, CTL, LFT, DWN, RIT
*/
void rgb_matrix_indicators_user(void)
{
	if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(8, 0xFF, 0xFF, 0xFF);
	}

	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
		case _NAV:
			if (IS_LED_ON(this_led, USB_LED_NUM_LOCK)) {
				rgb_matrix_set_color(17, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(26, 0xFF, 0xFF, 0x00);
			} else {
				rgb_matrix_set_color(17, 0x00, 0x00, 0x00);
				rgb_matrix_set_color(26, 0xFF, 0x00, 0x00);
			}

			rgb_matrix_set_color(8, 0xFF, 0xFF, 0xFF); // layer indicator
			// ESDF
			rgb_matrix_set_color(4, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(47, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(46, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(45, 0xFF, 0x00, 0x00);
			// home/end
			rgb_matrix_set_color(5, 0x00, 0xFF, 0x00);
			rgb_matrix_set_color(3, 0x00, 0xFF, 0x00);
			// pgup/dn
			rgb_matrix_set_color(6, 0x00, 0x00, 0xFF);
			rgb_matrix_set_color(48, 0x00, 0x00, 0xFF);
			// numpad
			rgb_matrix_set_color(10,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(9,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(18,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(0, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(27, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(51, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(52, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(53, 0xFF, 0xFF, 0x00);
			// zero
			rgb_matrix_set_color(60, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(61, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(62, 0xFF, 0x00, 0x00);
			// dot
			rgb_matrix_set_color(63, 0x00, 0x00, 0xFF);
			// math shit
			rgb_matrix_set_color(19,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(20,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(21,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(28,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(24,  0x00, 0x00, 0xFF); // macro minus
			rgb_matrix_set_color(25,  0x00, 0x00, 0xFF); // macro plus
			// other
			rgb_matrix_set_color(29, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF);
			break;

		case _FNC: {
			HSV hsv = { rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
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
			rgb_matrix_set_color(65, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(36, 0xFF, 0x00, 0x00); // MASBOOT
			rgb_matrix_set_color(37, 0xFF, 0x00, 0x40); // REEPROM
			rgb_matrix_set_color(37, 0xFF, 0x00, 0x40); // 60
			rgb_matrix_set_color(59, 0x00, 0x80, 0xFF); // KC_VOLU
			rgb_matrix_set_color(34, 0x00, 0x80, 0xFF);
			rgb_matrix_set_color(32, 0xFF, 0x00, 0x00); // KC_MUTE
			rgb_matrix_set_color(24, 0xFF, 0x40, 0x00); // KC_MPRV
			rgb_matrix_set_color(25, 0xFF, 0x40, 0x00);

			if (this_led & (1 << !autoshift_enabled)) {
				rgb_matrix_set_color(15, 0xFF, 0x00, 0x00); // KC_ASTG
			} else {
				rgb_matrix_set_color(15, 0xFF, 0xFF, 0x00);
			}

			rgb_matrix_set_color(6, 0xFF, 0x80, 0x00); //RGB_MOD
			rgb_matrix_set_color(48, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(29, 0xFF, 0x80, 0x00); //RGB_MOD
			rgb_matrix_set_color(30, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(40, 0xFF, 0x40, 0x00); //RGB_TOG
			rgb_matrix_set_color(4, rgbHUI.r, rgbHUI.g, rgbHUI.b); //RGB_HUI
			rgb_matrix_set_color(46, rgbHUD.r, rgbHUD.g, rgbHUD.b);
			rgb_matrix_set_color(3, rgbSAI.r, rgbSAI.g, rgbSAI.b); //RGB_SAI
			rgb_matrix_set_color(45, rgbSAD.r, rgbSAD.g, rgbSAD.b);
			rgb_matrix_set_color(2, rgbVAI.r, rgbVAI.g, rgbVAI.b); //RGB_VAI
			rgb_matrix_set_color(44, rgbVAD.r, rgbVAD.g, rgbVAD.b);
			rgb_matrix_set_color(35, rgb.r, rgb.g, rgb.b); // config display
			rgb_matrix_set_color(5, 0x80, 0x80, 0x80); //RGB_SPI
			rgb_matrix_set_color(47, 0x80, 0x80, 0x80);
			rgb_matrix_set_color(67, 0x80, 0x80, 0x80); //RGB_SPI
			rgb_matrix_set_color(33, 0x80, 0x80, 0x80);
			rgb_matrix_set_color(26, 0xF0, 0x00, 0xFF); //MAS_MGT
			rgb_matrix_set_color(27, 0x00, 0x02, 0xFF); //MAS_BLU
			rgb_matrix_set_color(51, 0xFF, 0x00, 0x00); //MAS_RED
			rgb_matrix_set_color(52, 0x00, 0x00, 0x00); //MAS_KEY
			rgb_matrix_set_color(53, 0x00, 0xFF, 0xF7); //MAS_CYN
			rgb_matrix_set_color(61, 0xFF, 0xDA, 0x00); //MAS_YEL
			rgb_matrix_set_color(62, 0x00, 0xFF, 0x01); //MAS_GRN
			rgb_matrix_set_color(63, 0xFF, 0xA5, 0x18); //MAS_CRM
			rgb_matrix_set_color(54, 0x81, 0x3C, 0xFF); //MAS_PRP
			rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF); //MAS_WHT
		}
		break;
		}
	}
}

void matrix_init_user(void)
{
	//user initialization
}

void matrix_scan_user(void)
{
	//user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
	static uint32_t key_timer;

	switch (keycode) {
	case REBOOT:
		if (record->event.pressed) {
			key_timer = timer_read32();
		} else {
			if (timer_elapsed32(key_timer) >= 500) {
				reset_keyboard();
			}
		}

		return false;

	case REEPROM:
		if (record->event.pressed) {
			key_timer = timer_read32();
		} else {
			if (timer_elapsed32(key_timer) >= 500) {
				eeconfig_init();
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
		return true;
	}
}
