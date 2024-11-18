/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
    KC_LOPTN = QK_KB_0,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_MCTRL,
    KC_LNPAD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA,
#ifdef WIN_LOCK_SCREEN_ENABLE
    KC_WIN_LOCK_SCREEN,
    __KC_WIN_LOCK_SCREEN_NEXT,
#else
    __KC_WIN_LOCK_SCREEN_NEXT = KC_CORTANA + 1,
#endif
#ifdef MAC_LOCK_SCREEN_ENABLE
    KC_MAC_LOCK_SCREEN = __KC_WIN_LOCK_SCREEN_NEXT,
    __KC_MAC_LOCK_SCREEN_NEXT,
#else
    __KC_MAC_LOCK_SCREEN_NEXT = __KC_WIN_LOCK_SCREEN_NEXT,
#endif
    KC_SIRI = __KC_MAC_LOCK_SCREEN_NEXT,
#ifdef LK_WIRELESS_ENABLE
    BT_HST1,
    BT_HST2,
    BT_HST3,
    P2P4G,
    BAT_LVL,
#endif
#ifdef ANANLOG_MATRIX
    PROF1,
    PROF2,
    PROF3,
#endif
    NEW_SAFE_RANGE,
};

#ifndef LK_WIRELESS_ENABLE
    #define BT_HST1     KC_TRANS
    #define BT_HST2     KC_TRANS
    #define BT_HST3     KC_TRANS
    #define P2P4G       KC_TRANS
    #define BAT_LVL     KC_TRANS
#endif
#ifndef ANANLOG_MATRIX
    #define PROF1 KC_TRANS
    #define PROF2 KC_TRANS
    #define PROF3 KC_TRANS
#endif

#define KC_TASK KC_TASK_VIEW
#define KC_FILE KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CTANA KC_CORTANA
#define KC_WLCK KC_WIN_LOCK_SCREEN
#define KC_MLCK KC_MAC_LOCK_SCREEN

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

bool process_record_keychron_common(uint16_t keycode, keyrecord_t *record);
void keychron_common_task(void);

#ifdef ENCODER_ENABLE
void encoder_cb_init(void);
#endif

