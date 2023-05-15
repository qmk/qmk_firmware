// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  _ALPHA,
  _SYMBOL,
  _NUMBER,
  _NAVIGATION,
  LAYER_LENGTH
};


enum tapdances {
  TD_QESC,
  TD_SBKT,
  TD_CBKT,
  TD_PARN,
  TD_LTGT,
  TD_ATAB,
  TAPDANCE_LENGTH
};

enum combos {
  COMBO_NAVIGATION,
  COMBO_LENGTH
};


// begin tapdances
#define KC_QESC     TD(TD_QESC)
#define KC_SBKT     TD(TD_SBKT)
#define KC_CBKT     TD(TD_CBKT)
#define KC_PARN     TD(TD_PARN)
#define KC_LTGT     TD(TD_LTGT)
#define KC_ATAB     TD(TD_ATAB)

#define KC_GUIX     LGUI_T(KC_X)
#define KC_ALTC     LALT_T(KC_C)

// oneshots
#define KC_OSFT   OSM(MOD_LSFT)
#define KC_OALT   OSM(MOD_LALT)

// layer changing
#define KC_OSYM   OSL(_SYMBOL)
#define KC_ONUM   LT(_NUMBER, KC_BSPC)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_GUIX:
        case KC_ALTC:
            return TAPPING_TERM * 2;
        default:
            return TAPPING_TERM;
    }
}

// tapdances
tap_dance_action_t tap_dance_actions[] = {
    [TD_QESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_SBKT]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_CBKT]   = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_PARN]   = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_LTGT]   = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
    [TD_ATAB]   = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_TAB)
};
// end tapdances

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_navigation[] = { KC_OSYM, KC_ONUM, COMBO_END };
combo_t key_combos[] = {
  [COMBO_NAVIGATION]        = COMBO(combo_navigation, OSL(_NAVIGATION)),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  switch(index) {
    case COMBO_NAVIGATION: // extending the combo term here helps reduce sticky layers some more.
      return 250;
    default:
      return COMBO_TERM;
  }
}
// end combos


// begin layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x5_3(
    KC_QESC,    KC_W,       KC_E,       KC_R,       KC_T,             KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,
    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,             KC_H,       KC_J,       KC_K,       KC_L,       KC_QUOT,
    KC_Z,       KC_GUIX,    KC_ALTC,    KC_V,       KC_B,             KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,
                            KC_LCTL,    KC_OSYM,    KC_OSFT,          KC_SPC,     KC_ONUM,    KC_ENT
  ),
  [_SYMBOL] = LAYOUT_split_3x5_3(
    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,          KC_CIRC,     KC_AMPR,   KC_ASTR,    KC_PIPE,    KC_NO,
    KC_GRV,     KC_TILD,      KC_UNDS,    KC_EQL,     KC_NO,          KC_SBKT,     KC_CBKT,   KC_PARN,    KC_LTGT,  KC_BACKSLASH,
    KC_NO,      KC_NO,      KC_PLUS,    KC_MINS,    KC_NO,            KC_NO,       KC_NO,     KC_COLN,    KC_DOT,     KC_SCLN,
                             KC_LCTL,    KC_OSYM,    KC_OSFT,          KC_SPC,     KC_ONUM,    KC_ENT
  ),
  [_NUMBER] = LAYOUT_split_3x5_3(
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,             KC_6,       KC_7,       KC_8,       KC_9,       KC_0,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,            KC_NO,      KC_NO,      KC_NO,      KC_DOT,     KC_NO,
                            KC_LCTL,    KC_OSYM,    KC_OSFT,          KC_SPC,     KC_ONUM,    KC_ENT
  ),
  [_NAVIGATION] = LAYOUT_split_3x5_3(
    KC_NO,      KC_F2,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_HOME,    KC_UP,      KC_END,     KC_BSPC,
    KC_TAB,     KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_ENT,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_DEL,
                            KC_LCTL,    KC_OSYM,    KC_OSFT,        KC_SPC,     KC_ONUM,    KC_ENT 
  )
};



