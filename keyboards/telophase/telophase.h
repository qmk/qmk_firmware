/*
Copyright 2021

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

#include "quantum.h"

#define red_led_off writePinHigh(F5)
#define red_led_on  writePinLow(F5)
#define blu_led_off writePinHigh(F4)
#define blu_led_on  writePinLow(F4)
#define grn_led_off writePinHigh(D1)
#define grn_led_on  writePinLow(D1)

#define set_led_off     red_led_off; grn_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_ortho_4x12( \
    k00, k01, k02, k03, k04, k05,      k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15,      k16, k17, k18, k19, k1A, k1B, \
    k20, k21, k22, k23, k24, k25,      k26, k27, k28, k29, k2A, k2B, \
    k30, k31, k32, k33, k34, k35,      k36, k37, k38, k39, k3A, k3B \
) { \
    { k00, k01, k02, k03, k04, k05,      k06, k07, k08, k09, k0A, k0B }, \
    { k10, k11, k12, k13, k14, k15,      k16, k17, k18, k19, k1A, k1B }, \
    { k20, k21, k22, k23, k24, k25,      k26, k27, k28, k29, k2A, k2B }, \
    { k30, k31, k32, k33, k34, k35,      k36, k37, k38, k39, k3A, k3B } \
}

#define LAYOUT LAYOUT_ortho_4x12
