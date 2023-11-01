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

// Sendstring lookup tables for Lithuanian QWERTY layouts

#pragma once

#include "send_string.h"
#include "keymap_lithuanian_qwerty.h"

// clang-format off

const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 0, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(0, 0, 1, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 1, 0, 0),
    KCLUT_ENTRY(1, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 1, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
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
    KC_SPC,  LT_1,    LT_QUOT, LT_3,    LT_4,    LT_5,    LT_7,    LT_QUOT,
    // (     )        *        +        ,        -        .        /
    LT_9,    LT_0,    LT_8,    LT_ZCAR, LT_COMM, LT_MINS, LT_DOT,  LT_SLSH,
    // 0     1        2        3        4        5        6        7
    LT_0,    LT_AOGO, LT_CCAR, LT_EOGO, LT_EDOT, LT_IOGO, LT_SCAR, LT_UOGO,
    // 8     9        :        ;        <        =        >        ?
    LT_UMAC, LT_9,    LT_SCLN, LT_SCLN, LT_COMM, LT_PLUS, LT_DOT,  LT_SLSH,
    // @     A        B        C        D        E        F        G
    LT_CCAR, LT_A,    LT_B,    LT_C,    LT_D,    LT_E,    LT_F,    LT_G,
    // H     I        J        K        L        M        N        O
    LT_H,    LT_I,    LT_J,    LT_K,    LT_L,    LT_M,    LT_N,    LT_O,
    // P     Q        R        S        T        U        V        W
    LT_P,    LT_Q,    LT_R,    LT_S,    LT_T,    LT_U,    LT_V,    LT_W,
    // X     Y        Z        [        \        ]        ^        _
    LT_X,    LT_Y,    LT_Z,    LT_LBRC, LT_BSLS, LT_RBRC, LT_SCAR, LT_MINS,
    // `     a        b        c        d        e        f        g
    LT_GRV,  LT_A,    LT_B,    LT_C,    LT_D,    LT_E,    LT_F,    LT_G,
    // h     i        j        k        l        m        n        o
    LT_H,    LT_I,    LT_J,    LT_K,    LT_L,    LT_M,    LT_N,    LT_O,
    // p     q        r        s        t        u        v        w
    LT_P,    LT_Q,    LT_R,    LT_S,    LT_T,    LT_U,    LT_V,    LT_W,
    // x     y        z        {        |        }        ~        DEL
    LT_X,    LT_Y,    LT_Z,    LT_LBRC, LT_BSLS, LT_RBRC, LT_GRV,  KC_DEL
};
