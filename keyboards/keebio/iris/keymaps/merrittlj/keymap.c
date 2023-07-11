// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _SHIFT 1
#define _SYMBOL 2
#define _FUNCTION 3
#define _ADDITIONAL 4

#define KC_LBRACE S(KC_LBRC)
#define KC_RBRACE S(KC_RBRC)
#define KC_LESSTHAN S(KC_COMMA)
#define KC_MORETHAN S(KC_DOT)
// #define KC_UNDERSCORE S(KC_MINUS)
#define KC_PLUS S(KC_EQUAL)
// #define KC_PIPE S(KC_BSLS)
#define KC_DQUOTE S(KC_QUOTE)
// #define KC_COLON S(KC_SCLN)
#define KC_QMARK S(KC_SLSH)
// #define KC_TILDE S(KC_GRAVE)
#define KC_BANG S(KC_1)
#define KC_AT S(KC_2)
#define KC_HASH S(KC_3)
// #define KC_DOLLAR S(KC_4)
#define KC_PCNT S(KC_5)
#define KC_AHEAD S(KC_6)
#define KC_AND S(KC_7)
// #define KC_ASTERISK S(KC_8)
#define KC_LPAREN S(KC_9)
#define KC_RPAREN S(KC_0)

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  SHIFT,
  SYMBOL,
  FUNCTION,
  ADDITIONAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_PGUP, KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                               KC_0,    KC_2,    KC_4,    KC_6,    KC_8,    DM_PLY2,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_UP,   KC_LGUI, KC_LCTL, KC_RALT, KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    DM_REC2,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PGDN, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    DM_PLY1,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DOWN, KC_ESC,  KC_Q,    KC_J,    KC_K,    KC_X,    KC_SPC,           MO(_SYMBOL),KC_B, KC_M,    KC_W,    KC_V,    KC_Z,    DM_REC1,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TAB,  KC_ENT,  KC_BSPC,                   LM(_SHIFT, MOD_LSFT),MO(_FUNCTION),MO(_ADDITIONAL)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SHIFT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX,          XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, XXXXXXX, KC_TRNS,                   XXXXXXX, XXXXXXX, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYMBOL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_ASTERISK,KC_PLUS,KC_MINUS,KC_UNDERSCORE,KC_EQUAL,                    KC_LBRC, KC_RBRC, KC_LESSTHAN,KC_MORETHAN,KC_PIPE,KC_AHEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_SCLN, KC_COMMA,KC_DOT,  KC_DQUOTE,KC_QUOTE,                          KC_LBRACE,KC_RBRACE,KC_LPAREN,KC_RPAREN,KC_SLSH,KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_HASH, KC_BANG, KC_AND,  KC_COLON,KC_QMARK,XXXXXXX,          XXXXXXX, KC_GRAVE,KC_TILDE,KC_AT,   KC_DOLLAR,KC_PCNT,XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FUNCTION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, KC_F7,   KC_F5,   KC_F3,   KC_1,    KC_F9,                              KC_F10,  KC_F2,   KC_F4,   KC_F6,   KC_F8,   XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, QK_REP,  QK_AREP, QK_LOCK, KC_BTN4, KC_BTN5,                            KC_SCRL, KC_HOME, KC_END,  QK_BOOT, KC_PWR,  XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, TT(_SHIFT),KC_LEFT,KC_RIGHT,KC_WBAK,KC_WFWD,                            KC_INS,  KC_DEL,  KC_VOLU, KC_VOLD, KC_MUTE, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADDITIONAL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X,                            RGB_M_G, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,                            RGB_VAI, RGB_VAD, RGB_M_P, RGB_M_B, RGB_M_T, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DVORAK:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
        }
        return false;
        break;
    case SHIFT:
        if (record->event.pressed) {
            layer_on(_SHIFT);
        } else {
            layer_off(_SHIFT);
        }
        return false;
        break;
    case SYMBOL:
        if (record->event.pressed) {
            layer_on(_SYMBOL);
        } else {
            layer_off(_SYMBOL);
        }
        return false;
        break;
    case FUNCTION:
        if (record->event.pressed) {
            layer_on(_FUNCTION);
        } else {
            layer_off(_FUNCTION);
        }
        return false;
        break;
    case ADDITIONAL:
        if (record->event.pressed) {
            layer_on(_ADDITIONAL);
        } else {
            layer_off(_ADDITIONAL);
        }
        return false;
        break;
    }
    return true;
}
