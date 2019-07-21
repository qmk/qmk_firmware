/* Copyright 2018 Jonathan Nifenecker
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

// Sendstring lookup tables for BÉPO layouts

#pragma once

#include "keymap_bepo.h"

const bool ascii_to_shift_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0,
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

    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1,
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
    KC_SPC,  BP_DCRC, BP_DQOT, BP_DLR,  BP_DLR,  BP_PERC, BP_P,    BP_APOS,
    // (     )        *        +        ,        -        .        /
    BP_LPRN, BP_RPRN, BP_ASTR, BP_PLUS, BP_COMM, BP_MINS, BP_DOT,  BP_SLSH,
    // 0     1        2        3        4        5        6        7
    BP_ASTR, BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, BP_AT,   BP_PLUS,
    // 8     9        :        ;        <        =        >        ?
    BP_MINS, BP_SLSH, BP_DOT,  BP_COMM, BP_LGIL, BP_EQL,  BP_RGIL, BP_APOS,
    // @     A        B        C        D        E        F        G
    BP_AT,   BP_A,    BP_B,    BP_C,    BP_D,    BP_E,    BP_F,    BP_G,
    // H     I        J        K        L        M        N        O
    BP_H,    BP_I,    BP_J,    BP_K,    BP_L,    BP_M,    BP_N,    BP_O,
    // P     Q        R        S        T        U        V        W
    BP_P,    BP_Q,    BP_R,    BP_S,    BP_T,    BP_U,    BP_V,    BP_W,
    // X     Y        Z        [        \        ]        ^        _
    BP_X,    BP_Y,    BP_Z,    BP_LPRN, BP_AGRV, BP_RPRN, BP_AT,   KC_SPC,
    // `     a        b        c        d        e        f        g
    BP_PERC, BP_A,    BP_B,    BP_C,    BP_D,    BP_E,    BP_F,    BP_G,
    // h     i        j        k        l        m        n        o
    BP_H,    BP_I,    BP_J,    BP_K,    BP_L,    BP_M,    BP_N,    BP_O,
    // p     q        r        s        t        u        v        w
    BP_P,    BP_Q,    BP_R,    BP_S,    BP_T,    BP_U,    BP_V,    BP_W,
    // x     y        z        {        |        }        ~        DEL
    BP_X,    BP_Y,    BP_Z,    BP_Y,    BP_B,    BP_X,    BP_K,    KC_DEL
};
