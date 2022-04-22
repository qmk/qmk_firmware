// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "layouts.h"

/* Adjust, every thing on top row (except backspace) is related to rgb stuff
 * ,-----------------------------------------------------------------------------------.
 * |      |Reset |Debug |RGBTGL|RGBMDE| Hue+ | Hue- | Sat+ | Sat- | BriU | BriD | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MseCly| AudOn|AudOff|AgNorm|AgSwap|Dvorak|Colmak|Qwerty|QgmlUS|QgmlNO|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice+|Voice-|MusOn |MusOff|MIDIOn|MIDIOF|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
#define adjust_map LAYOUT_ortho_4x12(\
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI,    RGB_SAD,     RGB_VAI,    RGB_VAD,      KC_DEL,\
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, DF(DVORAK), DF(COLEMAK), DF(QWERTY), DF(QGMLWB_US), DF(QGMLWB_NO),\
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON,    TERM_OFF,    XXXXXXX,    _______,      _______,\
    _______, _______, _______, _______, _______, _______, _______, _______,    _______,     _______,    _______,      _______\
)

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   7  |   8  |   9  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   1  |   2  |   3  |   -  | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | XXXX |      |      |   0  |   ,  |   .  |   +  | XXXX |
 * `-----------------------------------------------------------------------------------'
*/
#define numpad_map LAYOUT_ortho_4x12(\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8,    KC_9,   KC_KP_SLASH,    _______,\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5,    KC_6,   KC_KP_ASTERISK, _______,\
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,    KC_3,   KC_KP_MINUS,    XXXXXXX,\
    _______, _______, _______, _______, XXXXXXX, _______, _______, KC_0, KC_COMM, KC_DOT, KC_KP_PLUS,     XXXXXXX\
)
