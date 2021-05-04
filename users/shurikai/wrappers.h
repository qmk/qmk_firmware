/*
 * Copyright 2020 Jason Chestnut <jason.chestnut@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...)          LAYOUT(__VA_ARGS__)
#define LAYOUT_reviung_wrapper(...)  LAYOUT_reviung39(__VA_ARGS__)
#define LAYOUT_microdox_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)
#define LAYOUT_preonic_wrapper(...)  LAYOUT_preonic_grid(__VA_ARGS__)
#define LAYOUT_niumini_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)

/*
 * My standard keymap is based on a 34-key split ortho board. This includes 5 columns and 2 thumb
 * keys per hand. The following macros define the base 34 key map, with any additional keys for a
 * given keyboard left to be defined in that specific keymap.c file.
 */

// Used as a blank number row for huge keyboards like the Preonic.
#define _________________BLANK_ROW_________________    _______, _______, _______, _______, _______

/* BASE
 * ,----------------------------------+    +----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |  cA  |  aS  |  sD  |  gF  |   G  |    |   H  |  gJ  |  sK  |  aL  |  c;  |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      | TAB  | BSPC |    | SPC  | ENT  |
 *                      `-------------+    +-------------'
 */
#define _________________BASE_L1___________________    KC_Q,     KC_W,    KC_E,     KC_R,     KC_T
#define _________________BASE_L2___________________    KC_CTLA,  KC_ALTS, KC_SFTD,  KC_GUIF,  KC_G
#define _________________BASE_L3___________________    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B
#define ____BASE_LT_____                                                            LT_NAV,   LT_NUM

#define _________________BASE_R1___________________    KC_Y,     KC_U,    KC_I,     KC_O,     KC_P
#define _________________BASE_R2___________________    KC_H,     KC_GUIJ, KC_SFTK,  KC_ALTL,  KC_CTLCLN
#define _________________BASE_R3___________________    KC_N,     KC_M,    KC_COMMA, KC_DOT,   KC_SLASH
#define ____BASE_RT_____                               LT_SYM,   LT_ADJ

/* Navigation
 * ,----------------------------------+    +----------------------------------.
 * |      |      |      |      |      |    |      | End  | Home |      |      |
 * |------+------+------+------+-------    |------+------+------+------+------|
 * | LCTL | LALT | LSFT | LGUI |      |    | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |      |      |      |      |      |    |      | PgDn | PgDn |      |      |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      |XXXXXX|      |    | Tab  |      |
 *                      `-------------+    +-------------'
 */
#define _________________NAVI_L1___________________    _______,  _______,  _______,  _______,  _______
#define _________________NAVI_L2___________________    KC_LCTL,  KC_LALT,  KC_LSFT,  KC_LGUI,  _______
#define _________________NAVI_L3___________________    _______,  _______,  _______,  _______,  _______
#define ____NAVI_LT_____                                                             KC_NO,    _______

#define _________________NAVI_R1___________________    _______,  KC_END,   KC_HOME,  _______,  _______
#define _________________NAVI_R2___________________    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______
#define _________________NAVI_R3___________________    _______,  KC_PGDN,  KC_PGUP,  _______,  _______
#define ____NAVI_RT_____                               KC_TAB,   _______

/* Symbols
 * ,----------------------------------+    +----------------------------------.
 * |  ~   |  `   |  {   |  }   |      |    |      |  &   |   *  |      |   |  |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |      |      |  (   |  )   |  @   |    |   -  |  $   |   %  |  ^   |  ' " |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |      |      |  [   |  ]   |      |    |   _  |  !   |   @  |  #   |   \  |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      | Shift|  DEL |    |XXXXXX|      |
 *                      `-------------+    +-------------'
 */
#define _________________SYM_L1____________________    KC_TILD,  KC_GRV,   KC_LCBR,  KC_RCBR,  _______
#define _________________SYM_L2____________________    _______,  _______,  KC_LPRN,  KC_RPRN,  KC_AT
#define _________________SYM_L3____________________    _______,  _______,  KC_LBRC,  KC_RBRC,  _______
#define _____SYM_LT_____                                                             KC_LSFT,  KC_DEL

