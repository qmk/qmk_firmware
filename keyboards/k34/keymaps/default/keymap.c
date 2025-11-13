// Copyright 2021 jp_smasher (@jp_smasher)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _L1,
    _L2
};

// define layers
#define L1  MO(_L1)
#define L2  LT(_L2, KC_ENT)

// define home-row styled alpha-mods
#define C_C     LCTL_T(KC_C)
#define C_COMM  LCTL_T(KC_COMM)
#define G_A     CMD_T(KC_A)
#define G_SC    CMD_T(KC_SCLN)
#define A_X     LOPT_T(KC_X)
#define A_DOT   LOPT_T(KC_DOT)
#define S_Z     SFT_T(KC_Z)
#define S_SLSH  SFT_T(KC_SLSH)

// combos for application shortcuts
#define SG_LBRC LSG(KC_LBRC)
#define SG_RBRC LSG(KC_RBRC)
#define G_LBRC  G(KC_LBRC)
#define G_RBRC  G(KC_RBRC)
#define A_SLSH  A(KC_SLSH)

/* combos */
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
combo_t key_combos[] = {COMBO(jk_combo, KC_ESC)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
  [_BASE] = LAYOUT_split_3x5_2(
    KC_Q, KC_W, KC_E, KC_R, KC_T,        KC_Y,   KC_U, KC_I,   KC_O,  KC_P,
    G_A,  KC_S, KC_D, KC_F, KC_G,        KC_H,   KC_J, KC_K,   KC_L,  G_SC,
    S_Z,  A_X,  C_C,  KC_V, KC_B,        KC_N,   KC_M, C_COMM, A_DOT, S_SLSH,
				              L1,   KC_SPC,      KC_SPC, L2
  ),


  [_L1] = LAYOUT_split_3x5_2(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,
    KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_GRV,       KC_QUOT, KC_LBRC, KC_RBRC, KC_BSLS, KC_PIPE,
    _______, _______, _______, KC_TAB,  _______,      KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,
				                       _______, _______,      _______, _______
  ),

  [_L2] = LAYOUT_split_3x5_2(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
    _______, _______, _______, _______, KC_DOT,       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_BSPC,
    _______, _______, _______, _______, _______,      A_SLSH,  SG_LBRC, SG_RBRC, G_LBRC,   G_RBRC,
				                       KC_LALT, KC_LGUI,      _______, _______
  ),
};
