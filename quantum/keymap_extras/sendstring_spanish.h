/* Copyright 2018 Daniel Rodríguez
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

// Sendstring lookup tables for Spanish layouts

#pragma once

#include "keymap_spanish.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 0, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 1, 1, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 1, 0, 0, 0, 0),
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
    KC_SPC,  ES_1,    ES_2,    ES_3,    ES_4,    ES_5,    ES_6,    ES_QUOT,
    // (     )        *        +        ,        -        .        /
    ES_8,    ES_9,    ES_PLUS, ES_PLUS, ES_COMM, ES_MINS, ES_DOT,  ES_7,
    // 0     1        2        3        4        5        6        7
    ES_0,    ES_1,    ES_2,    ES_3,    ES_4,    ES_5,    ES_6,    ES_7,
    // 8     9        :        ;        <        =        >        ?
    ES_8,    ES_9,    ES_DOT,  ES_COMM, ES_LABK, ES_0,    ES_LABK, ES_QUOT,
    // @     A        B        C        D        E        F        G
    ES_2,    ES_A,    ES_B,    ES_C,    ES_D,    ES_E,    ES_F,    ES_G,
    // H     I        J        K        L        M        N        O
    ES_H,    ES_I,    ES_J,    ES_K,    ES_L,    ES_M,    ES_N,    ES_O,
    // P     Q        R        S        T        U        V        W
    ES_P,    ES_Q,    ES_R,    ES_S,    ES_T,    ES_U,    ES_V,    ES_W,
    // X     Y        Z        [        \        ]        ^        _
    ES_X,    ES_Y,    ES_Z,    ES_GRV,  ES_MORD, ES_PLUS, ES_GRV,  ES_MINS,
    // `     a        b        c        d        e        f        g
    ES_GRV,  ES_A,    ES_B,    ES_C,    ES_D,    ES_E,    ES_F,    ES_G,
    // h     i        j        k        l        m        n        o
    ES_H,    ES_I,    ES_J,    ES_K,    ES_L,    ES_M,    ES_N,    ES_O,
    // p     q        r        s        t        u        v        w
    ES_P,    ES_Q,    ES_R,    ES_S,    ES_T,    ES_U,    ES_V,    ES_W,
    // x     y        z        {        |        }        ~        DEL
    ES_X,    ES_Y,    ES_Z,    ES_ACUT, ES_1,    ES_CCED, ES_4, KC_DEL
};
