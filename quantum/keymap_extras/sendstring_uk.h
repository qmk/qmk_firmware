/* Copyright 2019 Rys Sommefeldt
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

// Sendstring lookup tables for UK layouts

#pragma once

#include "keymap_uk.h"

const bool ascii_to_shift_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 1, 1, 0, 1, 1, 1, 0,
    1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 1, 1,
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
    UK_SPC,  UK_1,    UK_2,    UK_HASH, UK_4,    UK_5,    UK_7,    UK_QUOT,
    // (     )        *        +        ,        -        .        /
    UK_9,    UK_0,    UK_8,    UK_EQL,  UK_COMM, UK_MINS, UK_DOT,  UK_SLSH,
    // 0     1        2        3        4        5        6        7
    UK_0,    UK_1,    UK_2,    UK_3,    UK_4,    UK_5,    UK_6,    UK_7,
    // 8     9        :        ;        <        =        >        ?
    UK_8,    UK_9,    UK_SCLN, UK_SCLN, UK_COMM, UK_EQL,  UK_DOT,  UK_SLSH,
    // @     A        B        C        D        E        F        G
    UK_QUOT, UK_A,    UK_B,    UK_C,    UK_D,    UK_E,    UK_F,    UK_G,
    // H     I        J        K        L        M        N        O
    UK_H,    UK_I,    UK_J,    UK_K,    UK_L,    UK_M,    UK_N,    UK_O,
    // P     Q        R        S        T        U        V        W
    UK_P,    UK_Q,    UK_R,    UK_S,    UK_T,    UK_U,    UK_V,    UK_W,
    // X     Y        Z        [        \        ]        ^        _
    UK_X,    UK_Y,    UK_Z,    UK_LBRC, UK_BSLS, UK_RBRC, UK_6,    UK_MINS,
    // `     a        b        c        d        e        f        g
    UK_GRV,  UK_A,    UK_B,    UK_C,    UK_D,    UK_E,    UK_F,    UK_G,
    // h     i        j        k        l        m        n        o
    UK_H,    UK_I,    UK_J,    UK_K,    UK_L,    UK_M,    UK_N,    UK_O,
    // p     q        r        s        t        u        v        w
    UK_P,    UK_Q,    UK_R,    UK_S,    UK_T,    UK_U,    UK_V,    UK_W,
    // x     y        z        {        |        }        ~        DEL
    UK_X,    UK_Y,    UK_Z,    UK_LBRC, UK_BSLS, UK_RBRC, UK_HASH, KC_DEL
};
