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

// Sendstring lookup tables for Danish layouts

#pragma once

#include "keymap_danish.h"

// clang-format off

const bool ascii_to_shift_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 1, 1, 1, 0, 1, 1, 0,
    1, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

const bool ascii_to_altgr_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 0
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
    KC_SPC,  DK_1,    DK_2,    DK_3,    DK_4,    DK_5,    DK_6,    DK_QUOT,
    // (     )        *        +        ,        -        .        /
    DK_8,    DK_9,    DK_QUOT, DK_PLUS, DK_COMM, DK_MINS, DK_DOT,  DK_7,
    // 0     1        2        3        4        5        6        7
    DK_0,    DK_1,    DK_2,    DK_3,    DK_4,    DK_5,    DK_6,    DK_7,
    // 8     9        :        ;        <        =        >        ?
    DK_8,    DK_9,    DK_DOT,  DK_COMM, DK_LABK, DK_0,    DK_LABK, DK_PLUS,
    // @     A        B        C        D        E        F        G
    DK_2,    DK_A,    DK_B,    DK_C,    DK_D,    DK_E,    DK_F,    DK_G,
    // H     I        J        K        L        M        N        O
    DK_H,    DK_I,    DK_J,    DK_K,    DK_L,    DK_M,    DK_N,    DK_O,
    // P     Q        R        S        T        U        V        W
    DK_P,    DK_Q,    DK_R,    DK_S,    DK_T,    DK_U,    DK_V,    DK_W,
    // X     Y        Z        [        \        ]        ^        _
    DK_X,    DK_Y,    DK_Z,    DK_8,    DK_LABK, DK_9,    DK_DIAE, DK_MINS,
    // `     a        b        c        d        e        f        g
    DK_ACUT, DK_A,    DK_B,    DK_C,    DK_D,    DK_E,    DK_F,    DK_G,
    // h     i        j        k        l        m        n        o
    DK_H,    DK_I,    DK_J,    DK_K,    DK_L,    DK_M,    DK_N,    DK_O,
    // p     q        r        s        t        u        v        w
    DK_P,    DK_Q,    DK_R,    DK_S,    DK_T,    DK_U,    DK_V,    DK_W,
    // x     y        z        {        |        }        ~        DEL
    DK_X,    DK_Y,    DK_Z,    DK_7,    DK_ACUT, DK_0,    DK_DIAE, KC_DEL
};
