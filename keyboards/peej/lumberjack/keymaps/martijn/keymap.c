/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

enum custom_keycodes {
  HEADP = SAFE_RANGE,
  C_HOME,
};

enum unicode_names {
    THUMB,
};

const uint32_t PROGMEM unicode_map[] = {
    [THUMB]  = 0x1F44D, // 🐍
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------.
 * | esc   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | bksp  |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * | tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | del   |
 * |-------+------+------+------+------+-------------+------+------+------+------+-------|
 * | poker |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | enter |
 * |-------+------+------+------+------+------|------+------+------+------+------+-------|
 * | shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | shift |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * | ctrl  |  os  | mod3  | alt  |  program   |    space    | os   | duim | prnt | ctrl  |
 * `-------------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_ortho_5x12( \
  KC_ESC,   KC_1,    KC_2,       KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_BSLS, \
  POKER,    KC_A,    KC_S,       KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN, KC_ENT, \
  SC_LSPO,  KC_Z,    KC_X,       KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH, SC_RSPC, \
  KC_LCTL,  EXTR,    KC_LGUI,    KC_LALT, PROG,    PROG,    KC_SPC,  KC_SPC,  KC_RALT, UM(THUMB),  KC_PSCR, KC_LCTL
),


[_POKER] = LAYOUT_ortho_5x12( \
  CW_TOGG, _______,          _______, _______, _______,  _______,   _______,   _______,   _______,   PUSH_2_TALK, _______,   KC_DEL, \
  _______, KC_MPRV,          KC_MPLY, KC_MNXT, KC_F5,    N_TAB,     KC_PAUSE,  T_PREV,    KC_UP,     T_NEXT,      KC_ENT,    W_QUIT, \
  _______, TD(TAP_SHFT),     KC_VOLD, KC_VOLU, KC_MUTE,  _______,   KC_HOME,   KC_LEFT,   KC_DOWN,   KC_RGHT,     KC_BSPC,   KC_DEL, \
  _______, _______,          _______, COPY,    PASTE,    _______,   KC_END,    _______,   E_BACK,    E_FORWARD,   ALL,       C_HOME, \
  _______, _______,          _______, _______, _______,  _______,   KC_SPC,    _______,    _______,  _______,     _______,   _______
),

[_PROGRAM] = LAYOUT_ortho_5x12( \
  KC_F12,    KC_F1,   KC_F2,   KC_F3,              KC_F4,             KC_F5,    KC_F6,     KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11, \
  SWITCH,    KC_GRV,  KC_DLR,  KC_TILD,            KC_ASTERISK,       KC_CIRC,  _______,   _______,  KC_LBRC,  KC_RBRC, _______,  _______, \
  _______,   KC_PLUS, KC_UNDS, KC_MINS,            KC_EQL,            OSDOWN,   OSUP,      KC_DQUO,  KC_LCBR,  KC_RCBR, KC_QUOT,  _______, \
  KC_LSFT,   _______, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,  _______,  _______,   _______,  _______,  _______, _______,  _______, \
  _______,   _______, _______, _______,            _______,           _______,  _______,   _______,  _______,  _______, _______,  _______
),

[_SELECT] = LAYOUT_ortho_5x12( \
  _______,   _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______, \
  _______,   _______,  KC_W,      _______, _______, KC_T,    _______, _______, KC_UP,    _______,  _______, _______, \
  _______,   _______,  _______,   _______, KC_F,    _______, _______, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_BSPC, KC_ENT, \
  _______,   _______,  _______,   KC_C,    KC_V,    _______, _______, _______, _______,  _______,  _______, _______, \
  _______,   _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______
),

[_EXTRA] = LAYOUT_ortho_5x12( \
  _______,   QK_BOOT,        EE_CLR,       QK_REBOOT,        _______,   _______,   _______,   KC_MINS, KC_EQL,  _______, _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   KC_7,    KC_8,    KC_9,    _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   HEADP,     KC_4,    KC_5,    KC_6,    KC_DEL,  _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   KC_1,    KC_2,    KC_3,    _______, _______, \
  _______,   _______,        _______,      _______,          _______,   _______,   _______,   _______, KC_0,    KC_0,    KC_0,    _______
)

};

void keyboard_pre_init_user() {
    writePin(LED1, true);
    writePin(LED2, true);
}

void keyboard_post_init_user() {
    writePin(LED1, false);
    writePin(LED2, false);
}

void caps_word_set_user(bool active) {
    if (active) {
        writePin(LED2, true);
    } else {
        writePin(LED2, false);
    }
}

#define IDLE_TIMEOUT_MS 800

static uint32_t idle_callback(uint32_t trigger_time, void* cb_arg) {
  // reset wpm counter
  if (is_caps_word_on() == false) {
    writePin(LED2, false);
  }
  return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  writePin(LED1, record->event.pressed);

  if (is_caps_word_on() == false) {
    writePin(LED2, get_current_wpm() > 90);
  }

  // On every key event, start or extend the deferred execution to call
  // `idle_callback()` after IDLE_TIMEOUT_MS. (resetting wpm counter)
  static deferred_token idle_token = INVALID_DEFERRED_TOKEN;
  if (!extend_deferred_exec(idle_token, IDLE_TIMEOUT_MS)) {
    idle_token = defer_exec(IDLE_TIMEOUT_MS, idle_callback, NULL);
  }

  switch (keycode) {
    case HEADP:
      if (record->event.pressed) {
        SEND_STRING("TODO");
      }
      break;

    case C_HOME:
      if (record->event.pressed) {
        SEND_STRING("~/");
      }
      break;
  }
  return true;
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

