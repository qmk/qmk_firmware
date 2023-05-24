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

// Sendstring lookup tables for macOS Italian ANSI layouts

#pragma once

#include "keymap_italian_mac_ansi.h"
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
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 0, 0)
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
    KCLUT_ENTRY(0, 0, 0, 1, 0, 1, 0, 0),
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
    KC_SPC,  IT_1,    IT_2,    IT_AGRV, IT_4,    IT_5,    IT_6,    IT_QUOT,
    // (     )        *        +        ,        -        .        /
    IT_8,    IT_9,    IT_PLUS, IT_PLUS, IT_COMM, IT_MINS, IT_DOT,  IT_7,
    // 0     1        2        3        4        5        6        7
    IT_0,    IT_1,    IT_2,    IT_3,    IT_4,    IT_5,    IT_6,    IT_7,
    // 8     9        :        ;        <        =        >        ?
    IT_8,    IT_9,    IT_DOT,  IT_COMM, IT_LABK, IT_0,    IT_LABK, IT_QUOT,
    // @     A        B        C        D        E        F        G
    IT_OGRV, IT_A,    IT_B,    IT_C,    IT_D,    IT_E,    IT_F,    IT_G,
    // H     I        J        K        L        M        N        O
    IT_H,    IT_I,    IT_J,    IT_K,    IT_L,    IT_M,    IT_N,    IT_O,
    // P     Q        R        S        T        U        V        W
    IT_P,    IT_Q,    IT_R,    IT_S,    IT_T,    IT_U,    IT_V,    IT_W,
    // X     Y        Z        [        \        ]        ^        _
    IT_X,    IT_Y,    IT_Z,    IT_EGRV, IT_BSLS, IT_PLUS, IT_IGRV, IT_MINS,
    // `     a        b        c        d        e        f        g
    IT_BSLS, IT_A,    IT_B,    IT_C,    IT_D,    IT_E,    IT_F,    IT_G,
    // h     i        j        k        l        m        n        o
    IT_H,    IT_I,    IT_J,    IT_K,    IT_L,    IT_M,    IT_N,    IT_O,
    // p     q        r        s        t        u        v        w
    IT_P,    IT_Q,    IT_R,    IT_S,    IT_T,    IT_U,    IT_V,    IT_W,
    // x     y        z        {        |        }        ~        DEL
    IT_X,    IT_Y,    IT_Z,    IT_EGRV, IT_BSLS, IT_PLUS, IT_5,    KC_DEL
};
