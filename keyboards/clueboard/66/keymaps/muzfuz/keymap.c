#include "66.h"

// Helpful defines
#define ESC_CTL     CTL_T(KC_ESCAPE)            // Tap for Esc, hold for Ctrl
#define _______ KC_TRNS
#define _FL_KCF LT(1,KC_F)
#define _FL_KCJ LT(1,KC_J)
#define _AL_KCA LT(2,KC_A)
#define CMD_ENT LGUI(LSFT(KC_ENT))
#define HASHRKT M(0)
#define CLNEQLS M(1)

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _FL 1
#define _AL 2
#define _CL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = KEYMAP(
  KC_GRV,KC_1,      KC_2,     KC_3,    KC_4,       KC_5,     KC_6,     KC_7,       KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,HASHRKT,        LGUI(KC_C), \
  KC_TAB, KC_Q,     KC_W,     KC_E,    KC_R,       KC_T,     KC_Y,     KC_U,       KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,                LGUI(KC_V), \
  ESC_CTL,_AL_KCA,  KC_S,     KC_D,    _FL_KCF,    KC_G,     KC_H,     _FL_KCJ,    KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_LGUI,                            \
  KC_LSFT,KC_LSFT,  KC_Z,     KC_X,    KC_C,       KC_V,     KC_B,     KC_N,       KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_SLSH,KC_RSFT,        KC_UP,           \
  CMD_ENT,          KC_LCTL,  KC_LALT,  KC_LGUI,          KC_ENT, KC_SPC,                        KC_RGUI,KC_RALT,KC_RCTL,MO(_CL), KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_DEL,         KC_VOLU, \
  _______,HASHRKT,_______,KC_LCBR,KC_RCBR,_______,_______,KC_UNDS,KC_PLUS,KC_PIPE,_______,_______,_______,KC_MUTE,                KC_VOLD, \
  _______,CLNEQLS,_______,KC_LBRC,KC_RBRC,_______,_______,KC_MINS,KC_EQL,KC_BSLS,KC_TILD,KC_GRV,_______,_______,                         \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,         \
  _______,_______,_______,_______,        _______,_______,                        _______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _FL: Function Layer
   */
[_AL] = KEYMAP(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                _______, \
  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,_______,_______,                         \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,         \
  _______,_______,_______,_______,        _______,_______,                        _______,_______,_______,_______,_______,_______,_______),

  /* Keymap _CL: Control layer
   */
[_CL] = KEYMAP(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET,                    RGB_VAD, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,         \
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_HUI),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
			case 0:
				SEND_STRING("=>");
				return false;
      case 1:
        SEND_STRING(":=");
        return false;
		}
	}
	return MACRO_NONE;
};
