// Copyright 2023 c0ldbru
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(13),  KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,   KC_PSCR,  KC_SCRL, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  KC_DEL,   KC_END,  KC_PGDN,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot1 -- F1 */
  [1] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_R,    KC_X,    KC_F,    KC_S,   KC_U,   KC_Z,   KC_V,   KC_J,   KC_P,    KC_Q,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_B,    KC_T,    KC_E,    KC_G,   KC_H,   KC_I,   KC_K,   KC_L,   KC_M,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_A,    KC_Y,    KC_D,   KC_W,   KC_C,   KC_O,   KC_N,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot2 -- F2 */
  [2] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_S,    KC_Y,    KC_G,    KC_T,   KC_V,   KC_A,   KC_W,   KC_K,   KC_Q,    KC_R,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_C,    KC_U,    KC_F,    KC_H,   KC_I,   KC_J,   KC_L,   KC_M,   KC_N,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_B,    KC_Z,    KC_E,   KC_X,   KC_D,   KC_P,   KC_O,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot3 -- F3 */
  [3] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_T,    KC_Z,    KC_H,    KC_U,   KC_W,   KC_B,   KC_X,   KC_L,   KC_R,    KC_S,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_D,    KC_V,    KC_G,    KC_I,   KC_J,   KC_K,   KC_M,   KC_N,   KC_O,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_C,    KC_A,    KC_F,   KC_Y,   KC_E,   KC_Q,   KC_P,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot4 -- F4 */
  [4] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_U,    KC_A,    KC_I,    KC_V,   KC_X,   KC_C,   KC_Y,   KC_M,   KC_S,    KC_T,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_E,    KC_W,    KC_H,    KC_J,   KC_K,   KC_L,   KC_N,   KC_O,   KC_P,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_D,    KC_B,    KC_G,   KC_Z,   KC_F,   KC_R,   KC_Q,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot5 -- F5 */
  [5] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_V,    KC_B,    KC_J,    KC_W,   KC_Y,   KC_D,   KC_Z,   KC_N,   KC_T,    KC_U,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_F,    KC_X,    KC_I,    KC_K,   KC_L,   KC_M,   KC_O,   KC_P,   KC_Q,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_E,    KC_C,    KC_H,   KC_A,   KC_G,   KC_S,   KC_R,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot6 -- F6 */
  [6] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_W,    KC_C,    KC_K,    KC_X,   KC_Z,   KC_E,   KC_A,   KC_O,   KC_U,    KC_V,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_G,    KC_Y,    KC_J,    KC_L,   KC_M,   KC_N,   KC_P,   KC_Q,   KC_R,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_F,    KC_D,    KC_I,   KC_B,   KC_H,   KC_T,   KC_S,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot7 -- F7 */
  [7] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_X,    KC_D,    KC_L,    KC_Y,   KC_A,   KC_F,   KC_B,   KC_P,   KC_V,    KC_W,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_H,    KC_Z,    KC_K,    KC_M,   KC_N,   KC_O,   KC_Q,   KC_R,   KC_S,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_G,    KC_E,    KC_J,   KC_C,   KC_I,   KC_U,   KC_T,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot8 -- F8 */
  [8] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_Y,    KC_E,    KC_M,    KC_Z,   KC_B,   KC_G,   KC_C,   KC_Q,   KC_W,    KC_X,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_I,    KC_A,    KC_L,    KC_N,   KC_O,   KC_P,   KC_R,   KC_S,   KC_T,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_H,    KC_F,    KC_K,   KC_D,   KC_J,   KC_V,   KC_U,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot9 -- F9 */
  [9] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_Z,    KC_F,    KC_N,    KC_A,   KC_C,   KC_H,   KC_D,   KC_R,   KC_X,    KC_Y,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_J,    KC_B,    KC_M,    KC_O,   KC_P,   KC_Q,   KC_S,   KC_T,   KC_U,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_I,    KC_G,    KC_L,   KC_E,   KC_K,   KC_W,   KC_V,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot10 -- F10 */
  [10] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_A,    KC_G,    KC_O,    KC_B,   KC_D,   KC_I,   KC_E,   KC_S,   KC_Y,    KC_Z,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_K,    KC_C,    KC_N,    KC_P,   KC_Q,   KC_R,   KC_T,   KC_U,   KC_V,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_J,    KC_H,    KC_M,   KC_F,   KC_L,   KC_X,   KC_W,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot11 -- F11 */
  [11] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_B,    KC_H,    KC_P,    KC_C,   KC_E,   KC_J,   KC_F,   KC_T,   KC_Z,    KC_A,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_L,    KC_D,    KC_O,    KC_Q,   KC_R,   KC_S,   KC_U,   KC_V,   KC_W,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_K,    KC_I,    KC_N,   KC_G,   KC_M,   KC_Y,   KC_X,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot12 -- F12 */
  [12] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_C,    KC_I,    KC_Q,    KC_D,   KC_F,   KC_K,   KC_G,   KC_U,   KC_A,    KC_B,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_M,    KC_E,    KC_P,    KC_R,   KC_S,   KC_T,   KC_V,   KC_W,   KC_X,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_L,    KC_J,    KC_O,   KC_H,   KC_N,   KC_Z,   KC_Y,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot13 -- F13 (default for hack mode) */
  [13] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),  DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_D,    KC_J,    KC_R,    KC_E,   KC_G,   KC_L,   KC_H,   KC_V,   KC_B,    KC_C,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_N,    KC_F,    KC_Q,    KC_S,   KC_T,   KC_U,   KC_W,   KC_X,   KC_Y,    KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_M,    KC_K,    KC_P,   KC_I,   KC_O,   KC_A,   KC_Z,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* memfrob -- scroll */
  [14] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),     DF(7),  DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,      KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_LBRC, KC_RBRC, S(KC_O), S(KC_X),S(KC_6),S(KC_S),S(KC_MINS),S(KC_C),S(KC_E), S(KC_Z), KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, S(KC_K), S(KC_Y), S(KC_N), S(KC_L),S(KC_M),S(KC_B),S(KC_2),   S(KC_A),S(KC_F), KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          S(KC_P), S(KC_R), S(KC_I),KC_BSLS,S(KC_H),S(KC_D),   S(KC_G),KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* rot47 -- pause */
  [15] = LAYOUT_tkl_ansi(
      KC_ESC,  DF(0),   DF(1),   DF(2),   DF(3),  DF(4),  DF(5),  DF(6),      DF(7),     DF(8),   DF(9),   DF(10),   DF(11),  DF(12),   DF(13),   DF(14),  DF(15),
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,       KC_8,      KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_B,    KC_H,    KC_6,    KC_C,   KC_E,   KC_J,   KC_F,       S(KC_SCLN),S(KC_2),  KC_A,    KC_LBRC,  KC_RBRC, KC_BSLS,  OSL(20),   KC_END,  KC_PGDN,
      KC_CAPS, KC_2,    KC_D,    KC_5,    KC_7,   KC_8,   KC_9,   KC_SCLN,    S(KC_COMM),KC_EQL,  KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,          KC_K,    KC_I,    KC_4,   KC_G,   KC_3,   S(KC_SLSH), S(KC_DOT), KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(21),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

    /* function key for basic keeb functionality */
  [21] = LAYOUT_tkl_ansi(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                     KC_VOLU,
      KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,            KC_MPRV, KC_VOLD, KC_MNXT)
};
