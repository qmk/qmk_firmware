#include QMK_KEYBOARD_H


enum dz60rgb_layers {
	_QWERTY,
	_FNM,
	_NAV,
	_RGB,
	_FNC
};

enum dz60rgb_keycodes {
	REBOOT = SAFE_RANGE,
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
#define _V_V_V_ KC_TRNS
#define LT_CAPS LT(_NAV, KC_CAPS)
#define LT_DEL  LT(_RGB, KC_DEL)
extern bool autoshift_enabled;
#define MT_SLSH RSFT_T(KC_SLSH)
#define MT_APP  RALT_T(KC_APP)
#define LM_LALT LM(_FNM, MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
		LT_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
		KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MT_SLSH,          KC_UP,   LT_DEL,  \
		KC_LCTL, KC_LGUI, LM_LALT,       KC_SPC,                                MT_APP,  MO(_FNC),         KC_LEFT, KC_DOWN, KC_RGHT  \
	),
	[_FNM] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
		_______, _______, _V_V_V_,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_NAV] = LAYOUT(
		KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PMNS, KC_PPLS, KC_DEL,  \
		_______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PSLS, KC_PSCR, KC_SLCK, KC_INS,  \
		_V_V_V_, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, KC_PENT,          \
		_______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_P0,   KC_PDOT, _______,          _______, _______, \
		_______, _______, _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_RGB] = LAYOUT(
		_______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
		_______, RGB_MOD,  RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, MAS_MGT, MAS_BLU, MAS_WHT, RGB_RMOD, RGB_MOD, _______, \
		_______, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, _______, MAS_RED, MAS_KEY, MAS_CYN, MAS_PRP, _______, _______,          \
		_______, RGB_TOG,  _______, _______, _______, _______, _______, MAS_YEL, MAS_GRN, MAS_CRM, _______,          _______, _V_V_V_, \
		_______, _______,  _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_FNC] = LAYOUT( // fuck it edition
		RCTL(KC_ESC),  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,         KC_F9,        KC_F10,        KC_F11,        KC_F12,        KC_ASTG,       \
		RCTL(KC_TAB),  RCTL(KC_Q), RCTL(KC_W), RCTL(KC_E), RCTL(KC_R), RCTL(KC_T), RCTL(KC_Y), RCTL(KC_U), RCTL(KC_I),    RCTL(KC_O),   RCTL(KC_P),    RCTL(KC_LBRC), RCTL(KC_RBRC), RCTL(KC_BSLS), \
		RCTL(KC_CAPS), RCTL(KC_A), RCTL(KC_S), RCTL(KC_D), RCTL(KC_F), RCTL(KC_G), RCTL(KC_H), RCTL(KC_J), RCTL(KC_K),    RCTL(KC_L),   RCTL(KC_SCLN), RCTL(KC_QUOT), RCTL(KC_ENT),                 \
		RCTL(KC_LSFT), RCTL(KC_Z), RCTL(KC_X), RCTL(KC_C), RCTL(KC_V), REBOOT,     RCTL(KC_N), RCTL(KC_M), RCTL(KC_COMM), RCTL(KC_DOT), RCTL(KC_SLSH),                KC_VOLU, RCTL(KC_DEL),        \
		RCTL(KC_LCTL), RCTL(KC_LGUI), RCTL(KC_LALT),                   RCTL(KC_SPC),                       KC_MUTE,       _V_V_V_,                     RCTL(KC_LEFT), KC_VOLD, RCTL(KC_RGHT)        \
	),
	/*
	[_FNC] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ASTG, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
		_______, _______, _______, _______, _______, REBOOT,  _______, _______, _______, _______, RCTL(KC_SLSH),    KC_VOLU, RCTL(KC_DEL), \
		_______, _______, _______,                   _______,                   KC_MUTE, _______,    RCTL(KC_LEFT), KC_VOLD, RCTL(KC_RGHT)  \
	),
	[_LAYER] = LAYOUT(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
		_______, _______, _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	 [_LAYER] = LAYOUT(
		13,      12,      11,       10,      9,       8,       7,       6,       5,       4,       3,       2,       1,       0,      \
		27,      26,      25,       24,      23,      22,      21,      20,      19,      18,      17,      16,      15,      14,     \
		40,      39,      38,       37,      36,      35,      34,      33,      32,      31,      30,      29,      28,              \
		53,      52,      51,       50,      49,      48,      47,      46,      45,      44,      43,               42,      41,     \
		62,      61,      60,                         59,                        58,      57,               56,      55,      54      \
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
				rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(19, 0xFF, 0xFF, 0x00);
			} else {
				rgb_matrix_set_color(13, 0x00, 0x00, 0x00);
				rgb_matrix_set_color(19, 0xFF, 0x00, 0x00);
			}

			rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF); // layer indicator
			// ESDF
			rgb_matrix_set_color(24, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(38, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(36, 0xFF, 0x00, 0x00);
			// home/end
			rgb_matrix_set_color(25, 0x00, 0xFF, 0x00);
			rgb_matrix_set_color(23, 0x00, 0xFF, 0x00);
			// pgup/dn
			rgb_matrix_set_color(26, 0x00, 0x00, 0xFF);
			rgb_matrix_set_color(39, 0x00, 0x00, 0xFF);
			// numpad
			rgb_matrix_set_color(6,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(5,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(4,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(20, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(18, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(33, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(32, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(31, 0xFF, 0xFF, 0x00);
			// zero
			rgb_matrix_set_color(47, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(46, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(45, 0xFF, 0x00, 0x00);
			// dot
			rgb_matrix_set_color(44, 0x00, 0x00, 0xFF);
			// math shit
			rgb_matrix_set_color(3,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(2,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(1,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(0,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(17, 0x00, 0x00, 0xFF);
			// other
			rgb_matrix_set_color(16, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(15, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(14, 0xFF, 0xFF, 0xFF);
			break;

		case _RGB: {
			HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
			HSV hui = hsv;
			HSV hud = hsv;
			HSV sai = hsv;
			HSV sad = hsv;
			HSV vai = hsv;
			HSV vad = hsv;
			hui.h = hsv.h + 8;
			hud.h = hsv.h - 8;
			sai.s = hsv.s + 16 > 255 ? 255 : hsv.s + 16;
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
			rgb_matrix_set_color(41, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(59, rgb.r, rgb.g, rgb.b); // color indicator
			rgb_matrix_set_color(26, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(39, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(16, 0xFF, 0x80, 0x00); //RGB_RMOD
			rgb_matrix_set_color(15, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(52, 0xFF, 0x40, 0x00); //TOG
			rgb_matrix_set_color(25, 0x80, 0x80, 0x80); //SPI
			rgb_matrix_set_color(38, 0x80, 0x80, 0x80); //SPD
			rgb_matrix_set_color(24, rgbHUI.r, rgbHUI.g, rgbHUI.b); //HUI
			rgb_matrix_set_color(37, rgbHUD.r, rgbHUD.g, rgbHUD.b); //HUD
			rgb_matrix_set_color(23, rgbSAI.r, rgbSAI.g, rgbSAI.b); //SAI
			rgb_matrix_set_color(36, rgbSAD.r, rgbSAD.g, rgbSAD.b); //SAD
			rgb_matrix_set_color(22, rgbVAI.r, rgbVAI.g, rgbVAI.b); //VAI
			rgb_matrix_set_color(35, rgbVAD.r, rgbVAD.g, rgbVAD.b); //VAD
			rgb_matrix_set_color(19, 0xF0, 0x00, 0xFF); //MAS_MGT
			rgb_matrix_set_color(18, 0x00, 0x02, 0xFF); //MAS_BLU
			rgb_matrix_set_color(33, 0xFF, 0x00, 0x00); //MAS_RED
			rgb_matrix_set_color(32, 0x00, 0x00, 0x00); //MAS_KEY
			rgb_matrix_set_color(31, 0x00, 0xFF, 0xF7); //MAS_CYN
			rgb_matrix_set_color(46, 0xFF, 0xDA, 0x00); //MAS_YEL
			rgb_matrix_set_color(45, 0x00, 0xFF, 0x01); //MAS_GRN
			rgb_matrix_set_color(44, 0xFF, 0xA5, 0x18); //MAS_CRM
			rgb_matrix_set_color(30, 0x81, 0x3C, 0xFF); //MAS_PRP
			rgb_matrix_set_color(17, 0xFF, 0xFF, 0xFF); //MAS_WHT
		}
		break;

		case _FNC:
			rgb_matrix_set_color(57, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(48, 0xFF, 0x00, 0x00); // bootloader
			rgb_matrix_set_color(42, 0x00, 0x80, 0xFF); // vol
			rgb_matrix_set_color(55, 0x00, 0x80, 0xFF);
			rgb_matrix_set_color(58, 0xFF, 0x00, 0x00); // mute
			rgb_matrix_set_color(56, 0xFF, 0x80, 0x00); // ctrl+left/right
			rgb_matrix_set_color(54, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(41, 0xFF, 0x00, 0x40); // ctrl+delete
			rgb_matrix_set_color(43, 0xFF, 0x00, 0x40); // ctrl+slash

			if (this_led & (1 << !autoshift_enabled)) {
				rgb_matrix_set_color(0, 0xFF, 0x00, 0x00); // KC_ASTG
			} else {
				rgb_matrix_set_color(0, 0xFF, 0xFF, 0x00);
			}

			break;
		}
	}

	if (this_led & (1 << USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	}
}

void matrix_init_user(void)
{
	//user initialization
	autoshift_disable();
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
				rgb_matrix_enable_noeeprom();
				rgb_matrix_mode_noeeprom(1);
				rgb_matrix_sethsv_noeeprom(11, 11, 11);
				wait_ms(150);
				reset_keyboard();
			} else {
				register_code(KC_RCTL);
				tap_code(KC_B);
				unregister_code(KC_RCTL);
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
