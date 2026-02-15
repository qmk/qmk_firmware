/* Copyright 2026 Arthur Frangyan <https://github.com/ArthurFrangyan>
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

#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}, {7,5}},
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}, {6,6}, {7,6}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}, {6,7}, {7,7}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}, {6,8}, {7,8}},
    {{0,9}, {1,9}, {7,9}, {2,9}, {3,9}, {4,9}, {5,9}, {6,9}},
    /* Right hand, matrix positions */
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}, {6,2}, {7,2}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}},
    {{0,4}, {1,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {1,4}},
};
#endif

/*
#define ___ KC_NO 
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07,                         R57, R56, R55, R54, R53, R52, R51, R50,\
    L10, L11, L12, L13, L14, L15, L16, L17,                         R67, R66, R65, R64, R63, R62, R61, R60,\
    L20, L21, L22, L23, L24, L25, L26,                                   R76, R75, R74, R73, R72, R71, R70,\
    L30, L31, L32, L33, L34, L35, L36, E37, L47,               R96, E87, R86, R85, R84, R83, R82, R81, R80,\
                   L40, L41, L43, L44, L45, L46,               R95, R94, R93, R92, R91, R90\
    ) \
    { \
        { L00, L01, L02, L03, L04, L05, L06, L07 }, \
        { L10, L11, L12, L13, L14, L15, L16, L17 }, \
        { L20, L21, L22, L23, L24, L25, L26, ___ }, \
        { L30, L31, L32, L33, L34, L35, L36, E37 }, \
        { L40, L41, ___, L43, L44, L45, L46, L47 }, \
        \
        { R50, R51, R52, R53, R54, R55, R56, R57 },\
        { R60, R61, R62, R63, R64, R65, R66, R67 }, \
        { R70, R71, R72, R73, R74, R75, R76, ___ }, \
        { R80, R81, R82, R83, R84, R85, R86, E87 }, \
        { R90, R91, R92, R93, R94, R95, R96, ___ } \
    }
*/