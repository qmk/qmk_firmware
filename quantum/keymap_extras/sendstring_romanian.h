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

// Sendstring lookup tables for Romanian layouts

#pragma once

#include "keymap_romanian.h"
#include "quantum"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 0, 0, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 0, 1, 1, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 1, 0, 1, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 0, 1, 1, 0)
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
    KC_SPC,  RO_1,    RO_TCOM, RO_3,    RO_4,    RO_5,    RO_7,    RO_TCOM,
    // (     )        *        +        ,        -        .        /
    RO_9,    RO_0,    RO_8,    RO_EQL,  RO_COMM, RO_MINS, RO_DOT,  RO_SLSH,
    // 0     1        2        3        4        5        6        7
    RO_0,    RO_1,    RO_2,    RO_3,    RO_4,    RO_5,    RO_6,    RO_7,
    // 8     9        :        ;        <        =        >        ?
    RO_8,    RO_9,    RO_DOT,  RO_COMM, RO_COMM, RO_EQL,  RO_DOT,  RO_SLSH,
    // @     A        B        C        D        E        F        G
    RO_2,    RO_A,    RO_B,    RO_C,    RO_D,    RO_E,    RO_F,    RO_G,
    // H     I        J        K        L        M        N        O
    RO_H,    RO_I,    RO_J,    RO_K,    RO_L,    RO_M,    RO_N,    RO_O,
    // P     Q        R        S        T        U        V        W
    RO_P,    RO_Q,    RO_R,    RO_S,    RO_T,    RO_U,    RO_V,    RO_W,
    // X     Y        Z        [        \        ]        ^        _
    RO_X,    RO_Y,    RO_Z,    RO_ABRV, RO_BSLS, RO_ICIR, RO_6,    RO_MINS,
    // `     a        b        c        d        e        f        g
    RO_DLQU, RO_A,    RO_B,    RO_C,    RO_D,    RO_E,    RO_F,    RO_G,
    // h     i        j        k        l        m        n        o
    RO_H,    RO_I,    RO_J,    RO_K,    RO_L,    RO_M,    RO_N,    RO_O,
    // p     q        r        s        t        u        v        w
    RO_P,    RO_Q,    RO_R,    RO_S,    RO_T,    RO_U,    RO_V,    RO_W,
    // x     y        z        {        |        }        ~        DEL
    RO_X,    RO_Y,    RO_Z,    RO_ABRV, RO_BSLS, RO_ICIR, RO_DLQU, KC_DEL
};
