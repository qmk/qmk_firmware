#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_LAYER0] = LAYOUT_60_tsangan_hhkb( /* Base */
			      KC_GESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
			      KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
				  CTL_T(KC_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
			      KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          MO(2),
			      KC_LCTL,         KC_LGUI, KC_LALT,                   KC_SPACE,                                   KC_RALT, MO(1),            KC_RCTL),
		[_LAYER1] = LAYOUT_60_tsangan_hhkb( /* FN */
				  KC_GRAVE, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS, KC_TRNS, 
	              KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_CALC,  KC_TRNS,  KC_INS,   KC_TRNS,  KC_PSCR,  KC_SLCK,  KC_PAUS,  RESET  ,
			      KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_HOME,  KC_PGUP,            KC_TRNS,
			      KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_TRNS,  KC_TRNS,  MAGIC_TOGGLE_NKRO,  KC_TRNS,  KC_TRNS,  KC_END,   KC_PGDOWN,KC_MNXT,            KC_TRNS,
			      KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                          KC_TRNS,  KC_TRNS,            KC_TRNS),
		[_LAYER2] = LAYOUT_60_tsangan_hhkb( /* FN2 */
				  KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL ,KC_TRNS, 
			  	  KC_TRNS,  RGB_TOG,  KC_TRNS,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  RGB_MOD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RESET,
				  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_SPI,  RGB_SPD,  KC_TRNS,  KC_TRNS,            KC_TRNS,
				  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
				  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                          KC_TRNS,  KC_TRNS,            KC_TRNS),
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
