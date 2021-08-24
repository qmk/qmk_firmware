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

// Sendstring lookup tables for Latvian layouts

#pragma once

#include "keymap_latvian.h"

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
    KC_SPC,  LV_1,    LV_QUOT, LV_3,    LV_4,    LV_5,    LV_7,    LV_QUOT,
    // (     )        *        +        ,        -        .        /
    LV_9,    LV_0,    LV_8,    LV_EQL,  LV_COMM, LV_MINS, LV_DOT,  LV_SLSH,
    // 0     1        2        3        4        5        6        7
    LV_0,    LV_1,    LV_2,    LV_3,    LV_4,    LV_5,    LV_6,    LV_7,
    // 8     9        :        ;        <        =        >        ?
    LV_8,    LV_9,    LV_SCLN, LV_SCLN, LV_COMM, LV_EQL,  LV_DOT,  LV_SLSH,
    // @     A        B        C        D        E        F        G
    LV_2,    LV_A,    LV_B,    LV_C,    LV_D,    LV_E,    LV_F,    LV_G,
    // H     I        J        K        L        M        N        O
    LV_H,    LV_I,    LV_J,    LV_K,    LV_L,    LV_M,    LV_N,    LV_O,
    // P     Q        R        S        T        U        V        W
    LV_P,    LV_Q,    LV_R,    LV_S,    LV_T,    LV_U,    LV_V,    LV_W,
    // X     Y        Z        [        \        ]        ^        _
    LV_X,    LV_Y,    LV_Z,    LV_LBRC, LV_BSLS, LV_RBRC, LV_6,    LV_MINS,
    // `     a        b        c        d        e        f        g
    LV_GRV,  LV_A,    LV_B,    LV_C,    LV_D,    LV_E,    LV_F,    LV_G,
    // h     i        j        k        l        m        n        o
    LV_H,    LV_I,    LV_J,    LV_K,    LV_L,    LV_M,    LV_N,    LV_O,
    // p     q        r        s        t        u        v        w
    LV_P,    LV_Q,    LV_R,    LV_S,    LV_T,    LV_U,    LV_V,    LV_W,
    // x     y        z        {        |        }        ~        DEL
    LV_X,    LV_Y,    LV_Z,    LV_LBRC, LV_BSLS, LV_RBRC, LV_GRV,  KC_DEL
};
