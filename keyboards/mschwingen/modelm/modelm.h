/*
 * Copyright 2020 Michael Schwingen

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

extern void update_layer_leds(void);

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 * The first section contains "names" for physical keys of the keyboard
 * and defines their position on the board.
 * The second section defines position of the keys on the switch matrix
 * (where COLUMNS and ROWS crosses). */

/* universla layout for both 101 and 102-key versions */
#define LAYOUT( \
    K5A,      K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M,   K5N, K5O, K5P, \
    \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N,   K4O, K4P, K4Q,   K4R, K4S, K4T, K4U, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,   K3O, K3P, K3Q,   K3R, K3S, K3T, K3U, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N,                    K2O, K2P, K2Q, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L,      K1M,        K1N,        K1O, K1P, K1Q, K1R, \
    K0A,      K0B,                K0C,                     K0D,      K0E,   K0F, K0G, K0H,   K0I,      K0J       \
) \
    {/* COL0    ............                           COL7 */		\
    { K0D  , KC_NO, KC_NO, K5O  , K5N  , KC_NO, KC_NO, K0B   }, /* ROW0 */ \
    { K0F  , K5P  , K1R  , K3U  , K3P  , K4P  , KC_NO, K1N   }, \
    { K4U  , K4T  , K1Q  , K3T  , K3Q  , K4Q  , K2Q  , K0J   }, \
    { K0H  , K4S  , K1P  , K3S  , K5M  , K4O  , K2P  , K0I   }, \
    { K0G  , K4R  , K1O  , K3R  , K5L  , K3O  , K2O  , KC_NO }, \
    { K1L  , K2M  , K2K  , K3K  , K4K  , K4L  , K3L  , K2L   }, \
    { KC_NO, K1K  , K2J  , K3J  , K4J  , K5I  , K5H  , KC_NO }, \
    { KC_NO, K1J  , K2I  , K3I  , K4I  , K4M  , K3M  , K5G   }, \
    { K1H  , K1I  , K2H  , K3H  , K4H  , K4G  , K3G  , K2G   }, \
    { K0C  , K2N  , K3N  , KC_NO, K5K  , K5J  , K4N  , K5F   }, \
    { K1G  , K1F  , K2E  , K3E  , K4E  , K4F  , K3F  , K2F   }, \
    { KC_NO, K1E  , K2D  , K3D  , K4D  , K5C  , K5D  , K5E   }, \
    { KC_NO, K1D  , K2C  , K3C  , K4C  , K5B  , K2A  , K1B   }, \
    { KC_NO, K1C  , K2B  , K3B  , K4B  , K4A  , K3A  , K5A   }, \
    { KC_NO, K1M  , KC_NO, KC_NO, KC_NO, KC_NO, K1A  , KC_NO }, \
    { KC_NO, K0E  , KC_NO, KC_NO, KC_NO, K0A  , KC_NO, KC_NO }, /* ROW15 */ \
}

