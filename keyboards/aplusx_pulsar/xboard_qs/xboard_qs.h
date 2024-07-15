/* Copyright 2024 Aplusx Inc.
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

#include "quantum.h"

enum pulsar_keycodes {
    KC_TGUI = QK_KB_0,  // Ver 0.21.6에서 변경 (USER00,)  // Toggle between GUI Lock or Unlock
    KC_WIN_MODE,        // WINDOWS Keyboard로 변경
    KC_MAC_MODE,        // Machintosh Keyboard로 변경
    KC_TMODE,        // WINDOWS <--> Machintosh
    KC_DICTATION,       // MAC_key
    KC_DO_NOT_DISTURB,  // MAC_key
    KC_LOCK_SCREEN,     // MAC_key
    KC_TASK_VIEW,       // for win (gui + tap)
    KC_FILE_EXPLORER,   // for win (gui + e)
    KC_PC1,             // KM Switch PC1
    KC_PC2,             // KM Switch PC2
    KC_TPC,             // KM Switch PC1<-->PC2 Toggle
    INIT_3S,            // EE_CLR(EEPROM CLear)(공장초기화)를 3초이상 눌러야 동작
    KC_S_LED            // Change Status LED Brightness
};

#define KC_WINM KC_WIN_MODE
#define KC_MACM KC_MAC_MODE

#define KC_SIRI KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LOCK_ KC_LOCK_SCREEN

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_DIC  LGUI(KC_H)      // WIN ; 받아쓰기
#define KC_LOCK2 LGUI(KC_L)     // WIN ; pc잠금
#define KC_SNAP SCMD(KC_5)      // MAC Capure ; commnd + shift + 5
