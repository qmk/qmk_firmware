/* Copyright 2016 Jack Humbert
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

// Sendstring lookup tables for Colemak layouts

#pragma once

#include "keymap_colemak.h"

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
    KC_SPC,  CM_1,    CM_QUOT, CM_3,    CM_4,    CM_5,    CM_7,    CM_QUOT,
    // (     )        *        +        ,        -        .        /
    CM_9,    CM_0,    CM_8,    CM_EQL,  CM_COMM, CM_MINS, CM_DOT,  CM_SLSH,
    // 0     1        2        3        4        5        6        7
    CM_0,    CM_1,    CM_2,    CM_3,    CM_4,    CM_5,    CM_6,    CM_7,
    // 8     9        :        ;        <        =        >        ?
    CM_8,    CM_9,    CM_SCLN, CM_SCLN, CM_COMM, CM_EQL,  CM_DOT,  CM_SLSH,
    // @     A        B        C        D        E        F        G
    CM_2,    CM_A,    CM_B,    CM_C,    CM_D,    CM_E,    CM_F,    CM_G,
    // H     I        J        K        L        M        N        O
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    // P     Q        R        S        T        U        V        W
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    // X     Y        Z        [        \        ]        ^        _
    CM_X,    CM_Y,    CM_Z,    CM_LBRC, CM_BSLS, CM_RBRC, CM_6,    CM_MINS,
    // `     a        b        c        d        e        f        g
    CM_GRV,  CM_A,    CM_B,    CM_C,    CM_D,    CM_E,    CM_F,    CM_G,
    // h     i        j        k        l        m        n        o
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    // p     q        r        s        t        u        v        w
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    // x     y        z        {        |        }        ~        DEL
    CM_X,    CM_Y,    CM_Z,    CM_LBRC, CM_BSLS, CM_RBRC, CM_GRV,  KC_DEL
};
