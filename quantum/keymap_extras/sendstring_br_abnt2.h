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

// Sendstring lookup tables for Brazilian (ABNT2) layouts

#pragma once

#include "keymap_br_abnt2.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 0, 1, 0, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 0, 0)
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
    KC_SPC,  BR_1,    BR_QUOT, BR_3,    BR_4,    BR_5,    BR_7,    BR_QUOT,
    // (     )        *        +        ,        -        .        /
    BR_9,    BR_0,    BR_8,    BR_EQL,  BR_COMM, BR_MINS, BR_DOT,  BR_SLSH,
    // 0     1        2        3        4        5        6        7
    BR_0,    BR_1,    BR_2,    BR_3,    BR_4,    BR_5,    BR_6,    BR_7,
    // 8     9        :        ;        <        =        >        ?
    BR_8,    BR_9,    BR_SCLN, BR_SCLN, BR_COMM, BR_EQL,  BR_DOT,  BR_SLSH,
    // @     A        B        C        D        E        F        G
    BR_2,    BR_A,    BR_B,    BR_C,    BR_D,    BR_E,    BR_F,    BR_G,
    // H     I        J        K        L        M        N        O
    BR_H,    BR_I,    BR_J,    BR_K,    BR_L,    BR_M,    BR_N,    BR_O,
    // P     Q        R        S        T        U        V        W
    BR_P,    BR_Q,    BR_R,    BR_S,    BR_T,    BR_U,    BR_V,    BR_W,
    // X     Y        Z        [        \        ]        ^        _
    BR_X,    BR_Y,    BR_Z,    BR_LBRC, BR_BSLS, BR_RBRC, BR_TILD, BR_MINS,
    // `     a        b        c        d        e        f        g
    BR_ACUT, BR_A,    BR_B,    BR_C,    BR_D,    BR_E,    BR_F,    BR_G,
    // h     i        j        k        l        m        n        o
    BR_H,    BR_I,    BR_J,    BR_K,    BR_L,    BR_M,    BR_N,    BR_O,
    // p     q        r        s        t        u        v        w
    BR_P,    BR_Q,    BR_R,    BR_S,    BR_T,    BR_U,    BR_V,    BR_W,
    // x     y        z        {        |        }        ~        DEL
    BR_X,    BR_Y,    BR_Z,    BR_LBRC, BR_BSLS, BR_RBRC, BR_TILD, KC_DEL
};
