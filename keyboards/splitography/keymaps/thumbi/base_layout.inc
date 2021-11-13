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
// ..................................................................... BEAKL I

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │   ;  │   Y  │   O  │   U  │   Z  │  Fn  │ Caps │   G  │   D  │   N  │   M  │   X  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   Q  │   H  │   E  │   A  │   .  │Cursor│ Mouse│   C  │   T  │   R  │   S  │   W  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   J  │   -  │   '  │   K  │   ,  │  Num │ Regex│   B  │   P  │   L  │   F  │   V  │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  Esc │   I  │ Space│ Bksp │
//                             └──────┴──────┴──────┴──────┘

[_BASE] = LAYOUT(
    KC_SCLN, KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    HOME_Q,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_R,  HOME_S,  HOME_W ,
    KC_J,    KC_MINS, KC_QUOT, KC_K,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
                                        LT_ESC,  LT_I,    TD_SPC,  LT_BSPC
),

[_SHIFT] = LAYOUT(
    KC_COLN, S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_Q), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_UNDS, KC_DQT,  S(KC_K), KC_EXLM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
                                        KC_ESC,  S(KC_I), KC_SPC,  KC_BSPC
),

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │   ;  │   Y  │   O  │   U  │   Z  │  Fn  │ Caps │   G  │   D  │   N  │   M  │   X  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   Q  │   H  │   E  │   A  │   ~  │Cursor│ Mouse│   C  │   T  │   R  │   S  │   W  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   J  │   -  │   '  │   K  │   `  │  Num │ Regex│   B  │   P  │   L  │   F  │   V  │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  Tab │  f() │ Enter│  Del │
//                             └──────┴──────┴──────┴──────┘
// thumb side lower case to avoid triggering same hand upper case

[_LSHIFT] = LAYOUT(
    KC_SCLN, KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    KC_Q,    KC_H,    KC_E,    KC_A,    TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    KC_J,    KC_MINS, KC_QUOT, KC_K,    KC_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
                                        KC_TAB,  _______, TD_ENT,  LT_DEL
),

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │   :  │   Y  │   O  │   U  │   Z  │  Fn  │ Caps │   G  │   D  │   N  │   M  │   X  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   Q  │   H  │   E  │   A  │   ?  │Cursor│ Mouse│   C  │   T  │   R  │   S  │   W  │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   J  │   _  │   "  │   K  │   /  │  Num │ Regex│   B  │   P  │   L  │   F  │   V  │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  Tab │   I  │  f() │  Del │
//                             └──────┴──────┴──────┴──────┘
// thumb side lower case to avoid triggering same hand upper case

[_RSHIFT] = LAYOUT(
    KC_COLN, S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    S(KC_Q), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_C,    KC_T,    KC_R,    KC_S,    KC_W   ,
    S(KC_J), KC_UNDS, KC_DQT,  S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
                                        KC_TAB,  S(KC_I), _______, KC_DEL
),

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │      │      │      │      │      │      │   *  │   [  │   ^  │   ]  │      │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │      │      │      │      │      │   │  │   (  │   $  │   )  │      │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │      │      │      │      │      │   /  │   {  │   #  │   }  │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │      │   \  │  Del |
//                             └──────┴──────┴──────┴──────┘

[_LSYMBOL] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, TD_ASTR, KC_LBRC, KC_CIRC, KC_RBRC, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_PIPE, KC_LPRN, KC_DLR,  KC_RPRN, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_SLSH, KC_LCBR, KC_HASH, KC_RCBR, XXXXXXX,
                                        _______, _______, KC_BSLS, SL_DEL
),

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │   :  │   .  │   *  │   &  │      │      │      │      │ Home │  Up  │  End │ PgUp │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │   ~  │   <  │   %  │   >  │   ?  │      │      │      │ Left │ Down │ Right│ PgDn │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │   +  │   @  │   !  │   /  │      │      │      │      │      │      │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │ ↑Tab │   =  │      │  f() │
//                             └──────┴──────┴──────┴──────┘

[_RSYMBOL] = LAYOUT(
    HS_COLN, KC_DOT,  KC_ASTR, KC_AMPR, XXXXXXX, _______, _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    SG_TILD, HS_LT,   SA_PERC, HS_GT,   KC_QUES, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    XXXXXXX, KC_PLUS, KC_AT,   KC_EXLM, KC_SLSH, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        SL_TAB,  HS_EQL,  _______, _______
),
