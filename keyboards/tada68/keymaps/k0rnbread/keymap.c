#include "tada68.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS

//////// TAP DANCE SECTION START ////////


//Tap Dance Declarations (double tap r_alt for alt+f4)
enum {
 TD_RALT_CLOSE,
 SINGLE_TAP = 1,
 SINGLE_HOLD = 2,
 DOUBLE_TAP = 3,
 DOUBLE_HOLD = 4,
 DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//// Tap Dance Definitions ////

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap ralttap_state = {
  .is_press_action = true,
  .state = 0
};

//Define function for double tapping r_alt to send alt+f4
void ralt_finished (qk_tap_dance_state_t *state, void *user_data) {
  ralttap_state.state = cur_dance(state);
  switch (ralttap_state.state) {
    case SINGLE_TAP: register_code(KC_RALT); break;
    case SINGLE_HOLD: register_code(KC_RALT); break;
    case DOUBLE_TAP: register_code(KC_Q); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_RALT); unregister_code(KC_RALT); register_code(KC_RALT);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void ralt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ralttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_RALT); break;
    case SINGLE_HOLD: unregister_code(KC_RALT); break;
    case DOUBLE_TAP: unregister_code(KC_Q); break;
    case DOUBLE_HOLD: unregister_code(KC_RALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_RALT);
  }
  ralttap_state.state = 0;
}

//All tap dance functions would go here. 
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RALT_CLOSE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, ralt_finished, ralt_reset)
};

//// TAP DANCE SECTION END ////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN, \
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                     TD(TD_RALT_CLOSE),MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|       |Ins |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |MUT|VU-|VU+|   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_FL] = KEYMAP_ANSI(
  _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9, KC_F10, KC_F11, KC_F12,_______, KC_INS ,  \
  _______,_______,_______,_______,_______, _______,_______,_______,_______,_______,_______,_______,_______,_______, KC_HOME, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, KC_END, \
  _______,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______, \
  _______,_______,_______,                    _______,               _______,_______,_______,_______,_______, _______),
};




