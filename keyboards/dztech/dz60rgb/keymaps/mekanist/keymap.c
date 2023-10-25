#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6
#define _LAYER7 7
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_LAYER0] = LAYOUT( /* MAC */
		QK_GESC,  KC_1, 	KC_2, 	  KC_3,  KC_4,  KC_5,  KC_6,	KC_7,  KC_8,	KC_9,	  KC_0,			   KC_MINS,  KC_EQL,  KC_BSPC,
		KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,			   KC_LBRC,  KC_RBRC, KC_BSLS,
		CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,         KC_QUOT,           KC_ENT,
		KC_LSFT,  KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   RSFT_T(KC_SLSH), KC_UP,             LT(2, KC_DEL),
		KC_LCTL,  KC_LALT,  KC_LGUI,                KC_SPC,                KC_RGUI,  MO(1)  , KC_LEFT,         KC_DOWN,           KC_RGHT),
	[_LAYER1] = LAYOUT( /* FN */
		TO(3),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  LGUI(LSFT(KC_5)),   KC_SCRL,  KC_PAUS,  _______,  _______,   QK_BOOT,
		_______,  KC_VOLU,  KC_VOLD,  KC_MUTE,  KC_EJCT,  _______,  KC_ASTR,  KC_PSLS,  KC_HOME,  KC_PGUP,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  KC_PPLS,  KC_PMNS,  KC_END,   KC_PGDN,  MO(5),              KC_MPLY,            _______,
		_______,  _______,  _______,                      TO(4),                        _______,  _______, KC_MPRV,   KC_MSTP,            KC_MFFD),
	[_LAYER2] = LAYOUT( /* LIGHT */
    RGB_TOG,    RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  _______,    _______,    _______,    _______,    _______,
		_______,    RGB_HUD,  RGB_HUI,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
		_______,    RGB_SAD,  RGB_SAI,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,
		_______,    RGB_VAD,  RGB_VAI,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_MOD,                _______,
		_______,    _______,  _______,                          _______,                            _______,    _______,    RGB_SPD,    RGB_RMOD,               RGB_SPI),
	[_LAYER3] = LAYOUT( /* NUMPAD */
		KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,      _______,    _______,    _______,    _______,    KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,  _______,
		_______,    KC_P7,    KC_P8,    KC_P9,    _______,    _______,    _______,    _______,    KC_P7,    KC_P8,    KC_P9,    _______,    _______,    TO(0),
		_______,    KC_P4,    KC_P5,    KC_P6,    _______,    _______,    _______,    _______,    KC_P4,    KC_P5,    KC_P6,    _______,              KC_PENT,
		_______,    KC_P1,    KC_P2,    KC_P3,    _______,    _______,    _______,    _______,    KC_P1,    KC_P2,    KC_P3,    _______,              _______,
		_______,    KC_P0,    KC_PDOT,                        KC_ENT,                             KC_P0,    KC_PDOT,  _______,  _______,              _______),
	[_LAYER4] = LAYOUT( /* WIN */
		QK_GESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,            KC_MINS,  KC_EQL,  KC_BSPC,
		KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,            KC_LBRC,  KC_RBRC, KC_BSLS,
		CTL_T(KC_CAPS),     KC_A,     KC_S,  KC_D,  KC_F,  KC_G,    KC_H,  KC_J,    KC_K,     KC_L,  KC_SCLN,  KC_QUOT,           KC_ENT,
		KC_LSFT,  KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   RSFT_T(KC_SLSH), KC_UP,             LT(2, KC_DEL),
		KC_LCTL,  KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT,  MO(5)  , KC_LEFT,         KC_DOWN,           KC_RIGHT),
	[_LAYER5] = LAYOUT( /* FN */
		_______,  KC_BRID,  KC_BRIU, LCTL(KC_UP), LSFT(KC_F12),     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
		_______,  _______,  KC_UP,    _______,  _______,  _______,  KC_CALC,  _______,  KC_INS,   _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  QK_BOOT,
		_______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,            _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDN, KC_VOLU,           KC_MUTE,
		_______,  _______,  _______,                      TO(0),                        _______,  _______,  KC_MPRV,  KC_VOLD,            KC_MNXT),
}
;



void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
	led_t led_state = host_keyboard_led_state();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (get_highest_layer(layer_state)) {
		case _LAYER1:
			rgb_matrix_layer_helper(0xFF, 0x00, 0x00); break;

		case _LAYER2:
			rgb_matrix_layer_helper(0x00, 0xFF, 0x00); break;

		case _LAYER4:
			rgb_matrix_layer_helper(0xFF, 0xFF, 0x00); break;
		}
	}

	if (led_state.caps_lock) {
		rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	}

	switch (get_highest_layer(layer_state)) {
	case _LAYER3:
		if (led_state.num_lock) {
			rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
		} else {
			rgb_matrix_set_color(13, 0x00, 0x00, 0x00);
		}

		rgb_matrix_set_color(0, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(1, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(1, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(2, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(3, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(4, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(5, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(6, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(7, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(8, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(9, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(10, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(11, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(12, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(14, 0x00, 0x00, 0xFF);
		rgb_matrix_set_color(15, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(16, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(17, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(18, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(19, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(20, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(21, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(22, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(23, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(24, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(25, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(26, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(27, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(28, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(29, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(30, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(31, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(32, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(33, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(34, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(35, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(36, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(37, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(38, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(39, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(40, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(41, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(43, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(44, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(45, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(46, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(47, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(48, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(49, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(50, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(51, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(52, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(53, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(54, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(55, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(56, 0x00, 0x00, 0x00);
		rgb_matrix_set_color(57, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(58, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(59, 0xFF, 0x00, 0x00);
		rgb_matrix_set_color(60, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(61, 0xFF, 0xFF, 0x00);
		rgb_matrix_set_color(62, 0x00, 0x00, 0x00);
		break;
	}
    return false;
}
