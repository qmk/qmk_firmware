// Copyright 2022 Takeshi Noda (nodatk@gmail.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "twig50.h"

#define LAL_NCV  LALT_T(KC_LANG2)
#define RAL_CNV  RALT_T(KC_LANG1)
#define LGU_NCV  LGUI_T(KC_LANG2)
#define RGU_ENT  RGUI_T(KC_ENT)
#define RGU_IN8  RGUI_T(KC_INT8)

#define RSF_SCL  RSFT_T(KC_SCLN)
#define RCT_ESC  RCTL_T(KC_ESC)
#define RCT_IN7  RCTL_T(KC_INT7)

#define LT1_SPC  LT(1, KC_SPC)
#define LT2_F    LT(2, KC_F)
#define LT2_N    LT(2, KC_N)
#define LT3_BS   LT(3, KC_BSPC)
#define LT3_V    LT(3, KC_V)
#define LT3_QOT  LT(3, KC_QUOT)
#define TG4      TG(4)

#define SFT_1    RSFT(KC_1)
#define SFT_2    RSFT(KC_2)
#define SFT_3    RSFT(KC_3)
#define SFT_4    RSFT(KC_4)
#define SFT_5    RSFT(KC_5)
#define SFT_6    LSFT(KC_6)
#define SFT_7    LSFT(KC_7)
#define SFT_8    LSFT(KC_8)
#define SFT_9    LSFT(KC_9)
#define SFT_0    LSFT(KC_0)
#define SFT_LBR  LSFT(KC_LBRC)

#define OSM_LSF  OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Layer 0, Base layer
  LAYOUT_diag_4x14(
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_BSPC,
    KC_LCTL,          KC_A,    KC_S,    KC_D,    LT2_F,   KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    RSF_SCL, LT3_QOT, KC_ENT,
    KC_LSFT, TG4,     KC_Z,    KC_X,    KC_C,    LT3_V,   KC_B,         LT2_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_BTN1, KC_BTN2, KC_LALT,          LGU_NCV, LT1_SPC,               RCT_ESC, RGU_ENT, RAL_CNV, KC_INT1, KC_DEL,           MU_TOG
  ),

  // Layer 1, Space-modifiers: Basic keys
  LAYOUT_diag_4x14(
    RESET,            KC_EXEC, KC_HELP, KC_MENU, KC_SLCT, KC_STOP,      KC_BTN2, KC_INT1, KC_MINS, KC_EQL,  KC_INT3, SFT_LBR, KC_TRNS,
    KC_TRNS,          KC_AGIN, KC_FIND, KC_PGUP, KC_PGDN, KC_F19,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  SFT_7,   SFT_2,
    KC_TRNS, KC_TRNS, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_APP,       KC_BSPC, KC_DEL,  KC_RBRC, KC_BSLS, KC_HOME,          KC_END,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,               RCT_IN7, RGU_IN8, KC_TRNS, KC_INT2, KC_INT4,          MU_MOD
  ),

  // Layer 2, F,N-modifiers: Number keys and symbols
  LAYOUT_diag_4x14(
    KC_TRNS,          SFT_1,   SFT_2,   SFT_3,   SFT_4,   SFT_5,        SFT_6,   SFT_7,   SFT_8,   SFT_9,   KC_COMM, KC_DOT,  KC_QUOT,
    KC_TRNS,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SFT_1,   SFT_2,
    KC_TRNS, KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,         KC_BSPC, KC_MINS, SFT_4,   SFT_5,   KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_4,                  KC_5,    KC_TRNS, KC_TRNS, KC_INT5, KC_INT6,          KC_TRNS
  ),

  // Layer 3, V,:-modifiers: Functions and mouse keys
  LAYOUT_diag_4x14(
    KC_F1,            KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
    KC_MPLY,          KC_MRWD, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU,      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN3, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,       KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,           KC_F18,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_BTN2, KC_BTN1,               KC_WH_D, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS
  ),

  // Layer 4, Toggles: One handed mode
  LAYOUT_diag_4x14(
    KC_TRNS,          KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_LEFT, KC_DOWN, KC_RGHT, KC_LSFT, KC_TRNS,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RSFT, KC_TRNS, KC_TRNS,
    KC_TRNS, TG4,     KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,      KC_PGDN, KC_PGUP, KC_TRNS, KC_TRNS, KC_UP,            KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LALT,          KC_LGUI, KC_LCTL,               KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN,          KC_RGHT
  )
};
