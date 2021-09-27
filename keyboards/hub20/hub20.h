/* Copyright 2020 joshajohnson
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

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


    /* LAYOUT_all


     *     ┌───┬───┐ 
     *     │01 │02 │    
     * ┌───┼───┼───┼───┐
     * │10 │11 │12 │13 │
     * ├───┼───┼───┼───┤
     * │20 │21 │22 │23 │
     * ├───┼───┼───┼───┤
     * │30 │31 │32 │33 │
     * ├───┼───┼───┼───┤
     * │40 │41 │42 │43 │
     * ├───┼───┼───┼───┤
     * │50 │51 │52 │53 │
     * └───┴───┴───┴───┘
     */
#define LAYOUT_all(   \
      K01,      K02,    \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43, \
    K50, K51, K52, K53  \
) \
{ \
    { ___, K01, K02, ___, }, \
    { K10, K11, K12, K13, }, \
    { K20, K21, K22, K23, }, \
    { K30, K31, K32, K33, }, \
    { K40, K41, K42, K43, }, \
    { K50, K51, K52, K53, }, \
}

    /* LAYOUT_left_handed


     *     ┌───┬───┐ 
     *     │01 │02 │    
     * ┌───┼───┼───┼───┐
     * │10 │11 │12 │13 │
     * ├───┼───┼───┼───┤
     * │   │21 │22 │23 │
     * │20 ├───┼───┼───┤
     * │   │31 │32 │33 │
     * ├───┼───┼───┼───┤
     * │   │41 │42 │43 │
     * │40 ├───┼───┴───┤
     * │   │51 │  52   │
     * └───┴───┴───────┘
     */
#define LAYOUT_left_handed(   \
      K01,      K02,    \
    K10, K11, K12, K13, \
         K21, K22, K23, \
    K20, K31, K32, K33, \
         K41, K42, K43, \
    K40, K51, K52       \
) \
{ \
    { ___, K01, K02, ___, }, \
    { K10, K11, K12, K13, }, \
    { K20, K21, K22, K23, }, \
    { ___, K31, K32, K33, }, \
    { K40, K41, K42, K43, }, \
    { ___, K51, K52, ___, }, \
}


    /* LAYOUT_right_handed


     *     ┌───┬───┐ 
     *     │01 │02 │    
     * ┌───┼───┼───┼───┐
     * │10 │11 │12 │13 │
     * ├───┼───┼───┼───┤
     * │20 │21 │22 │   │
     * ├───┼───┼───┤23 │
     * │30 │31 │32 │   │
     * ├───┼───┼───┼───┤
     * │40 │41 │42 │   │
     * ├───┴───┼───┤43 │
     * │  50(not sure, confirm)   │52 │   │
     * └───────┴───┴───┘
     */
        //NOT TESTED, WAITING ENDORSEMENT FROM MANUFACTURER
#define LAYOUT_right_handed(   \
      K01,      K02,    \
    K10, K11, K12, K13, \
    K20, K21, K22,      \
    K30, K31, K32, K23, \
    K40, K41, K42,      \
    K50,      K52, K43  \
) \
{ \
    { ___, K01, K02, ___, }, \
    { K10, K11, K12, K13, }, \
    { K20, K21, K22, K23, }, \
    { K30, K31, K32, ___, }, \
    { K40, K41, K42, K43, }, \
    { K50, ___, K52, ___, }, \
}


