#include "tada68.h"
#include <print.h>

#define _BL 0
#define _FL 1

#define _______ 	KC_TRNS
#define FN_CAPS 	LT(_FL, KC_CAPS)

// Keys useful in Eclipse IDE
#define CD_CMPL		LCTL(KC_SPC)
#define CD_TEST		LCTL(KC_F11)

//Tap Dance Declarations
enum {
  TD_F5 = 0
};

void dance_end(qk_tap_dance_state_t *state, void *user_data) {
	//sprintf("%d count", state->count)
	#ifdef CONSOLE_ENABLE
	xprintf("foo Fu\n", state->count);
	#endif //CONSOLE_ENABLE
  if (state->count == 1) {
	  if(state->pressed) {
		  // key is held
		  register_code (KC_RSFT);
		  register_code (KC_F);
	  }
	  else {
		register_code (KC_F);
	}
  }
}

void dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_F);
    unregister_code (KC_RSFT);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //[TD_F5]  = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
  [TD_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_end, dance_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |Del |
   * |-------------------------------------------------------    -----|
   * |Fn     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;| '|  #|Entr|PgUp|
   * |----------------------------------------------------------------|
   * |Shift|  \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .| /|Rshift|Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = KEYMAP_ISO(
  KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC,  KC_GRV, \
  KC_TAB ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_NUHS,  KC_DEL, \
  FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, KC_PGUP,  \
  KC_LSFT, KC_NUBS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,   KC_UP, KC_PGDN, \
  KC_LCTL, KC_LGUI, KC_LALT,                    KC_SPC,                            KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL1: Function Layer 1
   * ,----------------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete|    |   
   * |----------------------------------------------------------------|
   * |     |   | ↑ |   |   |   |   |   |   |   |   |   |   |     | Ins|
   * |-------------------------------------------------------    -----|
   * |       | ← | ↓ | → |   |   |   |   |   |   |   |  |   |    |Home|
   * |----------------------------------------------------------------|
   * |     |   |   |   | L+|LED| L-|   | V+|  V-|Mut|  | MsBtn|Up| End|
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    | Lt| Dn| Rt |
   * `----------------------------------------------------------------'
   */
[_FL] = KEYMAP_ISO(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL, _______,  \
  _______, _______, _______, _______,   KC_F5, CD_TEST, _______, KC_HOME,   KC_UP,  KC_END, _______, _______, _______, _______,  KC_INS, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, _______,          _______, KC_HOME, \
  _______, _______, _______, _______,  BL_DEC,  BL_INC, BL_TOGG, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN1, KC_MS_U,  KC_END, \
  _______, _______, _______,                   CD_CMPL,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),
};

