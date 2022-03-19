// Copyright 2022 Adrian (@elagil)
// SPDX-License-Identifier: GPL-2.0-or-later
 
#include QMK_KEYBOARD_H

enum layers {
    BASE,
    _F1,
    _F2
};

#define PRE_WRD LCTL(KC_LEFT) // jump to next word
#define NXT_WRD LCTL(KC_RGHT) // jump to previous word

#define NXT_WDL LCTL(KC_DEL)  // delete next word
#define PRE_WDL LCTL(KC_BSPC) // delete previous word

#define PRE_TAB LCTL(KC_PGUP) // jump to previous tab
#define NXT_TAB LCTL(KC_PGDN) // jump to next tab

#define SFT_TAB LSFT(KC_TAB)  // Shift + Tab

#define MF1 MO(_F1) // F1 layer access
#define MF2 MO(_F2) // F2 layer access

/*
 * This default keymap is aimed at users of the US, the US international layout, or Eurkey (https://eurkey.steffen.bruentjen.eu/).
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE
   *       ,-----------------------------------------.                              ,-----------------------------------------.
   *       |  =+  |  1!  |  2@  |  3#  |  4$  |  5%  |                              |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       | [{   |  Q   |  W   |  E   |  R   |  T   |                              |   Y  |   U  |   I  |   O  |   P  |  }]  |
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       | Tab  |  A   |  S   |  D   |  F   |  G   |                              |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   *       |------+------+------+------+------+------+------.                ,------+------+------+------+------+------+------|
   *       | Sft  |  Z   |  X   |  C   |  V   |  B   | GEsc |                |  \|  |   N  |   M  |  ,<  |  .>  |  /?  |  Sft |
   *       `------------------------------------------------'------.  ,------`------------------------------------------------'
   *                            | LGUI |  SYM | Back | Ctrl | LAlt |  | Ent  | Ralt | Space| NAV  | RGUI |
   *                            `----------------------------------'  `----------------------------------'
   */
  [BASE] = LAYOUT(
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_LBRC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GESC,                   KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_LGUI, MF2,     KC_BSPC, KC_LCTL, KC_LALT, KC_ENT,  KC_RALT, KC_SPC,  MF1,     KC_RGUI
  ),

  /* F1
   *       ,-----------------------------------------.                              ,-----------------------------------------.
   *       |      |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       |      |      |      | Vol+ |      |      |                              |      |  <-W |  UP  | W->  | PRINT|   F12|
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       | Del  |      | Prev | Play | Next |      |                              | <--- |  <-  | DOWN |  ->  | ---> |      |
   *       |------+------+------+------+------+------+------.                ,------+------+------+------+------+------+------|
   *       |  T   |      |      | Vol- |      |      |      |                |      |      |  <-X | Ins  | X->  | PAUSE|  T   |
   *       `------------------------------------------------'------.  ,------`------------------------------------------------'
   *                            |      |  T   |      |      |      |  |      |      |      |   T  |      |
   *                            `----------------------------------'  `----------------------------------'
   */
  [_F1] = LAYOUT(
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX,                                     XXXXXXX, PRE_WRD, KC_UP,   NXT_WRD, KC_PSCR, KC_F12,
    KC_DEL,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                     KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX,  
    _______, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, _______,                   _______, XXXXXXX, PRE_WDL, KC_INS,  NXT_WDL, KC_PAUS, _______,
                               XXXXXXX, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX
  ),

  /* F2
   *       ,-----------------------------------------.                              ,-----------------------------------------.
   *       |      |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       |      |      |      | PgUp |      |      |                              |      |    7 |    8 |    9 |      |   F12|
   *       |------+------+------+------+------+------|                              |------+------+------+------+------+------|
   *       | STab |      |<--Tab| Del  |-->Tab|      |                              |   +  |    4 |    5 |    6 |   *  |      |
   *       |------+------+------+------+------+------+------.                ,------+------+------+------+------+------+------|
   *       |  T   |      |      | PgDn |      |      |      |                |      |   -  |    1 |    2 |    3 |   /  |  T   |
   *       `------------------------------------------------'------.  ,------`------------------------------------------------'
   *                            |      |  T   |      |      |      |  | Pent |      |   0  |      |  NLK |
   *                            `----------------------------------'  `----------------------------------'
   */
  [_F2] = LAYOUT(
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, KC_F12,
    SFT_TAB, XXXXXXX, PRE_TAB, KC_DEL,  NXT_TAB, XXXXXXX,                                     KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, XXXXXXX,  
    _______, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, _______,
                               XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PENT, XXXXXXX, KC_P0,   XXXXXXX, KC_NUM
  )
};
