/* Copyright 2021 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "foldkb.h"
#include "quantum.h"

#define LAYOUT( \
    LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, \
    LB1,      LB3, LB4, LB5, LB6, LB7, LB8, RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, \
    LC1,      LC3, LC4, LC5, LC6, LC7, LC8, RC1, RC2, RC3, RC4, RC5, RC6,      RC8, \
    LD1,      LD3, LD4, LD5, LD6, LD7, LD8, RD1, RD2, RD3, RD4, RD5, RD6,      RD8, \
    LE1,      LE3, LE4, LE5, LE6, LE7, LE8, RE1, RE2,      RE4, RE5, RE6,      RE8 \
  ) \
  { \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8 }, \
    { LB1, KC_NO, LB3, LB4, LB5, LB6, LB7, LB8 }, \
    { LC1, KC_NO, LC3, LC4, LC5, LC6, LC7, LC8 }, \
    { LD1, KC_NO, LD3, LD4, LD5, LD6, LD7, LD8 }, \
    { LE1, KC_NO, LE3, LE4, LE5, LE6, LE7, LE8 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO, RC8 }, \
    { RD1, RD2, RD3, RD4, RD5, RD6, KC_NO, RD8 }, \
    { RE1, RE2, KC_NO, RE4, RE5, RE6, KC_NO, RE8 }, \
  }
