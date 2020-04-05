/* Copyright 2018 Jacob Jerrell
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

// Sendstring lookup tables for Workman ZXCVM layouts
#pragma once

#include "keymap_workman_zxcvm.h"

// clang-format off

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
    KC_SPC,  WK_1,    WK_QUOT, WK_3,    WK_4,    WK_5,    WK_7,    WK_QUOT,
    // (     )        *        +        ,        -        .        /
    WK_9,    WK_0,    WK_8,    WK_EQL,  WK_COMM, WK_MINS, WK_DOT,  WK_SLSH,
    // 0     1        2        3        4        5        6        7
    WK_0,    WK_1,    WK_2,    WK_3,    WK_4,    WK_5,    WK_6,    WK_7,
    // 8     9        :        ;        <        =        >        ?
    WK_8,    WK_9,    WK_SCLN, WK_SCLN, WK_COMM, WK_EQL,  WK_DOT,  WK_SLSH,
    // @     A        B        C        D        E        F        G
    WK_2,    WK_A,    WK_B,    WK_C,    WK_D,    WK_E,    WK_F,    WK_G,
    // H     I        J        K        L        M        N        O
    WK_H,    WK_I,    WK_J,    WK_K,    WK_L,    WK_M,    WK_N,    WK_O,
    // P     Q        R        S        T        U        V        W
    WK_P,    WK_Q,    WK_R,    WK_S,    WK_T,    WK_U,    WK_V,    WK_W,
    // X     Y        Z        [        \        ]        ^        _
    WK_X,    WK_Y,    WK_Z,    WK_LBRC, WK_BSLS, WK_RBRC, WK_6,    WK_MINS,
    // `     a        b        c        d        e        f        g
    WK_GRV,  WK_A,    WK_B,    WK_C,    WK_D,    WK_E,    WK_F,    WK_G,
    // h     i        j        k        l        m        n        o
    WK_H,    WK_I,    WK_J,    WK_K,    WK_L,    WK_M,    WK_N,    WK_O,
    // p     q        r        s        t        u        v        w
    WK_P,    WK_Q,    WK_R,    WK_S,    WK_T,    WK_U,    WK_V,    WK_W,
    // x     y        z        {        |        }        ~        DEL
    WK_X,    WK_Y,    WK_Z,    WK_LBRC, WK_BSLS, WK_RBRC, WK_GRV,  KC_DEL
};
