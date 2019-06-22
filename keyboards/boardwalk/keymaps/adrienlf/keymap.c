#include QMK_KEYBOARD_H

#include "open_close_parenthese.c"
#include "open_close_parenthese_mods.c"
#include "sendstring_french.h"
extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _REVERSE 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,

  MAIL1,
  MAIL2,
  MAKE,
  SUPER,
  CODE,
  REV

};
enum {
  ARO = 0,
  WLESS = 1,


};

#define REV TT(_REVERSE)


qk_tap_dance_action_t tap_dance_actions[] = {

  [ARO]  = ACTION_TAP_DANCE_DOUBLE(FR_A, LCA(KC_0)),
  [WLESS]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, FR_LESS),
//   [OPEN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,open_finished, open_reset),
//  [CLOSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,close_finished, close_reset),
  [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_a_finished, td_a_reset),
  [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_e_finished, td_e_reset),
[SHIFT_PAR_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shift_o_finished, shift_o_reset),
[CTRL_BRACK_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctrl_o_o_finished, ctrl_o_o_reset),
[ALT_CURL_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_o_finished, alt_o_reset),
[SHIFT_PAR_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shift_c_finished, shift_c_reset),
[CTRL_BRACK_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctrl_c_c_finished, ctrl_c_c_reset),
[ALT_CURL_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_c_finished, alt_c_reset)
// Other declarations would go here, separated by commas, if you have KCeZ
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty

 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |  )     | =      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | A      | Z      | E      | R      | T      | Y      | U      | I      | O      | P      | ^      | $      | ____      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | Q      | S      | D      | F      | G      | H      | J      | K      | L      | M      | ù      | *      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | W      | X      | C      | V      | B      | N      | ?      | ,      | ;      | :      | UP     | !      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | ALT    | SUPER  | CODE   | LOWER  |      SPACE      | RAISE  | ALTGR  | RIGHT  | DOWN   | UP     | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */


[_QWERTY] = LAYOUT_ortho_mit( \
  KC_ESC,          KC_1,    KC_2,           KC_3,         KC_4,    KC_5,          KC_6,        KC_7,         KC_8,             KC_9,             KC_0,        KC_MINS,          KC_EQL,     KC_BSPC, \
  KC_TAB,          TD(TD_A),KC_W,           KC_E,         KC_R,    KC_T,          KC_Y,        KC_U,         KC_I,             KC_O,             KC_P,        KC_LBRC,          KC_RBRC,    KC_HOME, \
  REV,             KC_A,    KC_S,           KC_D,         KC_F,    KC_G,          KC_H,        KC_J,         KC_K,             KC_L,             KC_SCLN,     KC_QUOT,          KC_BSLS,    KC_ENT,    \
  TD(SHIFT_PAR_O), KC_Z,    KC_X,           KC_C,         KC_V,    KC_B,          KC_N,        KC_M,         KC_COMM,          KC_DOT,           KC_SLSH,     KC_UP,            FR_LESS,    TD(SHIFT_PAR_C),\
  TD(CTRL_BRACK_O),KC_LGUI, TD(ALT_CURL_O), SUPER,        CODE,    LOWER,             KC_SPC,                  RAISE,            TD(ALT_CURL_C),   KC_LEFT,     KC_DOWN,          KC_RGHT,    TD(CTRL_BRACK_C)  \
 ),
[_LOWER] = LAYOUT_ortho_mit(\
    KC_ESC,        KC_F1,   KC_F2,          KC_F3,        KC_F4,   KC_F5,         KC_F6,       KC_F7,        KC_F8,            KC_F9,            KC_F10,      KC_F11,           KC_F12,     KC_MPLY, \
    MAIL1,         _______, KC_UP,          TD(TD_E),     _______, _______,       KC_KP_MINUS, KC_KP_7,      KC_KP_8,          KC_KP_9,          KC_KP_DOT,   KC_KP_SLASH,      _______,    KC_MNXT, \
    MAIL2,         KC_LEFT, KC_DOWN,        KC_RGHT,      _______, _______,       KC_KP_PLUS,  KC_KP_4,      KC_KP_5,          KC_KP_6,          KC_KP_EQUAL, _______,          _______,    KC_MPRV, \
    KC_LSHIFT,     FR_LESS, _______,        _______,      _______, _______,       KC_KP_0,     KC_KP_1,      KC_KP_2,          KC_KP_3,          KC_KP_COMMA, _______,          _______,    KC_PGUP, \
    KC_LCTL,       KC_LGUI, KC_LALT,        LOWER,        KC_SPC,  _______,            _______,              _______,          _______,          _______,     _______,          _______,    KC_PGDN
  ),

[_REVERSE] = LAYOUT_ortho_mit(\
    KC_ESC,        KC_F7,   KC_F8,         KC_F9,         KC_F10,  KC_F11,        KC_F12,      KC_PSCREEN,   KC_F8,            KC_F9,            KC_F10,      KC_F11,           KC_F12,     KC_BSPC,  \
    KC_TAB,        KC_Y,    KC_U,          KC_I,          KC_O,    KC_P,          KC_INSERT,   KC_HOME,      KC_PGUP,          _______,          _______,     _______,          _______,    _______, \
    TO(_QWERTY),   KC_H,    KC_J,          KC_K,          KC_L,    KC_SCLN,       KC_DEL,      KC_END,       KC_PGDN,          _______,          _______,     _______,          _______,    _______, \
    KC_LSFT,       KC_N,    KC_M,          KC_COMM,       KC_DOT,  KC_SLSH,       _______,     _______,      _______,          _______,          _______,     _______,          _______,    _______, \
    KC_LCTL,       KC_LGUI, KC_LALT,       LOWER,         KC_SPC,  _______,           _______,               _______,          _______,          _______,     _______,          _______,    _______
  )


};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
       case MAIL1:
     if (record->event.pressed) {
        SEND_STRING("sydneywriter@gmail.com" );

      } else {
        // when keycode QMKURL is released
      }
      break;

      case MAIL2:
     if (record->event.pressed) {
        SEND_STRING("adrienlefalher.pro@gmail.com");

      } else {
        // when keycode QMKURL is released
      }
      break;

     case MAKE:
     if (record->event.pressed) {
        SEND_STRING("make boardwalk:adrienlf:dfu");

      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}
