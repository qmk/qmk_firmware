/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _ARROWS 1
#define _SYMBOLS 2
#define _NUMFUN 3
#define _NUMPAD 4
#define _MODIFIED 5

// // Tap Dance declarations
// enum {
//     TD_Q_ESC,
// };

// // Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
// };

// Add tap dance item in place of a key code
// TD(TD_Q_ESC)

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    TD_Q_ESC,
    SOME_OTHER_DANCE
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void q_finished(qk_tap_dance_state_t *state, void *user_data);
void q_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                         ,-----------------------------------------------------.
       _______,  TD(TD_Q_ESC),    KC_W,    KC_E,    KC_R,    KC_T,                                                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  _______,
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      _______,    LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LT(_NUMPAD, KC_F), KC_G,                                    KC_H,    RGUI_T(KC_J), RALT_T(KC_K), RSFT_T(KC_L), RCTL_T(KC_SCLN), _______,
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                              KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                                |--------+--------+--------+--------+--------+--------+--------|
                                          LT(_NUMFUN, KC_DELETE), LT(_MODIFIED, KC_TAB), LT(_ARROWS, KC_QUOT),          LT(_SYMBOLS, KC_SPC),  LT(_NUMPAD, KC_ENT), LT(_NUMFUN, KC_BSPC)
                                      //`--------------------------'                                                `--------------------------'

  ),

  [_ARROWS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                                            KC_EQUAL, KC_HOME, KC_UP, KC_END, KC_LCBR, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL,    KC_LSFT,   KC_LALT,   KC_LGUI, _______,                                                     KC_RABK, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RCBR, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_BSLS, _______, KC_LABK, KC_RABK, KC_DELETE,                                                          KC_BSPC, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRACKET, KC_RBRACKET, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, KC_GRAVE,    KC_PERCENT,  KC_PIPE,   KC_AMPR, KC_EQUAL,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_EXCLAIM,    KC_AT,  KC_HASH,   KC_DOLLAR, KC_RABK,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_CIRC,    KC_ASTR,  KC_UNDERSCORE,   KC_PLUS, KC_MINUS,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_CAPSLOCK, KC_DOUBLE_QUOTE,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_NUMFUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5,                                                            KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_1,  KC_2, KC_3, KC_4, KC_5,                                                            KC_6, KC_7, KC_8, KC_9, KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_VOLD, KC_VOLU, _______,                                                            _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, RESET, _______, _______, _______, _______,                                                            _______, KC_7, KC_8, KC_9, SGUI(KC_S), _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC1, DM_RSTP, DM_PLY1, _______,                                                            _______, KC_4, KC_5, KC_6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC2, DM_RSTP, DM_PLY2, _______,                                                            _______, KC_1, KC_2, KC_3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_ENT,                                          KC_MINUS, KC_KP_0, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_MODIFIED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, LCTL(KC_R), _______,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, LCTL(KC_A),  LCTL(KC_S),   LCTL(KC_D), LCTL(KC_F), _______,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, LCTL(KC_Z),    LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),  LCTL(KC_B),                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Do work, son"), false);
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
         case LT(_ARROWS, KC_ENT):
         case LCTL_T(KC_A):
         case LSFT_T(KC_S):
         case LALT_T(KC_D):
         case LT(_NUMPAD, KC_F):
         case RGUI_T(KC_J):
         case RALT_T(KC_K):
         case RSFT_T(KC_L):
         case RCTL_T(KC_SCLN):
            return true;
         default:
            return false;
      }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap qtap_state = {
    .is_press_action = true,
    .state = 0
};

void q_finished(qk_tap_dance_state_t *state, void *user_data) {
    qtap_state.state = cur_dance(state);
    switch (qtap_state.state) {
        case SINGLE_TAP: register_code(KC_Q); break;
        case SINGLE_HOLD: register_code(KC_ESC); break;
        case DOUBLE_TAP: SEND_STRING(SS_TAP(X_ESC)); SEND_STRING(SS_TAP(X_ESC)); break;
        // case DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case DOUBLE_SINGLE_TAP: tap_code(KC_Q); register_code(KC_Q);
    }
}

void q_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Q); break;
        case SINGLE_HOLD: unregister_code(KC_ESC); break;
        // case DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case DOUBLE_HOLD: unregister_code(KC_LALT);
        // case DOUBLE_SINGLE_TAP: unregister_code(KC_Q);
    }
    qtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_ESC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, q_finished, q_reset, 450)
};