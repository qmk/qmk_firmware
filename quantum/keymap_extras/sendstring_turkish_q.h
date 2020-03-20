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

// Sendstring lookup tables for Turkish Q layouts

#pragma once

#include "keymap_turkish_q.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 0, 0, 0, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 0, 1, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 1, 1, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 1, 1, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0),
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
    KC_SPC,  TR_1,    TR_DQUO, TR_3,    TR_4,    TR_5,    TR_6,    TR_2,
    // (     )        *        +        ,        -        .        /
    TR_8,    TR_9,    TR_ASTR, TR_4,    TR_COMM, TR_MINS, TR_DOT,  TR_7,
    // 0     1        2        3        4        5        6        7
    TR_0,    TR_1,    TR_2,    TR_3,    TR_4,    TR_5,    TR_6,    TR_7,
    // 8     9        :        ;        <        =        >        ?
    TR_8,    TR_9,    TR_DOT,  TR_COMM, TR_LABK, TR_0,    TR_LABK, TR_ASTR,
    // @     A        B        C        D        E        F        G
    TR_Q,    TR_A,    TR_B,    TR_C,    TR_D,    TR_E,    TR_F,    TR_G,
    // H     I        J        K        L        M        N        O
    TR_H,    TR_I,    TR_J,    TR_K,    TR_L,    TR_M,    TR_N,    TR_O,
    // P     Q        R        S        T        U        V        W
    TR_P,    TR_Q,    TR_R,    TR_S,    TR_T,    TR_U,    TR_V,    TR_W,
    // X     Y        Z        [        \        ]        ^        _
    TR_X,    TR_Y,    TR_Z,    TR_8,    TR_ASTR, TR_9,    TR_3,    TR_MINS,
    // `     a        b        c        d        e        f        g
    TR_COMM, TR_A,    TR_B,    TR_C,    TR_D,    TR_E,    TR_F,    TR_G,
    // h     i        j        k        l        m        n        o
    TR_H,    TR_I,    TR_J,    TR_K,    TR_L,    TR_M,    TR_N,    TR_O,
    // p     q        r        s        t        u        v        w
    TR_P,    TR_Q,    TR_R,    TR_S,    TR_T,    TR_U,    TR_V,    TR_W,
    // x     y        z        {        |        }        ~        DEL
    TR_X,    TR_Y,    TR_Z,    TR_7,    TR_MINS, TR_0,    TR_UDIA, KC_DEL
};
