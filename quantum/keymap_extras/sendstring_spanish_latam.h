/* Copyright 2022 Hugo Muñoz
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

// Sendstring lookup tables for Latin American Spanish layouts

#pragma once

#include "keymap_spanish_latam.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 1, 1, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 0, 1, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 1, 0, 1, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 1, 0)
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
    KC_SPC,  SP_1,    SP_2,    SP_3,    SP_4,    SP_5,    SP_6,    SP_QUOT,
    // (     )        *        +        ,        -        .        /
    SP_8,    SP_9,    SP_PLUS, SP_PLUS, SP_COMM, SP_MINS, SP_DOT,  SP_7,
    // 0     1        2        3        4        5        6        7
    SP_0,    SP_1,    SP_2,    SP_3,    SP_4,    SP_5,    SP_6,    SP_7,
    // 8     9        :        ;        <        =        >        ?
    SP_8,    SP_9,    SP_COLN, SP_SCLN, SP_LABK, SP_0,    SP_LABK, SP_QUES,
    // @     A        B        C        D        E        F        G
    SP_Q,    SP_A,    SP_B,    SP_C,    SP_D,    SP_E,    SP_F,    SP_G,
    // H     I        J        K        L        M        N        O
    SP_H,    SP_I,    SP_J,    SP_K,    SP_L,    SP_M,    SP_N,    SP_O,
    // P     Q        R        S        T        U        V        W
    SP_P,    SP_Q,    SP_R,    SP_S,    SP_T,    SP_U,    SP_V,    SP_W,
    // X     Y        Z        [        \        ]        ^        _
    SP_X,    SP_Y,    SP_Z,    SP_LCBR, SP_QUOT, SP_RCBR, SP_LCBR, SP_MINS,
    // `     a        b        c        d        e        f        g
    SP_RCBR, SP_A,    SP_B,    SP_C,    SP_D,    SP_E,    SP_F,    SP_G,
    // h     i        j        k        l        m        n        o
    SP_H,    SP_I,    SP_J,    SP_K,    SP_L,    SP_M,    SP_N,    SP_O,
    // p     q        r        s        t        u        v        w
    SP_P,    SP_Q,    SP_R,    SP_S,    SP_T,    SP_U,    SP_V,    SP_W,
    // x     y        z        {        |        }        ~        DEL
    SP_X,    SP_Y,    SP_Z,    SP_LCBR, SP_PIPE, SP_RCBR, SP_PLUS, KC_DEL
};



    