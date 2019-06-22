#include QMK_KEYBOARD_H
//#include "keymap_french.h"
#include "open_close_parenthese.c"
#include "open_close_parenthese_mods.c"

#include "sendstring_french.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MAIL1,
  MAIL2
};

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _REVERSE
};

enum {
  ARO = 0,
  WLESS = 1,


};

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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {

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

  }
  return true;
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define REV TT(_REVERSE)


uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (biton32(state)) {
    case _BASE:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(28, 255, 255);
        break;
    case _LOWER:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(338, 255, 255);
        break;
    case _RAISE:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(260, 255, 255);
        break;
    case _ADJUST:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(120, 0, 255);
        break;
     case _REVERSE:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(0, 255, 255);
        break;


    }


    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65(
    KC_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, \
    KC_TAB,  TD(TD_A),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,  KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
    REV,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END, \
    TD(SHIFT_PAR_O), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(SHIFT_PAR_C), KC_UP,   KC_PGDN, \
    TD(CTRL_BRACK_O), KC_LGUI, TD(ALT_CURL_O), LOWER,KC_SPC,                KC_SPC,TD(ALT_CURL_C),RAISE,KC_RGUI, TD(CTRL_BRACK_C), KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_LOWER] = LAYOUT_65(
    KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, KC_MPLY, \
    MAIL1, _______, KC_UP,   TD(TD_E), _______, _______, KC_KP_MINUS, KC_KP_7, KC_KP_8, KC_KP_9,    KC_KP_DOT, KC_KP_SLASH, _______, _______, KC_MNXT, \
    MAIL2, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_KP_PLUS, KC_KP_4, KC_KP_5, KC_KP_6,    KC_KP_EQUAL, _______, _______, KC_MPRV, \
    KC_LSHIFT, FR_LESS, _______, _______, _______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3,    KC_KP_COMMA, _______, KC_PGUP,_______, \
    KC_LCTL, KC_LGUI, KC_LALT, LOWER,KC_SPC,           _______, _______, _______, _______, _______, _______, KC_PGDN, _______
  ),
   [_RAISE] = LAYOUT_65(
    KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, KC_MPLY, \
    _______, _______, _______, KC_UP,   _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9,    _______, FR_SLSH, _______, _______,KC_MNXT, \
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6,    _______, _______, _______, KC_MPRV, \
    _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3,    _______, _______, _______, _______, \
    KC_TILD, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  ),
     [_ADJUST] = LAYOUT_65(
    KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, KC_ASTG, \
    RGB_TOG, RGB_MOD, KC_X,    KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ASUP, \
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, KC_ASDN, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_TILD, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  ),
     [_REVERSE] = LAYOUT_65(
    KC_ESC, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_PSCREEN,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_BSPC, _______, \
    KC_TAB,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,              KC_INSERT, KC_HOME, KC_PGUP, _______, _______, _______, _______, _______, _______, \
    TO(_BASE),KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,               KC_DEL, KC_END, KC_PGDN, _______, _______, _______, _______, _______, \
    KC_LSFT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_LCTL,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,                           _______, _______, _______, _______, _______, _______, _______, _______
  )

};
