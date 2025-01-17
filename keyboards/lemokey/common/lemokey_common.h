/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"

// clang-format off
enum {
    KC_TASK_VIEW = QK_KB_0,
    KC_FILE_EXPLORER,
    KC_LOCK_SCREEN,        // Lock screen
#ifdef LK_WIRELESS_ENABLE
    BT_HST1,
    BT_HST2,
    BT_HST3,
    P2P4G,
    BAT_LVL,
#else
    BT_HST1 = _______,
    BT_HST2 = _______,
    BT_HST3 = _______,
    P2P4G   = _______,
    BAT_LVL = _______,
#endif
#ifdef ANANLOG_MATRIX
    PROF1,
    PROF2,
    PROF3,
#endif
	NEW_SAFE_RANGE,
};

#define KC_TASK KC_TASK_VIEW
#define KC_FILE KC_FILE_EXPLORER
#define KC_LOCK KC_LOCK_SCREEN

#ifdef ANANLOG_MATRIX
enum {
    KEY_PRESS_FN = 0x01 << 0,
    KEY_PRESS_P  = 0x01 << 1,
    KEY_PRESS_PROF_COMBO = KEY_PRESS_FN | KEY_PRESS_P,
};
#endif

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

bool process_record_lemokey_common(uint16_t keycode, keyrecord_t *record);
void lemokey_common_task(void);

#ifdef ENCODER_ENABLE
void encoder_cb_init(void);
#endif
#ifdef ANANLOG_MATRIX
void analog_matrix_rx(uint8_t *data, uint8_t length);
#endif

