/* Copyright 2021 Joshua Cheung and Nathan Nguyen
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

#include "quantum.h"


// M = macro
// L = left
// R = right
// N = numpad
// A-E = row
// 0-9 = column
#define LAYOUT( \
    MA0, MA1, MA2, MA3, LA0, LA1, LA2, LA3, LA4, LA5, LA6,           RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, NA0, NA1, NA2, NA3, \
    MB0, MB1, MB2, MB3, LB0, LB1, LB2, LB3, LB4, LB5,           RB0, RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, NB0, NB1, NB2, NB3, \
    MC0, MC1, MC2, MC3, LC0, LC1, LC2, LC3, LC4, LC5,                RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8,      NC1, NC2, NC3, \
    MD0, MD1, MD2, MD3, LD0, LD1, LD2, LD3, LD4, LD5,                RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8,      ND1, ND2, ND3, \
    ME0, ME1, ME2, ME3, LE0, LE1, LE2, LE3, LE4,                          RE2, RE3, RE4, RE5, RE6, RE7, RE8,      NE1, NE2, NE3 \
    ) \
    { \
        { MA0, MA1, MA2, MA3, LA0, LA1, LA2, LA3, LA4, LA5, LA6, KC_NO, KC_NO }, \
        { MB0, MB1, MB2, MB3, LB0, LB1, LB2, LB3, LB4, LB5, KC_NO, KC_NO, KC_NO }, \
        { MC0, MC1, MC2, MC3, LC0, LC1, LC2, LC3, LC4, LC5, KC_NO, KC_NO, KC_NO }, \
        { MD0, MD1, MD2, MD3, LD0, LD1, LD2, LD3, LD4, LD5, KC_NO, KC_NO, KC_NO }, \
        { ME0, ME1, ME2, ME3, LE0, LE1, LE2, LE3, LE4, KC_NO, KC_NO, KC_NO, KC_NO }, \
        { KC_NO, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, NA0, NA1, NA2, NA3 }, \
        { RB0, RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, NB0, NB1, NB2, NB3 }, \
        { KC_NO, RC1, RC2, RC3, RC4, RC5, RC6, RC7, RC8, KC_NO, NC1, NC2, NC3 }, \
        { KC_NO, RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8, KC_NO, ND1, ND2, ND3 }, \
        { KC_NO, KC_NO, RE2, RE3, RE4, RE5, RE6, RE7, RE8, KC_NO, NE1, NE2, NE3 } \
    }
