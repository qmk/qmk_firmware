/* Copyright 2019 Torben Hoffmann
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

// Sendstring lookup tables for Norman layouts

#pragma once

#include "keymap_norman.h"

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
    KC_SPC,  KC_1,    KC_QUOT, KC_3,    KC_4,    KC_5,    KC_7,    KC_QUOT,
    // (     )        *        +        ,        -        .        /
    KC_9,    KC_0,    KC_8,    KC_EQL,  KC_COMM, KC_MINS, KC_DOT,  KC_SLSH,
    // 0     1        2        3        4        5        6        7
    KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // 8     9        :        ;        <        =        >        ?
    KC_8,    KC_9,    NM_SCLN, NM_SCLN, KC_COMM, KC_EQL,  KC_DOT,  KC_SLSH,
    // @     A        B        C        D        E        F        G
    KC_2,    NM_A,    NM_B,    NM_C,    NM_D,    NM_E,    NM_F,    NM_G,
    // H     I        J        K        L        M        N        O
    NM_H,    NM_I,    NM_J,    NM_K,    NM_L,    NM_M,    NM_N,    NM_O,
    // P     Q        R        S        T        U        V        W
    NM_P,    NM_Q,    NM_R,    NM_S,    NM_T,    NM_U,    NM_V,    NM_W,
    // X     Y        Z        [        \        ]        ^        _
    NM_X,    NM_Y,    NM_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_6,    KC_MINS,
    // `     a        b        c        d        e        f        g
    KC_GRV,  NM_A,    NM_B,    NM_C,    NM_D,    NM_E,    NM_F,    NM_G,
    // h     i        j        k        l        m        n        o
    NM_H,    NM_I,    NM_J,    NM_K,    NM_L,    NM_M,    NM_N,    NM_O,
    // p     q        r        s        t        u        v        w
    NM_P,    NM_Q,    NM_R,    NM_S,    NM_T,    NM_U,    NM_V,    NM_W,
    // x     y        z        {        |        }        ~        DEL
    NM_X,    NM_Y,    NM_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV,  KC_DEL
};
