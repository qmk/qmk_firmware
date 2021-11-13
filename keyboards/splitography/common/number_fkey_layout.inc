/* Copyright 2021 Alexis Jeandeau
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

#pragma once

// clang-format off
// ......................................................... Number Keypad Layer

// .-----------------------------------------------------------------------------------.
// |      |   F  |   E  |   D  |      |      |      |   /  |   7  |   8  |   9  |   *  |
// |-----------------------------------------------------------------------------------|
// |  GUI |   C  |   B  |   A  |      |      |      |   .  |   4  |   5  |   6  |   -  |
// |-----------------------------------------------------------------------------------|
// |      |   X  |   G  |   \  |      |      |      |   ,  |   1  |   2  |   3  |   +  |
// |-----------------------------------------------------------------------------------|
// |                           |      |  f() |  0/= |  =/0 |                           |
// '-----------------------------------------------------------------------------------'

[_NUMBER] = LAYOUT(
    XXXXXXX, KC_F,    MT_E,    KC_D,    XXXXXXX, _______, _______, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR,
    OS_GUI,  GT_C,    AT_B,    ST_A,    XXXXXXX, _______, _______, TD_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS,
    XXXXXXX, KC_X,    SM_G,    KC_BSLS, XXXXXXX, _______, _______, TD_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS,
#if defined(THUMB_0)
                                        _______, _______, KC_0,    KC_EQL
#else
                                        _______, _______, KC_EQL,  KC_0
#endif
),

// ............................................................... Function Keys

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │      │      │      │      │      │      │      │  F7  │  F8  │  F9  │  F12 │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │  GUI │ Ctrl │  Alt │ Shift│      │      │      │      │  F4  │  F5  │  F6  │  F11 │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │      │      │      │      │      │      │  F1  │  F2  │  F3  │  F10 │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │      │      │  f() │      │
//                             └──────┴──────┴──────┴──────┘

[_FNCKEY] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12 ,
    OS_GUI,  OS_CTL,  OS_ALT,  OS_SFT,  XXXXXXX, _______, _______, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11 ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10 ,
                                        _______, _______, _______, _______
),
