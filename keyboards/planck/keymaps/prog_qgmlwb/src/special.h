// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "layouts.h"

/* Adjust
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug| RGB  |RGBMod| Hue- | Hue+ | Sat- | Sat+ | Bri- | Bri+ | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX |MusMod|AudOff| AudOn|AgNorm|AgSwap|Dvorak|Colmak|Qwerty|QgmlEN|QgmlNO|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|MusOff| MusOn|MIDIOf|MIDIOn|      |      |  T0  |  T1  |  T2  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | XXXX | XXXX | XXXX | XXXX |
 * `-----------------------------------------------------------------------------------'
*/
#define adjust_map LAYOUT_ortho_4x12(\
    QK_RBT,  QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD,    RGB_SAI,     RGB_VAD,    RGB_VAI,       KC_DEL,\
    QK_MAKE, XXXXXXX, MU_MOD,  AU_OFF,  AU_ON,   AG_NORM, AG_SWAP, DF(DVORAK), DF(COLEMAK), DF(QWERTY), DF(QGMLWB_EN), DF(QGMLWB_NO),\
    _______, MUV_IN,  MUV_DE,  MU_OFF,  MU_ON,   MI_OFF,  MI_ON,   _______,    _______,     KC_T0,      KC_T1,         KC_T2,\
    _______, _______, _______, _______, _______, _______, _______, _______,    XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX\
)

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |  7   |  8   |  9   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |  4   |  5   |  6   |  *   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |  1   |  2   |  3   |  -   | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | XXXX |      |      |  0   |  ,   |  .   |  +   | XXXX |
 * `-----------------------------------------------------------------------------------'
*/
#define numpad_map LAYOUT_ortho_4x12(\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8,    KC_9,   KC_KP_SLASH,    _______,\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5,    KC_6,   KC_KP_ASTERISK, _______,\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,    KC_3,   KC_KP_MINUS,    XXXXXXX,\
    _______, _______, _______, _______, XXXXXXX, _______, _______, KC_0, KC_COMM, KC_DOT, KC_KP_PLUS,     XXXXXXX\
)
