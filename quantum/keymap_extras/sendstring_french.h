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

// Sendstring lookup tables for French (AZERTY) layouts

#pragma once

#include "keymap_french.h"

const bool ascii_to_shift_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

const bool ascii_to_altgr_lut[128] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
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
    KC_SPC,  FR_EXLM, FR_QUOT, FR_QUOT, FR_DLR,  FR_UGRV, FR_AMP,  FR_APOS,
    // (     )        *        +        ,        -        .        /
    FR_LPRN, FR_RPRN, FR_ASTR, FR_EQL,  FR_COMM, FR_MINS, FR_SCLN, FR_COLN,
    // 0     1        2        3        4        5        6        7
    FR_AGRV, FR_AMP,  FR_EACU, FR_QUOT, FR_APOS, FR_LPRN, FR_MINS, FR_EGRV,
    // 8     9        :        ;        <        =        >        ?
    FR_CCED, FR_AGRV, FR_COLN, FR_SCLN, FR_LESS, FR_EQL,  FR_LESS, FR_COMM,
    // @     A        B        C        D        E        F        G
    FR_AGRV, FR_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,
    // H     I        J        K        L        M        N        O
    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    FR_M,    KC_N,    KC_O,
    // P     Q        R        S        T        U        V        W
    KC_P,    FR_Q,    KC_R,    KC_S,    KC_T,    KC_U,    KC_V,    FR_W,
    // X     Y        Z        [        \        ]        ^        _
    KC_X,    KC_Y,    FR_Z,    FR_LPRN, FR_UNDS, FR_RPRN, FR_CCED, FR_UNDS,
    // `     a        b        c        d        e        f        g
    FR_EGRV, FR_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,
    // h     i        j        k        l        m        n        o
    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    FR_M,    KC_N,    KC_O,
    // p     q        r        s        t        u        v        w
    KC_P,    FR_Q,    KC_R,    KC_S,    KC_T,    KC_U,    KC_V,    FR_W,
    // x     y        z        {        |        }        ~        DEL
    KC_X,    KC_Y,    FR_Z,    FR_APOS, FR_MINS, FR_EQL,  FR_EACU, KC_DEL
};
