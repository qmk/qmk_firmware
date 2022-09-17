/*
Copyright 2019 @foostan
Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
Copyright 2021 Rocco Meli <@RMeli>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "rmeli.h"

// + -------------------- +
// + RGB MATRIX CALLBACKS |
// + -------------------- +

// LED numbers:
//      https://github.com/foostan/crkbd/blob/main/corne-classic/doc/buildguide_en.md

// Change LED color to red when CAPS LOCK is active
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 0, 0);
        // Only works with SPLIT_LED_STATE_ENABLE
        rgb_matrix_set_color(53, 255, 0, 0);
    }
}

// + ---- +
// + OLED |
// + ---- +

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_rocco();
    } else {
        oled_render_meli();
    }
    return false;
}

// + ------- +
// + KEY MAP |
// + ------- +

// Layer names
enum layer_names {
    _QWERTY,
    _COLEMAK_DH,
    _DWN,
    _UP,
    _CONFIG,
};

// Layer names shortcuts
#define _QWY 0
#define _CMK 1
#define _CFG 4

#define _____THUMB_LEFT_x3_____ KC_LGUI,MO(_DWN),  KC_SPC
#define _____THUMB_RIGHT_x3____  KC_ENT, MO(_UP), KC_RCTL

// clang-format off

// Define wrapper for standard CRKB layout
#define LAYOUT_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)

// Define free keys for base layout
// K01-K0A are free keys for row 0, K11-K1A are free keys for row 1, K21-K2A are free keys for row 2
// x5: 5 keys per row left to fill
// x6: 6 keys per row left to fill
#define LAYOUT_base_x5( \
    K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A,  \
                   K31, K32, K33, K34, K35, K36  \
  ) \
  LAYOUT_wrapper( \
      XXXXXXX,     K01,     K02,     K03,     K04,     K05,                          K06,     K07,     K08,     K09,     K0A, XXXXXXX, \
      XXXXXXX,     K11,     K12,     K13,     K14,     K15,                          K16,     K17,     K18,     K19,     K1A, XXXXXXX, \
      XXXXXXX,     K21,     K22,     K23,     K24,     K25,                          K26,     K27,     K28,     K29,     K2A, XXXXXXX, \
                                              K31,     K32,     K33,     K34,     K35,     K36 \
  )

#define LAYOUT_base_x6( \
    K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, K0B, K0C, \
    K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, K1B, K1C, \
    K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A, K2B, K2C, \
                   K31, K32, K33, K34, K35, K36  \
  ) \
  LAYOUT_wrapper( \
          K01,     K02,     K03,     K04,     K05,    K06,                       K07,     K08,     K09,     K0A,     K0B,     K0C, \
          K11,     K12,     K13,     K14,     K15,    K16,                       K17,     K18,     K19,     K1A,     K1B,     K1C, \
          K21,     K22,     K23,     K24,     K25,    K26,                       K27,     K28,     K29,     K2A,     K2B,     K2C, \
                                             K31,     K32,     K33,     K34,     K35,     K36 \
  )

// Define wrapper for base layout, so that free keys can be filled
// with partial row definitions in users/rmeli/krecords/wrappers.h
#define LAYOUT_base_wrapper_x5(...)       LAYOUT_base_x5(__VA_ARGS__)
#define LAYOUT_base_wrapper_x6(...)       LAYOUT_base_x6(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_base_wrapper_x6(
    _______________QWERTY_L1_x6________________, _______________QWERTY_R1_x6________________,
    _______________QWERTY_L2_x6________________, _______________QWERTY_R2_x6________________,
    _______________QWERTY_L3_x6________________, _______________QWERTY_R3_x6________________,
                        _____THUMB_LEFT_x3_____, _____THUMB_RIGHT_x3____
  ),

  [_COLEMAK_DH] = LAYOUT_base_wrapper_x5(
    ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
    ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
    ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________,
                      KC_LGUI,MO(_DWN),  KC_SPC,     KC_ENT, MO(_UP), KC_RCTL
  ),

  [_DWN] = LAYOUT_base_wrapper_x5(
    ______________NUMBER_LEFT_x5_______________, ______________NUMBER_RIGHT_x5______________,
    ______________UNICODE_L2_x5________________, ________________NAV_R2_x5__________________,
    ______________UNICODE_L3_x5________________, ________________NAV_R3_x5__________________,
                      KC_LGUI, _______, _______,    _______,MO(_CFG), _______
  ),

  [_UP] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,MO(_CFG), _______,   _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_CONFIG] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      UC_MOD,  KC_ASUP,   NK_ON, XXXXXXX, XXXXXXX,DF(_QWY),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                      XXXXXXX, KC_ASTG, NK_TOGG, CG_TOGG, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      UC_RMOD, KC_ASDN,  NK_OFF, CG_NORM, XXXXXXX,DF(_CMK),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  )
};

// clang-format on
