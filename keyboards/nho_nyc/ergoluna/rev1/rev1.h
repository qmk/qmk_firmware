/*
 * Copyright 2020 fruitkt
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

#include "ergoluna.h"
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#ifndef FLIP_HALF
/*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox(                                                  \
                                                                                \
    L17,L16,L15,L14,L13,L12,L11,               R11,R12,R13,R14,R15,R16,R17,     \
    L27,L26,L25,L24,L23,L22,L21,               R21,R22,R23,R24,R25,R26,R27,     \
    L37,L36,L35,L34,L33,L32,                       R32,R33,R34,R35,R36,R37,     \
    L47,L46,L45,L44,L43,L42,L41,               R41,R42,R43,R44,R45,R46,R47,     \
    L57,L56,L55,L54,L53,                               R53,R54,R55,R56,R57,     \
                            L66,L65,       R65,R66,                             \
                                L64,       R64,                                 \
                        L62,L61,L63,       R63,R61,R62 )                        \
                                                                                \
   /* matrix positions */                                                       \
   {                                                                            \
    {   L17,L16,L15,L14,L13,L12,L11  }, \
    {   L27,L26,L25,L24,L23,L22,L21  }, \
    {   L37,L36,L35,L34,L33,L32,KC_NO}, \
    {   L47,L46,L45,L44,L43,L42,L41  }, \
    { L57,L56,L55,L54,L53,KC_NO,KC_NO}, \
    { KC_NO,L66,L65,L64,L63,L62,L61  }, \
    {   R17,R16,R15,R14,R13,R12,R11  }, \
    {   R27,R26,R25,R24,R23,R22,R21  }, \
    {   R37,R36,R35,R34,R33,R32,KC_NO}, \
    {   R47,R46,R45,R44,R43,R42,R41  }, \
    { R57,R56,R55,R54,R53,KC_NO,KC_NO}, \
    { KC_NO,R66,R65,R64,R63,R62,R61  }  \
   }
   
