/* Copyright 2021 Danny Nguyen <danny@keeb.io>
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

#include "dsp40.h"
#include "quantum.h"

#define LAYOUT_ortho_4x12( \
    KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KA9, KA10, KA11, KA12, \
    KB1, KB2, KB3, KB4, KB5, KB6, KB7, KB8, KB9, KB10, KB11, KB12, \
    KC1, KC2, KC3, KC4, KC5, KC6, KC7, KC8, KC9, KC10, KC11, KC12, \
    KD1, KD2, KD3, KD4, KD5, KD6, KD7, KD8, KD9, KD10, KD11, KD12 \
) \
{ \
    { KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KA9, KA10, KA11, KA12 }, \
    { KB1, KB2, KB3, KB4, KB5, KB6, KB7, KB8, KB9, KB10, KB11, KB12 }, \
    { KC1, KC2, KC3, KC4, KC5, KC6, KC7, KC8, KC9, KC10, KC11, KC12 }, \
    { KD1, KD2, KD3, KD4, KD5, KD6, KD7, KD8, KD9, KD10, KD11, KD12 } \
}

#define LAYOUT( \
    KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KA9, KA10, KA11, KA12, \
    KB1, KB2, KB3, KB4, KB5, KB6, KB7, KB8, KB9, KB10,       KB12, \
         KC2, KC3, KC4, KC5, KC6, KC7, KC8, KC9, KC10, KC11, KC12, \
    KD1, KD2, KD3,      KD5,           KD8,      KD10, KD11, KD12 \
) \
{ \
    { KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KA9, KA10, KA11, KA12 }, \
    { KB1, KB2, KB3, KB4, KB5, KB6, KB7, KB8, KB9, KB10, KC_NO, KB12 }, \
    { KC_NO, KC2, KC3, KC4, KC5, KC6, KC7, KC8, KC9, KC10, KC11, KC12 }, \
    { KD1, KD2, KD3, KC_NO, KD5, KC_NO, KC_NO, KD8, KC_NO, KD10, KD11, KD12 } \
}

#define LAYOUT_40_staggered LAYOUT
