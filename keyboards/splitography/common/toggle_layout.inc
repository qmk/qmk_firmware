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

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │   F  │   E  │   D  │      │      │      │   /  │   7  │   8  │   9  │   *  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │  GUI │   C  │   B  │   A  │      │      │      │   .  │   4  │   5  │   6  │   -  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │   #  │   G  │   \  │      │      │      │   ,  │   1  │   2  │   3  │   +  │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │ Space│   0  │   =  │
//                             │  f() │ Space│   =  │   0  │
//                             └──────┴──────┴──────┴──────┘

[_TTNUMBER] = LAYOUT(
    XXXXXXX, KC_F,    MT_E,    KC_D,    XXXXXXX, _______, _______, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR,
    OS_GUI,  GT_C,    AT_B,    ST_A,    XXXXXXX, _______, _______, TD_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS,
    XXXXXXX, KC_HASH, SM_G,    KC_BSLS, XXXXXXX, _______, _______, TD_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS,
#if defined(THUMB_0)
                                        TT_ESC,  KC_SPC,  KC_0,    KC_EQL
#else
                                        TT_ESC,  KC_SPC,  KC_EQL,  KC_0
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
//                             │  f() │      │   +  │      │
//                             └──────┴──────┴──────┴──────┘

[_TTFNCKEY] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12 ,
    OS_GUI,  OS_CTL,  OS_ALT,  OS_SFT,  XXXXXXX, _______, _______, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11 ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10 ,
                                        TT_ESC,  XXXXXXX, KC_PLUS, XXXXXXX
),

// ....................................................................... Regex

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │   .  │   *  │   &  │   ~  │      │      │   `  │   [  │   ^  │   ]  │      │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │   <  │   %  │   >  │   ?  │      │      │   │  │   (  │   $  │   )  │      │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │   :  │   @  │   !  │   /  │      │      │   \  │   {  │   #  │   }  │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │   =  │   +  │ Space│
//                             └──────┴──────┴──────┴──────┘

[_TTREGEX] = LAYOUT(
    _______, KC_DOT,  KC_ASTR, KC_AMPR, KC_TILD, _______, _______, KC_GRV,  KC_LBRC, KC_CIRC, KC_RBRC, _______,
    _______, KC_LT,   KC_PERC, KC_GT,   KC_QUES, _______, _______, KC_PIPE, KC_LPRN, KC_DLR,  KC_RPRN, _______,
    _______, KC_COLN, KC_AT,   KC_EXLM, KC_SLSH, _______, _______, KC_BSLS, KC_LCBR, KC_HASH, KC_RCBR, _______,
                                        TT_ESC,  KC_EQL,  KC_PLUS, KC_SPC
),

// ............................................................ Navigation Layer

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │      │      │      │      │      │      │      │ Home │  Up  │  End │ PgUp │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │  GUI │ Ctrl │  Alt │ Shift│      │      │      │      │ Left │ Down │ Right│ PgDn │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │      │      │      │      │      │      │      │      │      │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │      │      │      │
//                             └──────┴──────┴──────┴──────┘

[_TTCURSOR] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    OS_GUI,  OS_CTL,  OS_ALT,  OS_SFT,  XXXXXXX, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        TT_ESC,  XXXXXXX, XXXXXXX, XXXXXXX
),

// ............................................................... Mouse Actions

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │      │      │      │      │      │      │      │ Left │  Up  │ Right│  Up  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │ Btn3 │ Btn2 │ Btn1 │      │      │      │      │ Left │ Down │ Right│ Down │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │      │      │      │      │      │      │      │      │      │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │      │      │      │
//                             └──────┴──────┴──────┴──────┘

[_TTMOUSE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,
    XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1, XXXXXXX, _______, _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        TT_ESC,  XXXXXXX, XXXXXXX, XXXXXXX
),
