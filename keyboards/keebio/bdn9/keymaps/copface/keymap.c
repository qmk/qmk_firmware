// Copyright 2021 Gustavs Gutmanis (@gustavs-gutmanis)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _SMITE = 0,
};

enum custom_keycodes {
    S_7 = SAFE_RANGE, // [VEL] - laugh
    S_8, // [VVN] - No
    S_9, // [VVA] - OK

    S_4, // [VVB] - be right back
    S_5, // [VVVE] - on my way
    S_6, // [VVM] - out of mana

    S_1, // [VRR] - retreat
    S_2, // [VDD] - defend
    S_3, // [VAA] - attack
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case S_7:
      if (record->event.pressed) {
        // VEL
        SEND_STRING("v" SS_DELAY(20) "e"  SS_DELAY(20) "l");
      }
      break;
    case S_8:
      if (record->event.pressed) {
        // VVN
        SEND_STRING("v" SS_DELAY(20) "v"  SS_DELAY(20) "n");
      }
      break;
    case S_9:
      if (record->event.pressed) {
        // VVA
        SEND_STRING("v" SS_DELAY(20) "v"  SS_DELAY(20) "a");
      }
      break;

    case S_4:
      if (record->event.pressed) {
        // VVB
        SEND_STRING("v" SS_DELAY(20) "v"  SS_DELAY(20) "b");
      }
      break;
    case S_5:
      if (record->event.pressed) {
        // VVVE
        SEND_STRING("v" SS_DELAY(20) "v"  SS_DELAY(20) "v"  SS_DELAY(20) "e");
      }
      break;
    case S_6:
      if (record->event.pressed) {
        // VVM
        SEND_STRING("v" SS_DELAY(20) "v"  SS_DELAY(20) "m");
      }
      break;

    case S_1:
      if (record->event.pressed) {
        // VRR
        SEND_STRING("v" SS_DELAY(20) "r"  SS_DELAY(20) "r");
      }
      break;
    case S_2:
      if (record->event.pressed) {
        // VDD
        SEND_STRING("v" SS_DELAY(20) "d"  SS_DELAY(20) "d");
      }
      break;
    case S_3:
      if (record->event.pressed) {
        // VAA
        SEND_STRING("v" SS_DELAY(20) "a"  SS_DELAY(20) "a");
      }
      break;
  }

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SMITE] = LAYOUT(
        S_7, S_8, S_9,
        S_4, S_5, S_6,
        S_1, S_2, S_3
    ),
};
