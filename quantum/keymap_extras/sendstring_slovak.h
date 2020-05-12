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

// Sendstring lookup tables for Slovak layouts

#pragma once

#include "keymap_slovak.h"
#include "quantum.h"

// clang-format off

const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 0, 1),
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

    KCLUT_ENTRY(0, 0, 0, 0, 1, 0, 0, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0)
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
    KC_SPC,  SK_SECT, SK_OCIR, SK_X,    SK_OCIR, SK_EQL,  SK_AMPR, SK_P,
    // (     )        *        +        ,        -        .        /
    SK_ADIA, SK_NCAR, SK_AMPR, SK_PLUS, SK_COMM, SK_MINS, SK_DOT,  SK_UACU,
    // 0     1        2        3        4        5        6        7
    SK_EACU, SK_PLUS, SK_LACU, SK_SCAR, SK_CCAR, SK_TACU, SK_ZCAR, SK_YACU,
    // 8     9        :        ;        <        =        >        ?
    SK_AACU, SK_IACU, SK_DOT,  SK_SCLN, SK_AMPR, SK_EQL,  SK_Y,    SK_COMM,
    // @     A        B        C        D        E        F        G
    SK_V,    SK_A,    SK_B,    SK_C,    SK_D,    SK_E,    SK_F,    SK_G,
    // H     I        J        K        L        M        N        O
    SK_H,    SK_I,    SK_J,    SK_K,    SK_L,    SK_M,    SK_N,    SK_O,
    // P     Q        R        S        T        U        V        W
    SK_P,    SK_Q,    SK_R,    SK_S,    SK_T,    SK_U,    SK_V,    SK_W,
    // X     Y        Z        [        \        ]        ^        _
    SK_X,    SK_Y,    SK_Z,    SK_F,    SK_Q,    SK_G,    SK_3,    SK_MINS,
    // `     a        b        c        d        e        f        g
    SK_7,    SK_A,    SK_B,    SK_C,    SK_D,    SK_E,    SK_F,    SK_G,
    // h     i        j        k        l        m        n        o
    SK_H,    SK_I,    SK_J,    SK_K,    SK_L,    SK_M,    SK_N,    SK_O,
    // p     q        r        s        t        u        v        w
    SK_P,    SK_Q,    SK_R,    SK_S,    SK_T,    SK_U,    SK_V,    SK_W,
    // x     y        z        {        |        }        ~        DEL
    SK_X,    SK_Y,    SK_Z,    SK_B,    SK_W,    SK_N,    SK_1,    KC_DEL
};
