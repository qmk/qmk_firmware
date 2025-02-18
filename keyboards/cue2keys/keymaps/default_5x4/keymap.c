// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include <stdint.h>

enum layer_names { _BASE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_BASE] = LAYOUT_5x4(
                                                                  // clang-format off
        KC_MINUS, KC_PLUS, KC_PLUS, KC_ENTER, KC_ENTER,
        KC_ASTERISK, KC_9, KC_6, KC_3, KC_0,
        KC_SLASH, KC_8, KC_5, KC_2, KC_0,
        KC_NUM_LOCK, KC_7, KC_4, KC_1, KC_DEL
                                                                  // clang-format on
                                                                  )};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {[_BASE] = {}};
#endif
