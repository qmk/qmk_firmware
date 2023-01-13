/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
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

#include "nazu.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ISO 60
   *
   * ,-----------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  | [ { | ] } | Enter  |
   * |----------------------------------------------------------------------------------       |
   * |   Caps  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  | ; : | \ | |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift | ` ~ |  Y  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ | Shift   | FN2 |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  |  FN1  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */

  [_QWERTY] = LAYOUT_60_iso_split_space_bs_rshift(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    TD_CAPS, KC_NUBS, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, KC_RSFT, MO(_FN2),
    KC_LCTL, KC_LGUI, KC_LALT,                   XXXXXXX, KC_SPC,  XXXXXXX,          KC_R2,   KC_R1,   MO(_FN1),KC_LCTL
  ),

  /*
   * Colemak
   * ,-----------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  | ; : | [ { | ] } | Enter  |
   * |----------------------------------------------------------------------------------       |
   * |Backspace|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  | ' " |  #  |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift |  Z  |  X  |  C  |  V  |  B  | \ | |  K  |  M  | , < | . > | / ? | Shift   | FN2 |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  |  FN1  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_60_iso_split_space_bs_rshift(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,
    KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_HASH, KC_ENT,
    TD_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSLS, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2),
    KC_LCTL, KC_LGUI, KC_LALT,                   XXXXXXX, KC_SPC,  XXXXXXX,          KC_R2,   KC_R1,   MO(_FN1),KC_LCTL
  ),

  /*
   * Colemak DH
   * ,-----------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  F  |  P  |  B  |  J  |  L  |  U  |  Y  | ; : | [ { | ] } | Enter  |
   * |----------------------------------------------------------------------------------       |
   * |Backspace|  A  |  R  |  S  |  T  |  G  |  M  |  N  |  E  |  I  |  O  | ' " |  #  |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift |  Z  |  X  |  C  |  D  |  V  | \ | |  K  |  H  | , < | . > | / ? | Shift   | FN2 |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  |  FN1  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */
  [_COLEMAK_DH] = LAYOUT_60_iso_split_space_bs_rshift(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,
    KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_HASH, KC_ENT,
    TD_CAPS, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_BSLS, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2),
    KC_LCTL, KC_LGUI, KC_LALT,                   XXXXXXX, KC_SPC,  XXXXXXX,          KC_R2,   KC_R1,   MO(_FN1),KC_LCTL
  ),

  /*
   * FN1
   * ,-----------------------------------------------------------------------------------------.
   * | ` ~ | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   DEL     |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |RGBTg|RGBMd|Hue +|Hue -|Sat +|Sat -|Val +|Val -|     |Print|ScLck|Pause| Enter  |
   * |----------------------------------------------------------------------------------       |
   * |  Caps   |     |     |     |     |     |     |     |     |     | Ins |     |     |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift |     |     |     |BL - |BL TG|BL + |     |     |     |     |     | Shift   | FN2 |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  |  FN1  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */
  [_FN1] = LAYOUT_60_iso_split_space_bs_rshift(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______,                   XXXXXXX, _______, XXXXXXX,          _______, _______, _______, _______
  ),

  /*
   * FN2
   * ,-----------------------------------------------------------------------------------------.
   * |RESET|QWRTY|COLMK|CLMKDH|    |     |     |Prev |Play |Next |Mute |VolDn|VolUp|   DEL     |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |     | Up  |     |     |     |     |     |     |     |     |     |     | Enter  |
   * |----------------------------------------------------------------------------------       |
   * |  Caps   |Left |Down |Right|     |     |Left |Down | Up  |Right|     |     |     |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift |     |     |     |     |     |     |     |     |     |     |     | Shift   |     |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  | RGUI  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */
  [_FN2] = LAYOUT_60_iso_split_space_bs_rshift(
    QK_BOOT, QWERTY,  COLEMAK, CLMKDH,  XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,  KC_DEL,
    _______, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SWAP,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, KC_NORM, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______,                   XXXXXXX, _______, XXXXXXX,          _______, _______, _______, _______
  ),
};
