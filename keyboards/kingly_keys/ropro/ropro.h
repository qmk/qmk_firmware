/* Copyright 2019 Garret G. (TheRoyalSweatshirt)
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
 * 
 * Note:  Matrix is a little wacky with the rotary encoder click mapping being
 * on the opposite side of the board.  Remember to pay attention to 
 * the 13th column where the lone key mapped for rotary encoder click (K132).
*/

#pragma once

#include "quantum.h"

#define LAYOUT( \
         K10, K20, K30, K40, K50, K60, K70, K80, K90, K100, K110, K120, \
         K11, K21, K31, K41, K51, K61, K71, K81, K91, K101, K111, K121, \
    K132, K12, K22, K32, K42, K52, K62, K72, K82, K92, K102, K112, K122, \
    K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, K103, K113, K123, \
    K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, K104, K114, K124, \
    K05, K15, K25, K35, K45, K55, K65, K75, K85, K95, K105, K115, K125 \
) { \
    { KC_NO, K10, K20, K30, K40, K50, K60, K70, K80, K90, K100, K110, K120, KC_NO }, \
    { KC_NO, K11, K21, K31, K41, K51, K61, K71, K81, K91, K101, K111, K121, KC_NO }, \
    { KC_NO, K12, K22, K32, K42, K52, K62, K72, K82, K92, K102, K112, K122, K132  }, \
    { K03,   K13, K23, K33, K43, K53, K63, K73, K83, K93, K103, K113, K123, KC_NO }, \
    { K04,   K14, K24, K34, K44, K54, K64, K74, K84, K94, K104, K114, K124, KC_NO }, \
    { K05,   K15, K25, K35, K45, K55, K65, K75, K85, K95, K105, K115, K125, KC_NO } \
}
