#include QMK_KEYBOARD_H

extern bool g_suspend_state;

enum dz60rgb_layers {
	_QWERTY,
	_FNM,
	_NAV,
	_RGB,
	_FNC
};

enum dz60rgb_keycodes {
	REBOOT = SAFE_RANGE,
	RGB_CRM,
	// RGB_RMOD,
	// TAPA,
};

#define LT_CAPS LT(_NAV, KC_CAPS)
#ifdef RGB_MATRIX_ENABLE
#define LT_DEL  LT(_RGB, KC_DEL)
extern rgb_config_t rgb_matrix_config;
extern bool autoshift_enabled;
#else
#define LT_DEL KC_DEL
#endif // RGB_MATRIX_ENABLE
#define MT_SLSH RSFT_T(KC_SLSH)
#define MT_APP  RALT_T(KC_APP)
#define LM_LALT LM(_FNM, MOD_LALT)
// #define LM_LCTL LM(_FNC, MOD_LCTL)

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
		_______, _______, _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_NAV] = LAYOUT(
		KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PMNS, KC_PPLS, KC_DEL,  \
		_______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PSLS, KC_PSCR, KC_SLCK, KC_INS,  \
		_______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, KC_PENT,          \
		_______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_P0,   KC_PDOT, _______,          _______, _______, \
		_______, _______, _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_RGB] = LAYOUT(
		_______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
		_______, RGB_MOD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, RGB_RMOD, RGB_VAD, RGB_SPD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,          \
		_______, RGB_TOG,  RGB_CRM, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
		_______, _______,  _______,                   _______,                   _______, _______,          _______, _______, _______  \
	),
	[_FNC] = LAYOUT( // fuck it edition
		RCTL(KC_ESC),  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,         KC_F9,        KC_F10,        KC_F11,        KC_F12,        KC_ASTG,       \
		RCTL(KC_TAB),  RCTL(KC_Q), RCTL(KC_W), RCTL(KC_E), RCTL(KC_R), RCTL(KC_T), RCTL(KC_Y), RCTL(KC_U), RCTL(KC_I),    RCTL(KC_O),   RCTL(KC_P),    RCTL(KC_LBRC), RCTL(KC_RBRC), RCTL(KC_BSLS), \
		RCTL(KC_CAPS), RCTL(KC_A), RCTL(KC_S), RCTL(KC_D), RCTL(KC_F), RCTL(KC_G), RCTL(KC_H), RCTL(KC_J), RCTL(KC_K),    RCTL(KC_L),   RCTL(KC_SCLN), RCTL(KC_QUOT), RCTL(KC_ENT),                 \
		RCTL(KC_LSFT), RCTL(KC_Z), RCTL(KC_X), RCTL(KC_C), RCTL(KC_V), REBOOT,     RCTL(KC_N), RCTL(KC_M), RCTL(KC_COMM), RCTL(KC_DOT), RCTL(KC_SLSH),                KC_VOLU, RCTL(KC_DEL),        \
		RCTL(KC_LCTL), RCTL(KC_LGUI), RCTL(KC_LALT),                   RCTL(KC_SPC),                       KC_MUTE,       _______,                     RCTL(KC_LEFT), KC_VOLD, RCTL(KC_RGHT)        \
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
#ifdef RGB_MATRIX_ENABLE
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
			
		case _RGB:
			rgb_matrix_set_color(41, 0xFF, 0xFF, 0xFF); // layer indicator
			
			rgb_matrix_set_color(26, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(39, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(52, 0xFF, 0x40, 0x00); //TOG
			
			rgb_matrix_set_color(25, 0x00, 0xFF, 0xFF); //VAI
			rgb_matrix_set_color(38, 0x00, 0x40, 0x40); //VAD
			
			rgb_matrix_set_color(24, 0x80, 0x80, 0x80); //SPI
			rgb_matrix_set_color(37, 0x80, 0x80, 0x80); //SPD
			
			rgb_matrix_set_color(23, 0xFF, 0x80, 0x00); //HUI
			rgb_matrix_set_color(36, 0xFF, 0x00, 0x80); //HUD
			
			rgb_matrix_set_color(22, 0xFF, 0x00, 0x00); //SAI
			rgb_matrix_set_color(35, 0xFF, 0xAA, 0xAA); //SAD
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
	
#endif // RGB_MATRIX_ENABLE
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
		
	case RGB_CRM:
		if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
			rgb_matrix_sethsv(40, 144, 255);
#endif // RGB_MATRIX_ENABLE
		}
		
		return false;
		
	default:
		return true;
	}
}

