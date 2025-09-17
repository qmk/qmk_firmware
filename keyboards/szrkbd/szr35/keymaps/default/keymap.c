// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// Based loosely on https://peterxjang.com/blog/designing-a-36-key-custom-keyboard-layout.html
// This is a good starting point for someone who is used to normal qwerty keyboards and wants to
// switch easily between the 36-key keyboard and a laptop keyboard. The goal is to minimize the
// learning curve by avoiding key relocation and maintaining our hard-earned muscle memory.

#include "keycodes.h"
#include "keymap_us.h"
#include QMK_KEYBOARD_H

enum layers {
    _LAYER_0,
    _LAYER_1,
    _LAYER_2,
    _LAYER_3,
};

#define LAYER0 MO(_LAYER_0)
#define LAYER1 MO(_LAYER_1)
#define LAYER2 MO(_LAYER_2)
#define LAYER3 MO(_LAYER_3)

#define Z_SFT   LSFT_T(KC_Z)
#define SLS_SFT RSFT_T(KC_SLSH)
#define BSL_SFT RSFT_T(KC_BSLS)
#define TAB_GUI LGUI_T(KC_TAB)
#define ESC_CTL LCTL_T(KC_ESC)

#define G_TAB G(KC_TAB)
#define C_ESC C(KC_ESC)

#define ENT_LY1 LT(LAYER1, KC_ENT)
#define BSP_LY2 LT(LAYER2, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LAYER_0] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    Z_SFT,   KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SFT,
                      KC_LALT, TAB_GUI, ESC_CTL,      KC_SPC,  ENT_LY1, BSP_LY2
  ),

  [_LAYER_1] = LAYOUT_split_3x5_3(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_GRV,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_LSFT, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,      KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, BSL_SFT,
                      XXXXXXX, G_TAB,   C_ESC,        XXXXXXX, XXXXXXX, LAYER3
  ),

  [_LAYER_2] = LAYOUT_split_3x5_3(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_F11,  KC_F12,  KC_MPRV, KC_MPLY, KC_MNXT,      MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_PSCR,
    KC_MUTE, KC_VOLU, KC_VOLD, MS_WHLD, MS_WHLU,      MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4, MS_BTN5,
                      MS_ACL0, MS_ACL1, MS_ACL2,      XXXXXXX, LAYER3,  XXXXXXX
  ),

  [_LAYER_3] = LAYOUT_split_3x5_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  )

};
