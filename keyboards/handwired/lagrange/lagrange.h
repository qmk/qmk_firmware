/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#if !defined(SPI_SS_PIN)
#    define SPI_SS_PIN B0
#endif

#define SPI_SCK_PIN B1
#define SPI_MOSI_PIN B2
#define SPI_MISO_PIN B3

#define LAYOUT(                                                                       \
    l00, l01, l02, l03, l04, l05,                       r05, r04, r03, r02, r01, r00, \
    l10, l11, l12, l13, l14, l15,                       r15, r14, r13, r12, r11, r10, \
    l20, l21, l22, l23, l24, l25,                       r25, r24, r23, r22, r21, r20, \
    l30, l31, l32, l33, l34, l35,                       r35, r34, r33, r32, r31, r30, \
    l40,      l42, l43, l44, l45, l46, l47,   r47, r46, r45, r44, r43, r42,      r40, \
                   l50, l51, l52,                       r52, r51, r50,                \
                        l70,                                 r70)                     \
    {                                                                                 \
        {l00, l01, l02, l03, l04, l05},                                               \
        {l10, l11, l12, l13, l14, l15},                                               \
        {l20, l21, l22, l23, l24, l25},                                               \
        {l30, l31, l32, l33, l34, l35},                                               \
        {l40, KC_NO, l42, l43, l44, l45},                                             \
        {KC_NO, KC_NO, KC_NO, l50, l51, l46},                                         \
        {KC_NO, KC_NO, KC_NO, l70, l52, l47},                                         \
                                                                                      \
        {r00, r01, r02, r03, r04, r05},                                               \
        {r10, r11, r12, r13, r14, r15},                                               \
        {r20, r21, r22, r23, r24, r25},                                               \
        {r30, r31, r32, r33, r34, r35},                                               \
        {r40, KC_NO, r42, r43, r44, r45},                                             \
        {KC_NO, KC_NO, KC_NO, r50, r51, r46},                                         \
        {KC_NO, KC_NO, KC_NO, r70, r52, r47}                                          \
    }
