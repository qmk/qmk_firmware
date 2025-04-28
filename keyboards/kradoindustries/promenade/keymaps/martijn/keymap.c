#include QMK_KEYBOARD_H

#define _BASE    0
#define _POKER   1
#define _PROGRAM 2
#define _SELECT  3
#define _EXTRA   4

#define PROG   MO(_PROGRAM)
#define POKER  MO(_POKER)
#define EXTR   MO(_EXTRA)

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance keycodes
enum td_keycodes {
    TAP_SHFT
};

// Generates a pseudorandom value in 0-255.
static uint8_t simple_rand(void) {
  static uint16_t random = 1;
  random *= UINT16_C(36563);
  return (uint8_t)(random >> 8);
}

enum custom_keycodes {
  C_HOME = SAFE_RANGE,
  EMOJI
};

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  switch (keycode) {
  case C_HOME:
    if (record -> event.pressed) {
      SEND_STRING("~/");
    }
    break;
  case EMOJI:
    if (record -> event.pressed) {
      static
      const char * emojis[] = {"🌞","👾", "💃", "🙌"};
      const int NUM_EMOJIS = sizeof(emojis) / sizeof( * emojis);

      // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
      uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

      // Don't pick the same emoji twice in a row.
      static uint8_t last_index = 0;
      if (index >= last_index) {
        ++index;
      }
      last_index = index;

      // Produce the emoji.
      send_unicode_string(emojis[index]);
    }
    break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,----------------------------------------------------------------------------------------------------.
 * | esc   |   1  |   2  |   3  |   4  |   5  |   -  |   -  |   6  |   7  |   8  |   9   |   0  | bksp  |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|------|-------|
 * | tab   |   Q  |   W  |   E  |   R  |   T  |   -  |   -  |   Y  |   U  |   I  |   O   |   P  | del   |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|------|-------|
 * | poker |   A  |   S  |   D  |   F  |   G  |   -  |   -  |   H  |   J  |   K  |   L   |   ;  | enter |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|------|-------|
 * | shift |   Z  |   X  |   C  |   V  |   B  |   -  |   -  |   N  |   M  |   ,  |   .   |   /  | shift |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|------|-------|
 * | ctrl  |  os  | mod3 | alt  |       program      |       space        | os   | duim  | prnt | ctrl  |
 * `-------------------------------------------------------------------------------------|------|-------'
 */

[_BASE] = LAYOUT_2x3u(
  KC_ESC,   KC_1,    KC_2,       KC_3,    KC_4,    KC_5,    UG_TOGG,   UG_NEXT,      KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,    UG_HUEU,   UG_HUED,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS,
  POKER,    KC_A,    KC_S,       KC_D,    KC_F,    KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_ENT,
  SC_LSPO,  KC_Z,    KC_X,       KC_C,    KC_V,    KC_B,    LOCK,      EXTR,         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, SC_RSPC,
  KC_LCTL,  EXTR,    KC_LGUI,    KC_LALT,                   PROG,      KC_SPC,                         KC_RALT, EMOJI,  KC_PSCR, KC_LALT
),


[_POKER] = LAYOUT_2x3u(
  CW_TOGG, _______,      _______, _______, _______,  _______,   _______,  _______,   _______,   _______,   _______,   PUSH_2_TALK, _______,   KC_DEL,
  _______, KC_MPRV,      KC_MPLY, KC_MNXT, KC_F5,    N_TAB,     _______,  _______,   KC_PAUSE,  T_PREV,    KC_UP,     T_NEXT,      KC_ENT,    W_QUIT,
  _______, TD(TAP_SHFT), KC_VOLD, KC_VOLU, KC_MUTE,  _______,                        KC_HOME,   KC_LEFT,   KC_DOWN,   KC_RGHT,     KC_BSPC,   KC_DEL,
  _______, _______,      _______, COPY,    PASTE,    _______,   _______,  _______,   KC_END,    _______,   _______,   _______,     ALL,       C_HOME,
  _______, _______,      _______, _______,                      _______,   KC_SPC,                         _______,   _______,   _______,     _______
),

[_PROGRAM] = LAYOUT_2x3u(
  KC_F12,    KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,    _______,   _______,  KC_F6,     KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
  SWITCH,    KC_GRV,  KC_DLR,  KC_TILD, KC_ASTERISK, TERMINAL, _______,   _______,  _______,   _______,  KC_LBRC,  KC_RBRC, _______,  _______,
  _______,   KC_PLUS, KC_UNDS, KC_MINS, KC_EQL,      OSDOWN,                        OSUP,      KC_DQUO,  KC_LCBR,  KC_RCBR, KC_QUOT,  _______,
  KC_LSFT,   _______, _______, KC_BRID, KC_BRIU,     _______,  _______,  _______,   _______,   _______,  _______,  _______, _______,  _______,
  _______,   _______, _______, _______,                        KC_SPC,   _______,                        _______,  _______, _______,  _______
),

[_SELECT] = LAYOUT_2x3u(
  _______,   _______,  _______,   _______, _______, _______,     _______, _______,  _______, _______, _______,  _______,  _______, _______,
  _______,   _______,  KC_W,      _______, _______, KC_T,        _______, _______,  _______, _______, KC_UP,    _______,  _______, _______,
  _______,   _______,  _______,   _______, KC_F,    _______,                        _______, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_BSPC, KC_ENT,
  _______,   _______,  _______,   KC_C,    KC_V,    _______,     _______, _______,  _______, _______, _______,  _______,  _______, _______,
  _______,   _______,  _______,   _______,                       _______, _______,                    _______, _______,   _______, _______
),

[_EXTRA] = LAYOUT_2x3u(
  _______,   QK_BOOT, EE_CLR,  QK_REBOOT, _______,   _______,   _______,   _______, _______,   KC_MINS, KC_EQL,  _______, _______, D_SUGGEST,
  _______,   _______, _______, _______,   _______,   _______,   _______,   _______, _______,   KC_7,    KC_8,    KC_9,    _______, _______,
  _______,   BL_UP,   _______, _______,   _______,   _______,                       _______,   KC_4,    KC_5,    KC_6,    KC_DEL,  _______,
  _______,   _______, BL_DOWN, _______,   _______,   _______,   _______,   _______, _______,   KC_1,    KC_2,    KC_3,    _______, _______,
  _______,   _______, _______, _______,                         _______,   _______,                     KC_0,    KC_0,    KC_0,    _______
)
};

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}


// Handle the possible states for each tapdance keycode you define:
void tap_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    layer_on(_BASE);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LCTL);
            register_code16(KC_LSFT);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LCTL);
            register_code16(KC_LSFT);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            register_code16(KC_LCTL);
            break;
        default:
            break;
    }
}

void tap_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_BASE);
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LCTL);
            unregister_code16(KC_LSFT);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LCTL);
            unregister_code16(KC_LSFT);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LCTL);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TAP_SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_finished, tap_reset)
};
