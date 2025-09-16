// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    RGBRST = SAFE_RANGE,
};

#define KC_CTES CTL_T(KC_ESC)
#define KC_SFSP SFT_T(KC_SPC)
#define KC_ALBS ALT_T(KC_BSPC)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                      KC_H,   KC_J,   KC_K,   KC_L, KC_ENT,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                      KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_SPC,KC_LALT,KC_LGUI,  LOWER,KC_CTES,   KC_SFSP,  RAISE,KC_ALBS,KC_RCTL,KC_LGUI,XXXXXXX
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_TAB,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT, KC_ENT,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     KC_LCTL, KC_SPC,KC_LSFT,KC_LALT, KC_DEL,                   KC_BSPC,KC_HOME, KC_END,XXXXXXX,XXXXXXX,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
     KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,                   KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_TAB,KC_UNDS,KC_PLUS,KC_PIPE,KC_TILD,                   KC_COLN,KC_DQUO,  KC_GT,KC_LCBR,KC_RCBR,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     KC_LCTL,KC_MINS, KC_EQL,KC_BSLS, KC_GRV,                   KC_SCLN,KC_QUOT,  KC_LT,KC_LBRC,KC_RBRC,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_ADJUST] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                     KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_F11, KC_F12,  QK_BOOT,KC_PSCR, KC_INS,                   UG_TOGG,UG_HUEU,UG_SATU,UG_VALU,XXXXXXX,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   UG_NEXT,UG_HUED,UG_SATD,UG_VALD,RGBRST,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#endif
            break;
    }
    return true;
}
