/* Copyright 2021 JasonRen(biu)
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

#define LAYOUT( \
    L500,  L501,  L502,  L503,  L504,  L505,  L506,                       \
    L400,  L401,  L402,  L403,  L404,  L405,  L406,                       \
    L300,  L301,  L302,  L303,  L304,  L305,                              \
    L200,  L201,  L202,  L203,  L204,  L205,  L206,                       \
    L100,  L101,  L102,  L103,  L104,                                     \
                                              L005,   L006,               \
                                                      L004,               \
                                       L003,  L002,   L001,               \
                                                                          \
           R116,  R115,  R114,  R113,  R112,  R111,  R110,                \
           R106,  R105,  R104,  R103,  R102,  R101,  R100,                \
                  R905,  R904,  R903,  R902,  R901,  R900,                \
           R806,  R805,  R804,  R803,  R802,  R801,  R800,                \
                         R704,  R703,  R702,  R701,  R700,                \
    R606,  R605,                                                          \
    R604,                                                                 \
    R601,  R602,  R603                                                    \
) { \
	{ KC_NO, L001,  L002,  L003,  L004,  L005,  L006  }, \
	{ L100,  L101,  L102,  L103,  L104,  KC_NO, KC_NO }, \
	{ L200,  L201,  L202,  L203,  L204,  L205,  L206  }, \
	{ L300,  L301,  L302,  L303,  L304,  L305,  KC_NO }, \
	{ L400,  L401,  L402,  L403,  L404,  L405,  L406  }, \
	{ L500,  L501,  L502,  L503,  L504,  L505,  L506  }, \
                                                         \
    { KC_NO, R601,  R602,  R603,  R604,  R605,  R606  }, \
    { R700,  R701,  R702,  R703,  R704,  KC_NO, KC_NO }, \
    { R800,  R801,  R802,  R803,  R804,  R805,  R806  }, \
    { R900,  R901,  R902,  R903,  R904,  R905,  KC_NO }, \
    { R100,  R101,  R102,  R103,  R104,  R105,  R106  }, \
    { R110,  R111,  R112,  R113,  R114,  R115,  R116  }  \
}

#define TOG_OLED KC_F13
