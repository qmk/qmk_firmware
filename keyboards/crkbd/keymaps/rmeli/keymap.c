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
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 0, 0);
        // Only works with SPLIT_LED_STATE_ENABLE
        rgb_matrix_set_color(53, 255, 0, 0);
    }
    return false;
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

#define ______THUMB_LEFT_x3______ KC_LGUI, MO(_DWN), KC_SPC
#define ______THUMB_RIGHT_x3_____ KC_ENT, MO(_UP), KC_RCTL

// LAYOUT
//
// |-----------------------------|            |-----------------------------|
// |    |    |    |    |    |    |            |    |    |    |    |    |    |
// |----+----+----+----+----+----|            |----+----+----+----+----+----|
// |    |    |    |    |    |    |            |    |    |    |    |    |    |
// |----+----+----+----+----+----|            |----+----+----+----+----+----|
// |    |    |    |    |    |    |            |    |    |    |    |    |    |
// |----+----+----+----+----+----+----|  |----+----+----+----+----+----+----|
//                     |    |    |    |  |    |    |    |
//                     |--------------|  |--------------|

// Define wrapper for standard CRKB layout
#define LAYOUT_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_wrapper(
    // clang-format off
    ___________________QWERTY_L1_x6_____________________,                      ___________________QWERTY_R1_x6_____________________,
    ___________________QWERTY_L2_x6_____________________,                      ___________________QWERTY_R2_x6_____________________,
    ___________________QWERTY_L3_x6_____________________,                      ___________________QWERTY_R3_x6_____________________,
                                        ______THUMB_LEFT_x3______,     ______THUMB_RIGHT_x3_____
  ),

  [_COLEMAK_DH] = LAYOUT_wrapper(
    ________________COLEMAK_MOD_DH_L1_x6________________,                      ________________COLEMAK_MOD_DH_R1_x6________________,
    ________________COLEMAK_MOD_DH_L2_x6________________,                      ________________COLEMAK_MOD_DH_R2_x6________________,
    ________________COLEMAK_MOD_DH_L3_x6________________,                      ________________COLEMAK_MOD_DH_R3_x6________________,
                                        ______THUMB_LEFT_x3______,     ______THUMB_RIGHT_x3_____
  ),

  [_DWN] = LAYOUT_wrapper(
    _______, ______________NUMBER_LEFT_x5_______________,                      ______________NUMBER_RIGHT_x5______________, _______,
    _______, ______________UNICODE_L2_x5________________,                      ________________NAV_R2_x5__________________, XXXXXXX,
    _______, ______________UNICODE_L3_x5________________,                      ________________NAV_R3_x5__________________, _______,
                                        KC_LGUI, _______, _______,     _______,MO(_CFG), _______
  ),

  [_UP] = LAYOUT_wrapper(
    ___________________SYMBOL_LEFT_x6___________________,                      ___________________SYMBOL_RIGHT_x6__________________,
    _______, ____________NAV_VIM_x4____________, XXXXXXX,                      ____________________SYMBOL_R2_x6____________________,
    _______, _________________NONE_5x___________________,                      ____________________SYMBOL_R3_x6____________________,
                                        _______,MO(_CFG), _______,    _______, _______, _______
  ),

  [_CONFIG] = LAYOUT_wrapper(
    QK_BOOT, _________________NONE_5x___________________,                      _______________CONFIG_R1_x5________________,DF(_QWY),
    RGB_TOG, ________________RGB_L2_x5__________________,                      _______________CONFIG_R2_x5________________, XXXXXXX,
    XXXXXXX, ________________RGB_L3_x5__________________,                      _______________CONFIG_R3_x5________________,DF(_CMK),
                                        _______, _______, _______,   _______, _______, _______
  )
};
// clang-format on
