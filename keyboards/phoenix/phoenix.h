/* Copyright 2019
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

inline void led_pin_on(uint8_t pin) { palSetPad(GPIOB, pin); };
inline void led_pin_off(uint8_t pin) { palClearPad(GPIOB, pin); };

inline void led1_on(void) { led_pin_on(8); };
inline void led2_on(void) { led_pin_on(5); };
inline void led3_on(void) { led_pin_on(6); };

inline void led1_off(void) { led_pin_off(8); };
inline void led2_off(void) { led_pin_off(5); };
inline void led3_off(void) { led_pin_off(6); };

#define LAYOUT_ergodox(                    \
    k00,k01,k02,k03,k04,k05,k06,           \
    k10,k11,k12,k13,k14,k15,k16,           \
    k20,k21,k22,k23,k24,k25,               \
    k30,k31,k32,k33,k34,k35,k36,           \
    k40,k41,k42,k43,k44,                   \
                            k55,k56,       \
                                k54,       \
                        k53,k52,k51,       \
                                           \
        k07,k08,k09,k0A,k0B,k0C,k0D,       \
        k17,k18,k19,k1A,k1B,k1C,k1D,       \
            k28,k29,k2A,k2B,k2C,k2D,       \
        k37,k38,k39,k3A,k3B,k3C,k3D,       \
                k49,k4A,k4B,k4C,k4D,       \
    k57,k58,                               \
    k59,                                   \
    k5C,k5B,k5A )                          \
                                           \
   /* matrix positions */                  \
   {                                       \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25 },      \
    { k30, k31, k32, k33, k34, k35, k36 }, \
    { k40, k41, k42, k43, k44 },           \
    { k53, k52, k51, k55, k56, k54 },      \
                                           \
    { k0D, k0C, k0B, k0A, k09, k08, k07 }, \
    { k1D, k1C, k1B, k1A, k19, k18, k17 }, \
    { k2D, k2C, k2B, k2A, k29, k28 },      \
    { k3D, k3C, k3B, k3A, k39, k38, k37 }, \
    { k4D, k4C, k4B, k4A, k49  },          \
    { k5A, k5B, k5C, k58, k57, k59 },      \
   }

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_pretty(                                           \
    L00,L01,L02,L03,L04,L05,L06,           R00,R01,R02,R03,R04,R05,R06,  \
    L10,L11,L12,L13,L14,L15,L16,           R10,R11,R12,R13,R14,R15,R16,  \
    L20,L21,L22,L23,L24,L25,                   R21,R22,R23,R24,R25,R26,  \
    L30,L31,L32,L33,L34,L35,L36,           R30,R31,R32,R33,R34,R35,R36,  \
    L40,L41,L42,L43,L44,                           R42,R43,R44,R45,R46,  \
                            L55,L56,   R50,R51,                          \
                                L54,   R52,                              \
                        L53,L52,L51,   R55,R54,R53 )                     \
                                          \
   /* matrix positions */                 \
    {                                     \
    { L00, L10, L02, L03, L04, L05, L06 },\
    { L10, L11, L12, L13, L14, L15, L16 },\
    { L20, L21, L22, L23, L24, L25 },     \
    { L30, L31, L32, L33, L34, L35, L36 },\
    { L40, L41, L42, L43, L44 },          \
    { L53, L52, L51, L55, L56, L54 },     \
                                          \
    { R00, R01, R02, R03, R04, R05, R06 },\
    { R10, R11, R12, R13, R14, R15, R16 },\
    { R20, R21, R22, R23, R24, R25 },     \
    { R30, R31, R32, R33, R34, R35, R36 },\
    { R40, R41, R42, R43, R44 },          \
    { R53, R54, R55, R51, R50, R52 },     \
    }
