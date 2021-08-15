#include QMK_KEYBOARD_H
#include "keymap_italian.h"

enum layers {
    _MAIN,
    _SHIFT,
    _ACCENT,
    _NAVIGATE,
    _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT_all(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_MINS, IT_EQL,  KC_DEL, KC_ESC,    KC_INS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    IT_LBRC, IT_RBRC, KC_BSPC,            KC_VOLD,
      MT(MOD_LCTL, KC_TAB),     KC_A,    KC_S,    LT(_NAVIGATE, KC_D), LT(_SHIFT, KC_F),    KC_G,    KC_H, LT(_SHIFT, KC_J),    LT(_NAVIGATE, KC_K),    KC_L,    IT_SCLN, IT_QUOT, KC_SFTENT, KC_VOLU,
      LT(_SHIFT, KC_DEL),        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    IT_COMM, IT_DOT,  IT_SLSH, MO(_SHIFT), KC_UP,  KC_MUTE,
      KC_LCTL, KC_LALT, KC_LGUI,          LT(_ACCENT, KC_SPC),                                       LT(_SERVICE, IT_LESS), KC_LEFT,   KC_DOWN, KC_RGHT
  ),

  [_SHIFT] = LAYOUT_all(
      KC_ESC,     IT_EXLM,    IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, IT_UNDS, IT_PLUS, S(KC_DEL), S(KC_DEL), S(KC_INS),
      S(KC_TAB),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), IT_LCBR, IT_RCBR,    S(KC_BSPC),    S(KC_END),
      S(KC_CAPS), S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_COLN, IT_DQOT,             S(KC_ENT),  S(KC_PGUP),
      KC_LSFT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL, IT_PIPE, IT_QST,  KC_RSFT,          S(KC_UP),   S(KC_PGDN),
      S(KC_LCTL), S(KC_LALT), S(KC_LGUI),                         LT(_ACCENT, KC_SPC),                       IT_MORE,   S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
  ),

  [_ACCENT] = LAYOUT_all(
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, IT_EURO, _______, IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______, _______, _______, _______,
      _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_NAVIGATE] = LAYOUT_all(
      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, XXXXXXX, LCTL(KC_ENT), XXXXXXX,
      KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  KC_END, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, LALT(KC_BSPC), XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_SERVICE] = LAYOUT_all(
      RESET,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_HOME,
      _______, EF_INC,   H1_INC,  H2_INC,  S1_INC,  S2_INC, BR_INC, ES_INC, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_MUTE,
      _______, EF_DEC,   H1_DEC,  H2_DEC,  S1_DEC,  S2_DEC, BR_DEC, ES_DEC, _______, _______, _______, _______,          _______, KC_VOLU,
      KC_LSFT, RGB_TOG,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT,          KC_PGUP, KC_VOLD,
      KC_LCTL, KC_LALT,  KC_LGUI,                            _______,                                     _______, KC_HOME, KC_PGDN, KC_END
  ),

};
