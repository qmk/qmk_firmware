/* Copyright 2020
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

// Sendstring lookup tables for Finnish layouts

#pragma once

#include "keymap_finnish.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 0, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 1, 1, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 1, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0)
};

const uint8_t ascii_to_keycode_lut[128] PROGMEM = {
    // NUL   SOH      STX      ETX      EOT      ENQ      ACK      BEL
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // BS    TAB      LF       VT       FF       CR       SO       SI
    KC_BSPC, KC_TAB,  KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // DLE   DC1      DC2      DC3      DC4      NAK      SYN      ETB
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // CAN   EM       SUB      ESC      FS       GS       RS       US
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    //       !        "        #        $        %        &        '
    KC_SPC,  FI_1,    FI_2,    FI_3,    FI_4,    FI_5,    FI_6,    FI_QUOT,
    // (     )        *        +        ,        -        .        /
    FI_8,    FI_9,    FI_QUOT, FI_PLUS, FI_COMM, FI_MINS, FI_DOT,  FI_7,
    // 0     1        2        3        4        5        6        7
    FI_0,    FI_1,    FI_2,    FI_3,    FI_4,    FI_5,    FI_6,    FI_7,
    // 8     9        :        ;        <        =        >        ?
    FI_8,    FI_9,    FI_DOT,  FI_COMM, FI_LABK, FI_0,    FI_LABK, FI_PLUS,
    // @     A        B        C        D        E        F        G
    FI_2,    FI_A,    FI_B,    FI_C,    FI_D,    FI_E,    FI_F,    FI_G,
    // H     I        J        K        L        M        N        O
    FI_H,    FI_I,    FI_J,    FI_K,    FI_L,    FI_M,    FI_N,    FI_O,
    // P     Q        R        S        T        U        V        W
    FI_P,    FI_Q,    FI_R,    FI_S,    FI_T,    FI_U,    FI_V,    FI_W,
    // X     Y        Z        [        \        ]        ^        _
    FI_X,    FI_Y,    FI_Z,    FI_8,    FI_PLUS, FI_9,    FI_DIAE, FI_MINS,
    // `     a        b        c        d        e        f        g
    FI_ACUT, FI_A,    FI_B,    FI_C,    FI_D,    FI_E,    FI_F,    FI_G,
    // h     i        j        k        l        m        n        o
    FI_H,    FI_I,    FI_J,    FI_K,    FI_L,    FI_M,    FI_N,    FI_O,
    // p     q        r        s        t        u        v        w
    FI_P,    FI_Q,    FI_R,    FI_S,    FI_T,    FI_U,    FI_V,    FI_W,
    // x     y        z        {        |        }        ~        DEL
    FI_X,    FI_Y,    FI_Z,    FI_7,    FI_LABK, FI_0,    FI_DIAE, KC_DEL
};
