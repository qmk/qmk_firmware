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

// Sendstring lookup tables for Programmer Dvorak layouts

#pragma once

#include "keymap_dvp.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 1, 0, 0, 1, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 1, 0, 1, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 1, 0, 1, 0)
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
    KC_SPC,  DP_EXLM, DP_QUOT, DP_HASH, DP_DLR,  DP_AMPR, DP_AMPR, DP_QUOT,
    // (     )        *        +        ,        -        .        /
    DP_LPRN, DP_RPRN, DP_ASTR, DP_PLUS, DP_COMM, DP_MINS, DP_DOT,  DP_SLSH,
    // 0     1        2        3        4        5        6        7
    DP_ASTR, DP_LPRN, DP_RPRN, DP_RCBR, DP_PLUS, DP_LCBR, DP_RBRC, DP_LBRC,
    // 8     9        :        ;        <        =        >        ?
    DP_EXLM, DP_EQL,  DP_SCLN, DP_SCLN, DP_COMM, DP_EQL,  DP_DOT,  DP_SLSH,
    // @     A        B        C        D        E        F        G
    DP_AT,   DP_A,    DP_B,    DP_C,    DP_D,    DP_E,    DP_F,    DP_G,
    // H     I        J        K        L        M        N        O
    DP_H,    DP_I,    DP_J,    DP_K,    DP_L,    DP_M,    DP_N,    DP_O,
    // P     Q        R        S        T        U        V        W
    DP_P,    DP_Q,    DP_R,    DP_S,    DP_T,    DP_U,    DP_V,    DP_W,
    // X     Y        Z        [        \        ]        ^        _
    DP_X,    DP_Y,    DP_Z,    DP_LBRC, DP_BSLS, DP_RBRC, DP_AT,   DP_MINS,
    // `     a        b        c        d        e        f        g
    DP_HASH, DP_A,    DP_B,    DP_C,    DP_D,    DP_E,    DP_F,    DP_G,
    // h     i        j        k        l        m        n        o
    DP_H,    DP_I,    DP_J,    DP_K,    DP_L,    DP_M,    DP_N,    DP_O,
    // p     q        r        s        t        u        v        w
    DP_P,    DP_Q,    DP_R,    DP_S,    DP_T,    DP_U,    DP_V,    DP_W,
    // x     y        z        {        |        }        ~        DEL
    DP_X,    DP_Y,    DP_Z,    DP_LCBR, DP_BSLS, DP_RCBR, DP_DLR,  KC_DEL
};
