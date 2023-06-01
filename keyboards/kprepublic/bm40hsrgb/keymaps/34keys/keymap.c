// Copyright 2021 Taeyoon Kim (@partrita)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_korean.h"

enum layers {
  _Base,
  _Navi,
  _Numb,
  _Func,
};

// Left-hand home row mods - Base Layer
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)
#define HOME_J RSFT_T(KC_J)
#define HOME_K LCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_QU LGUI_T(KC_QUOT)

// layer keys
#define Lay_SPC LT(_Func,KC_SPC)
#define NAVI MO(_Navi)
#define NUMB MO(_Numb)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_Base] = LAYOUT_planck_mit(
        KC_Q,        KC_W,      KC_E,           KC_R,          KC_T,    KC_NO, KC_NO,       KC_Y,       KC_U,      KC_I,      KC_O,         KC_P,
      HOME_A,      HOME_S,    HOME_D,         HOME_F,          KC_G,    KC_NO, KC_NO,       KC_H,     HOME_J,    HOME_K,    HOME_L,      HOME_QU,
        KC_Z,        KC_X,      KC_C,           KC_V,          KC_B,    KC_NO, KC_NO,       KC_N,       KC_M,   KC_COMM,    KC_DOT,      KC_SLSH,
       KC_NO,       KC_NO,     KC_NO,           NAVI,       Lay_SPC,        KC_NO,       KC_BSPC,       NUMB,     KC_NO,     KC_NO,        KC_NO
      ),
  [_Navi] = LAYOUT_planck_mit(
      KC_WH_L,    KC_WH_D,   KC_WH_U,        KC_WH_R,        KC_ESC,    KC_NO, KC_NO,       KC_DEL,   KC_HOME,  KC_PGDN,   KC_PGUP,      KC_END,
      KC_LSFT,     HOME_S,    HOME_D,         HOME_F,        KC_TAB,    KC_NO, KC_NO,       KC_ENT,    KC_RSFT,   HOME_K,    HOME_L,     HOME_QU,
      KC_MS_L,    KC_MS_D,   KC_MS_U,        KC_MS_R,       KC_BTN1,    KC_NO, KC_NO,      KC_BTN2,   KC_LEFT,  KC_DOWN,     KC_UP,     KC_RGHT,
        KC_NO,      KC_NO,     KC_NO,          KC_NO,       Lay_SPC,        KC_NO,         KC_BSPC,     KC_NO,    KC_NO,     KC_NO,       KC_NO
      ),
  [_Numb] = LAYOUT_planck_mit(
      KC_LBRC,        KC_7,     KC_8,          KC_9,        KC_RBRC,    KC_NO, KC_NO,      KC_DEL,      KC_NO,     KC_NO,     KC_NO,       KC_NO,
      KC_SCLN,        KC_4,     KC_5,          KC_6,         KC_EQL,    KC_NO, KC_NO,      KC_ENT,     KC_RSFT,    HOME_K,    HOME_L,     HOME_QU,
       KC_GRV,        KC_1,     KC_2,          KC_3,        KC_BSLS,    KC_NO, KC_NO,       KC_NO,      KC_NO,     KC_NO,   KR_HAEN,       KC_NO,
        KC_NO,       KC_NO,     KC_NO,         KC_0,        KC_MINS,        KC_NO,        KC_BSPC,      KC_NO,     KC_NO,     KC_NO,       KC_NO
      ),
  [_Func] = LAYOUT_planck_mit(
      KC_F12,     KC_F7,     KC_F8,           KC_F9,       KC_PSCR,    KC_NO, KC_NO,        QK_BOOT,    KC_NO,     KC_NO,     KC_NO,     KC_NO,
      KC_F11,     KC_F4,     KC_F5,           KC_F6,       KC_SCRL,    KC_NO, KC_NO,      KC_CAPS,     KC_RSFT,    HOME_K,    HOME_L,   HOME_QU,
      KC_F10,     KC_F1,     KC_F2,           KC_F3,       KC_PAUS,    KC_NO, KC_NO,       KC_INS,      KC_NO,     KC_NO,   KR_HAEN,     KC_NO,
      KC_NO,       KC_NO,     KC_NO,          KC_NO,       Lay_SPC,         KC_NO,        KC_BSPC,      KC_NO,     KC_NO,     KC_NO,     KC_NO
      ),
};


// color by layer
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _Navi:
            rgblight_mode_noeeprom(RGB_MATRIX_RAINBOW_BEACON);
            break;
        case _Numb:
            rgblight_mode_noeeprom(RGB_MATRIX_HUE_PENDULUM);
            break;
        case _Func:
            rgblight_mode_noeeprom(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
            break;
        default:
            rgblight_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_WIDE);
    }
    return state;
}

// COMBO key for HOME ROW modifier
// modify `rules.mk` file
// by adding # COMBO_ENABLE = yes

enum combos {
  SFT_HAN,
};

const uint16_t PROGMEM sft_han_combo[] = {LSFT_T(KC_F), LT(_Func,KC_SPC), COMBO_END};

combo_t key_combos[] = {
  [SFT_HAN] = COMBO(sft_han_combo, KC_LNG1),
};
