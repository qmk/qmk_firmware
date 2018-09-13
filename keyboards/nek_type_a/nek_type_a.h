/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#ifndef NEK_TYPE_A_H
#define NEK_TYPE_A_H

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
         L12, L13,      L15, L16, L17, \
    L21, L22, L23, L24, L25, L26, L27, \
    L31, L32, L33, L34, L35, L36, \
    L41, L42, L43, L44, L45, L46, \
    L51, L52, L53, L54, L55, L56, \
    L61, L62, L63,      L65 \
) \
{ \
    { KC_NO,   L12,   L13, KC_NO,   L15,   L16,   L17 }, \
    {   L21,   L22,   L23,   L24,   L25,   L26,   L27 }, \
    {   L31,   L32,   L33,   L34,   L35,   L36, KC_NO }, \
    {   L41,   L42,   L43,   L44,   L45,   L46, KC_NO }, \
    {   L51,   L52,   L53,   L54,   L55,   L56, KC_NO }, \
    {   L61,   L62,   L63, KC_NO,   L65, KC_NO, KC_NO }, \
}
#endif
