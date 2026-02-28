/* Copyright 2025 QMK
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

// Sendstring lookup tables for Ergo‑L layouts

#pragma once

#include "send_string.h"
#include "keymap_ergol.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 0, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 1, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
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
    KC_SPC,  EL_1DK,  EL_QUOT, EL_9,    EL_4,    EL_5,    EL_7,    EL_QUOT,
    // (     )        *        +        ,        -        .        /
    EL_S,    EL_E,    EL_8,    EL_EQL,  EL_COMM, EL_MINS, EL_DOT,  EL_SLSH,
    // 0     1        2        3        4        5        6        7
    EL_0,    EL_1,    EL_2,    EL_3,    EL_4,    EL_5,    EL_6,    EL_7,
    // 8     9        :        ;        <        =        >        ?
    EL_8,    EL_9,    EL_DOT,  EL_COMM, EL_LABK, EL_EQL,  EL_LABK, EL_MINS,
    // @     A        B        C        D        E        F        G
    EL_0,    EL_A,    EL_B,    EL_C,    EL_D,    EL_E,    EL_F,    EL_G,
    // H     I        J        K        L        M        N        O
    EL_H,    EL_I,    EL_J,    EL_K,    EL_L,    EL_M,    EL_N,    EL_O,
    // P     Q        R        S        T        U        V        W
    EL_P,    EL_Q,    EL_R,    EL_S,    EL_T,    EL_U,    EL_V,    EL_W,
    // X     Y        Z        [        \        ]        ^        _
    EL_X,    EL_Y,    EL_Z,    EL_LBRC, EL_BSLS, EL_RBRC, EL_6,    EL_SLSH,
    // `     a        b        c        d        e        f        g
    EL_GRV,  EL_A,    EL_B,    EL_C,    EL_D,    EL_E,    EL_F,    EL_G,
    // h     i        j        k        l        m        n        o
    EL_H,    EL_I,    EL_J,    EL_K,    EL_L,    EL_M,    EL_N,    EL_O,
    // p     q        r        s        t        u        v        w
    EL_P,    EL_Q,    EL_R,    EL_S,    EL_T,    EL_U,    EL_V,    EL_W,
    // x     y        z        {        |        }        ~        DEL
    EL_X,    EL_Y,    EL_Z,    EL_LBRC, EL_BSLS, EL_RBRC, EL_GRV,  KC_DEL
};