#define _________________SYM_R1____________________    _______,  KC_AMPR,  KC_ASTR,  _______,  KC_PIPE
#define _________________SYM_R2____________________    KC_MINS,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_QUOT
#define _________________SYM_R3____________________    KC_UNDS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_BSLS
#define _____SYM_RT_____                               KC_NO,    _______

/* Numbers (ten-key style)
 * ,----------------------------------+    +----------------------------------.
 * |      |      |      |      |      |    |   +  |   7  |   8  |   9  |      |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * | Ctrl | Alt  | Shft | GUI  |      |    |   -  |   4  |   5  |   6  |   *  |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |      |      |      |      |      |    |   =  |   1  |   2  |   3  |   /  |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      |      |XXXXXX|    |   0  |   .  |
 *                      `-------------+    +-------------'
 */
#define _________________NUM_L1____________________    _______,  _______,  _______,  _______,  _______
#define _________________NUM_L2____________________    KC_LCTL,  KC_LALT,  KC_LSFT,  KC_LGUI,  _______
#define _________________NUM_L3____________________    _______,  _______,  _______,  _______,  _______
#define ____NUM_LT______                                                             _______,  KC_NO

#define _________________NUM_R1____________________    KC_PPLS,  KC_7,     KC_8,     KC_9,     _______
#define _________________NUM_R2____________________    KC_PMNS,  KC_4,     KC_5,     KC_6,     KC_ASTR
#define _________________NUM_R3____________________    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_SLSH
#define ____NUM_RT______                               KC_0,     KC_DOT

/* Function
 * ,----------------------------------+    +----------------------------------.
 * |  F10 |  F9  |  F8  |  F7  |      |    |      |      |      |      |      |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |  F11 |  F6  |  F5  |  F4  |      |    |      |      | Alt  |XXXXXX|      |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |  F12 |  F3  |  F2  |  F1  |      |    |      |      |      |      |      |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      |      |      |    |      |      |
 *                      `-------------+    +-------------'
 */
#define _________________FN_L1_____________________    KC_F10,   KC_F9,    KC_F8,    KC_F7,    _______
#define _________________FN_L2_____________________    KC_F11,   KC_F6,    KC_F5,    KC_F4,    _______
#define _________________FN_L3_____________________    KC_F12,   KC_F3,    KC_F2,    KC_F1,    _______
#define ____FN_LT_______                                                             _______,  _______

#define _________________FN_R1_____________________    _______,  _______,  _______,  _______,  _______
#define _________________FN_R2_____________________    _______,  _______,  KC_RALT,  KC_NO,    _______
#define _________________FN_R3_____________________    _______,  _______,  _______,  _______,  _______
#define ____FN_RT_______                               _______,  _______

/* Adjust
 * ,----------------------------------+    +----------------------------------.
 * | Tab  |      |      |      |      |    |      |      |      |      | Del  |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |RGBTOG|      |      |      |      |    |      |      |      |      |      |
 * |------+------+------+------+------|    |------+------+------+------+------|
 * |      |      |      |      |      |    |      |      |      |      |Reset |
 * `------+------+------+------+------|    |------+------+------+------+------'
 *                      | Tab  | Del  |    |      |XXXXXX|
 *                      `-------------+    +-------------'
 */
#define _________________ADJ_L1____________________    KC_TAB,   _______,  _______,  _______,  _______
#define _________________ADJ_L2____________________    _______,  _______,  _______,  _______,  _______
#define _________________ADJ_L3____________________    _______,  _______,  _______,  _______,  _______
    #define ____ADJ_LT______                                                         KC_TAB,  KC_DEL

#define _________________ADJ_R1____________________    _______,  _______,  _______,  _______,  KC_DEL
#define _________________ADJ_R2____________________    _______,  _______,  _______,  _______,  _______
#define _________________ADJ_R3____________________    _______,  _______,  _______,  _______,  RESET
#define ____ADJ_RT______                               _______,  KC_NO

