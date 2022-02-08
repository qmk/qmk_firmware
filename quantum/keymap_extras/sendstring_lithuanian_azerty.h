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

// Sendstring lookup tables for Lithuanian ĄŽERTY layouts

#pragma once

#include "keymap_lithuanian_azerty.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 0, 0, 0, 0, 1, 0),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 1, 0)
};

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(0, 0, 1, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 0, 0)
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
    KC_SPC,  LT_EXLM, LT_EDOT, LT_SLSH, LT_SCLN, LT_X,    LT_DOT,  LT_QUES,
    // (     )        *        +        ,        -        .        /
    LT_LPRN, LT_RPRN, LT_EQL,  LT_QUES, LT_COMM, LT_MINS, LT_DOT,  LT_SLSH,
    // 0     1        2        3        4        5        6        7
    LT_RPRN, LT_EXLM, LT_MINS, LT_SLSH, LT_SCLN, LT_COLN, LT_COMM, LT_DOT,
    // 8     9        :        ;        <        =        >        ?
    LT_EQL,  LT_LPRN, LT_COLN, LT_SCLN, LT_LABK, LT_EQL,  LT_LABK, LT_QUES,
    // @     A        B        C        D        E        F        G
    LT_EXLM, LT_A,    LT_B,    LT_C,    LT_D,    LT_E,    LT_F,    LT_G,
    // H     I        J        K        L        M        N        O
    LT_H,    LT_I,    LT_J,    LT_K,    LT_L,    LT_M,    LT_N,    LT_O,
    // P     Q        R        S        T        U        V        W
    LT_P,    LT_Q,    LT_R,    LT_S,    LT_T,    LT_U,    LT_V,    LT_W,
    // X     Y        Z        [        \        ]        ^        _
    LT_X,    LT_Y,    LT_Z,    LT_LPRN, LT_EOGO, LT_RPRN, LT_COMM, LT_MINS,
    // `     a        b        c        d        e        f        g
    LT_GRV,  LT_A,    LT_B,    LT_C,    LT_D,    LT_E,    LT_F,    LT_G,
    // h     i        j        k        l        m        n        o
    LT_H,    LT_I,    LT_J,    LT_K,    LT_L,    LT_M,    LT_N,    LT_O,
    // p     q        r        s        t        u        v        w
    LT_P,    LT_Q,    LT_R,    LT_S,    LT_T,    LT_U,    LT_V,    LT_W,
    // x     y        z        {        |        }        ~        DEL
    LT_X,    LT_Y,    LT_Z,    LT_IOGO, LT_Q,    LT_W,    LT_GRV,  KC_DEL
};
