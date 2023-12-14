// Copyright 2023 Nick Taormina
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define KC_X0 LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_MAIN] = LAYOUT_ortho_4x3(KC_ENT, KC_0, KC_BSPC, KC_7, KC_8, KC_9, KC_4, KC_5, KC_6, KC_1, KC_2, KC_3), [_FN] = LAYOUT_ortho_4x3(KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_CALCULATOR, KC_MY_COMPUTER, KC_WWW_HOME, KC_BACKSLASH, KC_PIPE, KC_TILDE, KC_UNDO, C(KC_C), C(KC_V))};
