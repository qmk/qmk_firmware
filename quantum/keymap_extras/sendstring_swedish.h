/* Copyright 2019
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

// Sendstring lookup tables for Swedish layouts

#pragma once

#include "keymap_swedish.h"
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
    KC_SPC,  SE_1,    SE_2,    SE_3,    SE_4,    SE_5,    SE_6,    SE_QUOT,
    // (     )        *        +        ,        -        .        /
    SE_8,    SE_9,    SE_QUOT, SE_PLUS, SE_COMM, SE_MINS, SE_DOT,  SE_7,
    // 0     1        2        3        4        5        6        7
    SE_0,    SE_1,    SE_2,    SE_3,    SE_4,    SE_5,    SE_6,    SE_7,
    // 8     9        :        ;        <        =        >        ?
    SE_8,    SE_9,    SE_DOT,  SE_COMM, SE_LABK, SE_0,    SE_LABK, SE_PLUS,
    // @     A        B        C        D        E        F        G
    SE_2,    SE_A,    SE_B,    SE_C,    SE_D,    SE_E,    SE_F,    SE_G,
    // H     I        J        K        L        M        N        O
    SE_H,    SE_I,    SE_J,    SE_K,    SE_L,    SE_M,    SE_N,    SE_O,
    // P     Q        R        S        T        U        V        W
    SE_P,    SE_Q,    SE_R,    SE_S,    SE_T,    SE_U,    SE_V,    SE_W,
    // X     Y        Z        [        \        ]        ^        _
    SE_X,    SE_Y,    SE_Z,    SE_8,    SE_PLUS, SE_9,    SE_DIAE, SE_MINS,
    // `     a        b        c        d        e        f        g
    SE_ACUT, SE_A,    SE_B,    SE_C,    SE_D,    SE_E,    SE_F,    SE_G,
    // h     i        j        k        l        m        n        o
    SE_H,    SE_I,    SE_J,    SE_K,    SE_L,    SE_M,    SE_N,    SE_O,
    // p     q        r        s        t        u        v        w
    SE_P,    SE_Q,    SE_R,    SE_S,    SE_T,    SE_U,    SE_V,    SE_W,
    // x     y        z        {        |        }        ~        DEL
    SE_X,    SE_Y,    SE_Z,    SE_7,    SE_LABK, SE_0,    SE_DIAE, KC_DEL
};
