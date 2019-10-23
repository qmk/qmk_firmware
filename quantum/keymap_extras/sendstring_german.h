/* Copyright 2018 Patrick Hener
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

// Sendstring lookup tables for German layouts

#pragma once

#include "keymap_german.h"

const bool ascii_to_shift_lut[128] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                                              0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const bool ascii_to_altgr_lut[128] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0};

const uint8_t ascii_to_keycode_lut[128] PROGMEM = {
    // NUL   SOH      STX      ETX      EOT      ENQ      ACK      BEL
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // BS    TAB      LF       VT       FF       CR       SO       SI
    KC_BSPC, KC_TAB, KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // DLE   DC1      DC2      DC3      DC4      NAK      SYN      ETB
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // CAN   EM       SUB      ESC      FS       GS       RS       US
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    //       !        "        #        $        %        &        '
    KC_SPC, DE_1, DE_2, DE_HASH, DE_4, DE_5, DE_6, DE_HASH,
    // (     )        *        +        ,        -        .        /
    DE_8, DE_9, DE_PLUS, DE_PLUS, DE_COMM, DE_MINS, DE_DOT, DE_7,
    // 0     1        2        3        4        5        6        7
    DE_0, DE_1, DE_2, DE_3, DE_4, DE_5, DE_6, DE_7,
    // 8     9        :        ;        <        =        >        ?
    DE_8, DE_9, DE_DOT, DE_COMM, DE_LESS, DE_0, DE_LESS, DE_SS,
    // @     A        B        C        D        E        F        G
    DE_Q, DE_A, DE_B, DE_C, DE_D, DE_E, DE_F, DE_G,
    // H     I        J        K        L        M        N        O
    DE_H, DE_I, DE_J, DE_K, DE_L, DE_M, DE_N, DE_O,
    // P     Q        R        S        T        U        V        W
    DE_P, DE_Q, DE_R, DE_S, DE_T, DE_U, DE_V, DE_W,
    // X     Y        Z        [        \        ]        ^        _
    DE_X, DE_Y, DE_Z, DE_8, DE_SS, DE_9, DE_CIRC, DE_MINS,
    // `     a        b        c        d        e        f        g
    DE_ACUT, DE_A, DE_B, DE_C, DE_D, DE_E, DE_F, DE_G,
    // h     i        j        k        l        m        n        o
    DE_H, DE_I, DE_J, DE_K, DE_L, DE_M, DE_N, DE_O,
    // p     q        r        s        t        u        v        w
    DE_P, DE_Q, DE_R, DE_S, DE_T, DE_U, DE_V, DE_W,
    // x     y        z        {        |        }        ~        DEL
    DE_X, DE_Y, DE_Z, DE_7, DE_LESS, DE_0, DE_PLUS, KC_DEL};
