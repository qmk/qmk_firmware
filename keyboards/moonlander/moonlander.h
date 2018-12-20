/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MCP23018_DEFAULT_ADDRESS 0b0100000

#define ML_LED_1(status) (status ? writePinHigh(B0) : writePinLow(B0))
#define ML_LED_2(status) (status ? writePinHigh(B1) : writePinLow(B1))
#define ML_LED_3(status) (status ? writePinHigh(B2) : writePinLow(B2))

#define ML_LED_4(status) mcp23018_leds[0] = status
#define ML_LED_5(status) mcp23018_leds[1] = status
#define ML_LED_6(status) mcp23018_leds[2] = status

#include "quantum.h"

#define LAYOUT_moonlander( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35, \
    k40, k41, k42, k43, k44, \
    k50, k51, k52, \
\
    k60, k61, k62, k63, k64, k65, k66, \
    k70, k71, k72, k73, k74, k75, k76, \
    k80, k81, k82, k83, k84, k85, k86, \
         k91, k92, k93, k94, k95, k96, \
              ka2, ka3, ka4, ka5, ka6, \
                        kb4, kb5, kb6 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, KC_NO }, \
    { k40, k41, k42, k43, k44, KC_NO, KC_NO }, \
    { k50, k51, k52, KC_NO, KC_NO, KC_NO, KC_NO }, \
\
    { k60, k61, k62, k63, k64, k65, k66 }, \
    { k70, k71, k72, k73, k74, k75, k76 }, \
    { k80, k81, k82, k83, k84, k85, k86 }, \
    { KC_NO,k91, k92, k93, k94, k95, k96 }, \
    { KC_NO, KC_NO, ka2, ka3, ka4, ka5, ka6 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, kb4, kb5, kb6  } \
}
