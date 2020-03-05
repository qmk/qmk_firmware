#include "split75.h"

#include QMK_KEYBOARD_H

#define QWERTY 0
#define MOD 1

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

//Tap dance enums
enum {
  ALT_OSL1 = 0
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY   ,-----------------------------------------.     ,-----------------------------------------------------.
  *                | ESC | F1  | F2  | F3  | F4  | F5  | F6  |     | F7  | F8  | F9  | F10 | F11 | F12 |Print| Ins | Del |
  * ,-----------.  |-----+-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----+-----------+-----|
  * |  8  |  9  |  |  ~  |  1  |  2  |  3  |  4  |  5  |  6  |     |  7  |  8  |  9  |  0  |  -  |  =  | Backspac  | Home|
  * |-----+-----|  |-----------------------------------------'  ,--------------------------------------------------+-----|
  * |  6  |  7  |  | Tab   |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    | PgUp|
  * |-----+-----|  |---------------------------------------.    `--------------------------------------------------+-----|
  * |  4  |  5  |  | Caps    |  A  |  S  |  D  |  F  |  G  |     |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PgDn|
  * |-----+-----|  |-----------------------------------------.   `-------------------------------------------------+-----|
  * |  2  |  3  |  | Shift     |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |   /   |  Shift  | Up  | End |
  * |-----+-----|  |-----------------------------------------'   ,-------------------------------------------+-----+-----|
  * |  0  |  1  |  | Ctrl  |  GUI |  Alt |   Space   |     |     | Space         |  Alt  |     | Ctrl  | Left| Down|Right|
  * `-----------'  `---------------------------------------'     `-------------------------------------------------------'
  */
  [QWERTY] = KEYMAP(
//--------------------------------Left Hand-----------------------------------| |--------------------------------Right Hand------------------------------------------------
                KC_ESC,   KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,                KC_F7,  KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,   KC_PSCR, KC_INS,   KC_DEL, \
KC_8,  KC_9,    KC_GRAVE, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,                 KC_7,   KC_8,    KC_9,   KC_0,    KC_MINUS, KC_EQUAL, KC_BSPC,           KC_HOME, \
KC_6,  KC_7,    KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                 KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_PGUP, \
KC_4,  KC_5,    KC_CAPS,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                 KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,  KC_ENTER,                    KC_PGDN, \
KC_2,  KC_3,    KC_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,                 KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,                      KC_RSFT, KC_UP,   KC_END, \
KC_0,  KC_1,    KC_LCTL,  KC_LGUI, KC_LALT, MO(MOD),KC_SPC,                       KC_SPC,         KC_RALT, MO(MOD),KC_RCTL,                      KC_LEFT, KC_DOWN, KC_RIGHT \
  ),

  [MOD] = KEYMAP(
//--------------------------------Left Hand---------------------------------------|    |--------------------------------Right Hand------------------------------------------------
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, \
KC_TRNS, KC_TRNS,   KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                 KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,            KC_PSCR, \
KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_UP,   KC_NO,   RGB_TOG, RGB_VAI,               RGB_HUI, RGB_SAI, KC_INS,  RESET,   KC_PSCR, KC_SLCK,  KC_PAUS, KC_BSLS,           KC_SLCK, \
KC_TRNS, KC_TRNS,   KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,RGB_MOD, RGB_VAD,               RGB_HUD, RGB_SAD, KC_NO,   KC_NO,   KC_F14,  KC_F15,   KC_INS,                     KC_HOME, \
KC_TRNS, KC_TRNS,   KC_LSFT, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   BL_TOGG,               KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,                      KC_RSFT, RGB_MOD,  KC_END, \
KC_TRNS, KC_TRNS,   KC_LCTL, KC_LGUI, TD(ALT_OSL1),     RESET, RESET,                   RESET,            KC_TRNS, KC_RCTL, KC_TRNS,                    KC_HOME, BL_STEP,  KC_END \
  )};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(1); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}