/*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_1(                                              \
                                                                               \
    L17,L16,L15,L14,L13,L12,L11,               R11,R12,R13,R14,R15,R16,R17,    \
    L27,L26,L25,L24,L23,L22,L21,               R21,R22,R23,R24,R25,R26,R27,    \
    L37,L36,L35,L34,L33,L32,                       R32,R33,R34,R35,R36,R37,    \
    L47,L46,L45,L44,L43,L42,L41,               R41,R42,R43,R44,R45,R46,R47,    \
    L57,L56,L55,L54,L53,                               R53,R54,R55,R56,R57,    \
                            L66,L65,       R65,R66,                            \
                            L51,L64,       R64,                                \
                        L62,L61,L63,       R63,R61,R62 )                       \
                                                                               \
   /* matrix positions */                                                      \
   {                                                                           \
    {   L17,L16,L15,L14,L13,L12,L11  }, \
    {   L27,L26,L25,L24,L23,L22,L21  }, \
    {   L37,L36,L35,L34,L33,L32,KC_NO}, \
    {   L47,L46,L45,L44,L43,L42,L41  }, \
    {   L57,L56,L55,L54,L53,KC_NO,L51}, \
    { KC_NO,L66,L65,L64,L63,L62,L61  }, \
    {   R17,R16,R15,R14,R13,R12,R11  }, \
    {   R27,R26,R25,R24,R23,R22,R21  }, \
    {   R37,R36,R35,R34,R33,R32,KC_NO}, \
    {   R47,R46,R45,R44,R43,R42,R41  }, \
    { R57,R56,R55,R54,R53,KC_NO,KC_NO}, \
    { KC_NO,R66,R65,R64,R63,R62,R61  }  \
   }
   
 /*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_2(                                                  \
                                                                                \
    L17,L16,L15,L14,L13,L12,L11,               R11,R12,R13,R14,R15,R16,R17,     \
    L27,L26,L25,L24,L23,L22,L21,               R21,R22,R23,R24,R25,R26,R27,     \
    L37,L36,L35,L34,L33,L32,                       R32,R33,R34,R35,R36,R37,     \
    L47,L46,L45,L44,L43,L42,L41,               R41,R42,R43,R44,R45,R46,R47,     \
    L57,L56,L55,L54,L53,                               R53,R54,R55,R56,R57,     \
                            L66,L65,       R65,R66,                             \
                                L64,       R64,R51,                             \
                        L62,L61,L63,       R63,R61,R62 )                        \
                                                                                \
   /* matrix positions */                                                       \
   {                                                                            \
    {   L17,L16,L15,L14,L13,L12,L11  }, \
    {   L27,L26,L25,L24,L23,L22,L21  }, \
    {   L37,L36,L35,L34,L33,L32,KC_NO}, \
    {   L47,L46,L45,L44,L43,L42,L41  }, \
    { L57,L56,L55,L54,L53,KC_NO,KC_NO}, \
    { KC_NO,L66,L65,L64,L63,L62,L61  }, \
    {   R17,R16,R15,R14,R13,R12,R11  }, \
    {   R27,R26,R25,R24,R23,R22,R21  }, \
    {   R37,R36,R35,R34,R33,R32,KC_NO}, \
    {   R47,R46,R45,R44,R43,R42,R41  }, \
    { R57,R56,R55,R54,R53,KC_NO,R51  }, \
    { KC_NO,R66,R65,R64,R63,R62,R61  }  \
   }
 /*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
 
 #define LAYOUT_ergodox_3(                                                  \
                                                                                \
    L17,L16,L15,L14,L13,L12,L11,               R11,R12,R13,R14,R15,R16,R17,     \
    L27,L26,L25,L24,L23,L22,L21,               R21,R22,R23,R24,R25,R26,R27,     \
    L37,L36,L35,L34,L33,L32,                       R32,R33,R34,R35,R36,R37,     \
    L47,L46,L45,L44,L43,L42,L41,               R41,R42,R43,R44,R45,R46,R47,     \
    L57,L56,L55,L54,L53,                               R53,R54,R55,R56,R57,     \
                            L66,L65,       R65,R66,                             \
                            L51,L64,       R64,R51,                             \
                        L62,L61,L63,       R63,R61,R62 )                        \
                                                                                \
   /* matrix positions */                                                       \
   {                                                                            \
    {   L17,L16,L15,L14,L13,L12,L11  }, \
    {   L27,L26,L25,L24,L23,L22,L21  }, \
    {   L37,L36,L35,L34,L33,L32,KC_NO}, \
    {   L47,L46,L45,L44,L43,L42,L41  }, \
    { L57,L56,L55,L54,L53,KC_NO,L51  }, \
    { KC_NO,L66,L65,L64,L63,L62,L61  }, \
    {   R17,R16,R15,R14,R13,R12,R11  }, \
    {   R27,R26,R25,R24,R23,R22,R21  }, \
    {   R37,R36,R35,R34,R33,R32,KC_NO}, \
    {   R47,R46,R45,R44,R43,R42,R41  }, \
    { R57,R56,R55,R54,R53,KC-NO,R51  }, \
    { KC_NO,R66,R65,R64,R63,R62,R61  }  \
   }
 /*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
 #define LAYOUT_ergodox_all(                                                  \
                                                                                \
    L17,L16,L15,L14,L13,L12,L11,               R11,R12,R13,R14,R15,R16,R17,     \
    L27,L26,L25,L24,L23,L22,L21,               R21,R22,R23,R24,R25,R26,R27,     \
    L37,L36,L35,L34,L33,L32,                       R32,R33,R34,R35,R36,R37,     \
    L47,L46,L45,L44,L43,L42,L41,               R41,R42,R43,R44,R45,R46,R47,     \
    L57,L56,L55,L54,L53,                               R53,R54,R55,R56,R57,     \
                            L66,L65,       R65,R66,                             \
                        L52,L51,L64,       R64,R51,R52,                         \
                        L62,L61,L63,       R63,R61,R62 )                        \
                                                                                \
   /* matrix positions */                                                       \
   {                                                                            \
    {   L17,L16,L15,L14,L13,L12,L11  }, \
    {   L27,L26,L25,L24,L23,L22,L21  }, \
    {   L37,L36,L35,L34,L33,L32,KC_NO}, \
    {   L47,L46,L45,L44,L43,L42,L41  }, \
    {   L57,L56,L55,L54,L53,L42,L51  }, \
    { KC_NO,L66,L65,L64,L63,L62,L61  }, \
    {   R17,R16,R15,R14,R13,R12,R11  }, \
    {   R27,R26,R25,R24,R23,R22,R21  }, \
    {   R37,R36,R35,R34,R33,R32,KC_NO}, \
    {   R47,R46,R45,R44,R43,R42,R41  }, \
    {   R57,R56,R55,R54,R53,R52,R51  }, \
    { KC_NO,R66,R65,R64,R63,R62,R61  }  \
   }
#endif
