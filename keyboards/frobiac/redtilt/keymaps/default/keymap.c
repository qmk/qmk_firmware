// Copyright 2023 @frobiac
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keymap_german.h"

enum layer_number {
    _ADNW = 0,
    _QWERTZ,
    _NAVNUM,
    _SYMBOL,
    _FUNC,
    _MOUSE,
};

#define CTL_TAB LCTL_T(KC_TAB)
#define ALT_SPC LALT_T(KC_SPC)
#define NAV_ESC LT(_NAVNUM, KC_ESC)
#define SFT_BSP LSFT_T(KC_BSPC)
#define SYM_ENT LT(_SYMBOL, KC_ENT)
#define MOUSE_X LT(_MOUSE, KC_X)
#define MOUSE_Y LT(_MOUSE, KC_Y)
#define RSFT__Z RSFT_T(DE_Z)
#define RSFT_SL RSFT_T(KC_SLSH)

/*
 *     ┌───┬───┐   ┌───┬───┬───┐    ┌───┬───┬───┐   ┌───┬───┐
 *     │   │MOU├───┤ Q │ . │ J │    │ P │ C │ L ├───┤Fx │   │
 *     ├───┼───┤ U ├───┼───┼───┤    ├─[TP]──┼───┤ M ├───┼───┤
 *     │   │ K ├───┤ E │ A │ O │    │ D │ T │ R ├───┤ F │   │
 *     ├───┼───┤ I ├───┼───┼───┤    ├───┼───┼───┤ N ├───┼───┤
 *     │   │ H ├───┤ - │ ; │ / │    │ D │ G │ W ├───┤ S │   │
 *     ├───┼───┤ Y ├───┼───┼───┤    ├───┼───┼───┤ V ├───┼───┤
 *     │   │ X ├───┤   │Tab│Spc│    │Esc│Bsp│Ret├───┤ Z │Tab│
 *     └───┴───┘   └───┴───┴───┘    └───┴───┴───┘   └───┴───┘
 *
 */

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ADNW] = LAYOUT(
      XXXXXXX, KC_K,    KC_U,    KC_Q,    KC_DOT,  KC_J,            KC_P,    KC_C,    KC_L,    KC_M,    KC_F,    XXXXXXX,
      XXXXXXX, KC_H,    KC_I,    KC_E,    KC_A,    KC_O,            KC_D,    KC_T,    KC_R,    KC_N,    KC_S,    XXXXXXX,
      XXXXXXX, MOUSE_X, DE_Y,    DE_MINS, KC_COMM, DE_SLSH,         KC_B,    KC_G,    KC_W,    KC_V,    RSFT__Z, XXXXXXX,
      XXXXXXX, XXXXXXX,          KC_LGUI, CTL_TAB, ALT_SPC,         NAV_ESC, SFT_BSP, SYM_ENT,          MO(_FUNC), XXXXXXX
  ),

  [_QWERTZ] = LAYOUT(
      XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
      XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, XXXXXXX,
      XXXXXXX, MOUSE_Y, KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  RSFT_SL, XXXXXXX,
      XXXXXXX, XXXXXXX,          KC_LGUI, CTL_TAB, ALT_SPC,         NAV_ESC, SFT_BSP, SYM_ENT,          MO(_FUNC),XXXXXXX
  ),

  [_SYMBOL] = LAYOUT(
      XXXXXXX, DE_AT,   DE_DEG,  DE_LBRC, DE_RBRC, DE_HASH,         DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, XXXXXXX,
      XXXXXXX, DE_BSLS, DE_EURO, DE_LCBR, DE_RCBR, DE_ASTR,         DE_QUES, DE_LPRN, DE_RPRN, DE_PLUS, KC_ENT,  XXXXXXX,
      XXXXXXX, XXXXXXX, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV,          DE_CIRC, DE_PERC, DE_DQUO, DE_QUOT, XXXXXXX, XXXXXXX,
      XXXXXXX, _______,          _______, _______, _______,         _______, _______, _______,          _______, XXXXXXX
  ),

  [_NAVNUM] = LAYOUT(
      XXXXXXX, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,         DE_SS,   KC_7,    KC_8,    KC_9,    DE_ADIA, XXXXXXX,
      XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,          KC_DOT,  KC_4,    KC_5,    KC_6,    DE_ODIA, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX,         KC_0,    KC_1,    KC_2,    KC_3,    DE_UDIA, XXXXXXX,
      XXXXXXX, _______,          _______, _______, _______,         _______, _______, _______,          _______, XXXXXXX
  ),

  [_FUNC] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(_QWERTZ),DF(_ADNW),    XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
      XXXXXXX, DM_REC1, DM_RSTP, DM_PLY1, XXXXXXX, QK_RBT,          XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,         XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  XXXXXXX,
      XXXXXXX, _______,          _______, _______, _______,         _______, _______, _______,          _______, XXXXXXX
  ),

  [_MOUSE] = LAYOUT(
      XXXXXXX, KC_WH_L, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,         KC_ACL0, XXXXXXX, KC_BTN3, XXXXXXX, KC_BTN5, XXXXXXX,
      XXXXXXX, KC_WH_R, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,         KC_ACL1, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN4, XXXXXXX,
      XXXXXXX, MOUSE_X, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_D,         KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, _______,          _______, _______, _______,         _______, _______, _______,          _______, XXXXXXX
  ),

};

// clang-format on
