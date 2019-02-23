#include QMK_KEYBOARD_H
extern bool g_suspend_state;
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_LAYER0] = LAYOUT_HHKB_ISO( /* Base */
			RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
		    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
			CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT,   KC_HOME,  KC_ENT, \
		    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
		    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		[_LAYER1] = LAYOUT_HHKB_ISO( /* FN */
				RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
			    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
				CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT, KC_HOME,  KC_ENT, \
			    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
			    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		[_LAYER2] = LAYOUT_HHKB_ISO( /* LIGHT */
				RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
			    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
				CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT,  KC_HOME,  KC_ENT, \
			    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
			    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		[_LAYER3] = LAYOUT_HHKB_ISO( /* NUMPAD */
				RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
			    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
				CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT,  KC_HOME, KC_ENT, \
			    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
			    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		[_LAYER4] = LAYOUT_HHKB_ISO( /* MAC */
				RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
			    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
				CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT,  KC_HOME,  KC_ENT, \
			    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
			    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		[_LAYER5] = LAYOUT_HHKB_ISO( /* RETURN LAYYER0 */
				RESET,         RGB_MOD,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,      KC_MINS,  KC_EQL,  KC_BSPC,\
			    KC_TAB,          KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,      KC_LBRC,  KC_RBRC, KC_BSLASH,\
				CTL_T(KC_CAPS),  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,   KC_QUOT,   KC_HOME,  KC_ENT, \
			    KC_LSFT,         KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,           KC_1,\
			    KC_LCTL,         KC_LGUI,  KC_LALT,                KC_SPC,                                   KC_RALT,   KC_RGUI,           KC_RCTL),
		};
void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

	bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	  return true;
	}
