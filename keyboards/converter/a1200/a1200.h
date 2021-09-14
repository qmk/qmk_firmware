/* Copyright 2021 8bits4ever
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

#define _x_ KC_NO

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 * The first section contains "names" for physical keys of the keyboard
 * and defines their position on the board.
 * The second section defines position of the keys on the switch matrix 
 * (where COLUMNS and ROWS crosses). */

#define LAYOUT( \
    K5A,      K5B, K5C, K5D, K5E, K5F,      K5G, K5H, K5I, K5J, K5K,    \
    \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N,K4O,    K4P, K4Q,       K4R, K4S, K4T, K4U, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,                             K3R, K3S, K3T, K3U, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N, K2O,       K2P,        K2Q, K2R, K2S, K2T, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L,      K1M,       K0F, K0G, K0H,   K1O, K1P, K1Q, K1R, \
    K0A,      K0B,                K0C,                     K0D,      K0E,                        K0I,      K0J \
) \
{ \
/* "Q" */ { K3A,   K3B,   K3C,   K3D,   K3E,   K3F,  K3G,   K3H,  K3I,   K3J,   K3K,   K3L,   K3M,  K2O,   K0F,   K4P }, \
/* "A" */ { K2B,   K2C,   K2D,   K2E,   K2F,   K2G,  K2H,   K2I,  K2J,   K2K,   K2L,   K2M,   K2N,  K4P,   K0H,   K0B }, \
/* "Z" */ { K1B,   K1C,   K1D,   K1E,   K1F,   K1G,  K1H,   K1I,  K1J,   K1K,   K1L,   K4O,   K0C,  K4O,   K0G,   K0A }, \
/* PAD */ { K4U,   K2T,   K3T,   K2S,   K1Q,   K0J,  K3S,   K2R,  K1P,   K1R,   K3R,   K2Q,   K1O,  K0I,   K3U,   K1A }, \
/* "1" */ { K4A,   K4B,   K4C,   K4D,   K4E,   K4F,  K4G,   K4H,  K4I,   K4J,   K4K,   K4L,   K4M,  K4N,   K2P,   K2A }, \
/* 05 */  { _x_,   _x_,   _x_,   _x_,   _x_,   _x_,  _x_,   _x_,  _x_,   _x_,   _x_,   _x_,   _x_,  _x_,   _x_,   K1M }, \
/* FN  */ { K5A,   K4R,   K5B,   K5C,   K5D,   K5E,  K5F,   K4S,  K5G,   K4T,   K5H,   K5I,   K5J,  K5K,   K4Q,   K0D }, \
/* 07 */  { _x_,   _x_,   _x_,   _x_,   _x_,   _x_,  _x_,   _x_,  _x_,   _x_,   _x_,   _x_,   _x_,  _x_,   _x_,   K0E }, \
}
/*         A(15)  B(16)  C(17)  D(18)  E(19)  F(20) G(21)  H(22) I(23)  J(24)  K(25)  L(26)   M(27) N(28)  O(29)  P(30)       */
