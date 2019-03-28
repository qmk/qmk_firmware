/*
Copyright 2018 Massdrop Inc.

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

#include "alt.h"
#include "led_matrix.h"

//GMK Laser
led_setup_t leds_gmk_laser[] = {
    { .hs = 0,  .he = 33,  .rs = 148,  .re = 148,  .gs = 0, .ge = 0, .bs = 211, .be = 211, .ef = EF_NONE },
    { .hs = 33, .he = 66,  .rs = 148,  .re = 212, .gs = 0, .ge = 36, .bs = 211, .be = 80, .ef = EF_NONE },
    { .hs = 66, .he = 100, .rs = 212, .re = 212, .gs = 36, .ge = 36, .bs = 80, .be = 80, .ef = EF_NONE },
    { .end = 1 },
};

//GMK Laser
led_setup_t leds_gmk_laser_scroll[] = {
    { .hs = 0,  .he = 100,  .rs = 148,  .re = 148,  .gs = 0, .ge = 0, .bs = 211, .be = 211, .ef = EF_NONE },
    { .hs = 0,  .he = 15,  .rs = 148,  .re = 212,  .gs = 0, .ge = 36, .bs = 211, .be = 80, .ef = EF_OVER | EF_SCR_R },
    { .hs = 15, .he = 30, .rs = 212, .re = 148, .gs = 36, .ge = 0, .bs = 80, .be = 211, .ef = EF_OVER | EF_SCR_R },
    { .end = 1 },
};

//White with moving red stripe
led_setup_t leds_white_with_red_stripe[] = {
    { .hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 255, .be = 255, .ef = EF_NONE },
    { .hs = 0, .he = 15, .rs = 0, .re = 0, .gs = 0, .ge = 255, .bs = 0, .be = 255, .ef = EF_SCR_R | EF_SUBTRACT },
    { .hs = 15, .he = 30, .rs = 0, .re = 0, .gs = 255, .ge = 0, .bs = 255, .be = 0, .ef = EF_SCR_R | EF_SUBTRACT },
    { .end = 1 },
};

//Yellow
led_setup_t leds_yellow[] = {
    { .hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_NONE },
    { .end = 1 },
};

//Off
led_setup_t leds_off[] = {
    { .hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_NONE },
    { .end = 1 },
};

//Red
led_setup_t leds_red[] = {
    { .hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_NONE },
    { .end = 1 },
};

//Green
led_setup_t leds_green[] = {
    { .hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_NONE },
    { .end = 1 },
};

//Blue
led_setup_t leds_blue[] = {
    { .hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 0, .ge = 0, .bs = 255, .be = 255, .ef = EF_NONE },
    { .end = 1 },
};

//Purple
led_setup_t leds_purple[] = {
    { .hs = 0, .he = 100, .rs = 148, .re = 148, .gs = 0, .ge = 0, .bs = 211, .be = 211, .ef = EF_NONE },
    { .end = 1 },
};

//White
led_setup_t leds_white[] = {
    { .hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 255, .be = 255, .ef = EF_NONE },
    { .end = 1 },
};

//Black with moving purple stripe
led_setup_t leds_black_with_purple_stripe[] = {
    { .hs = 0, .he = 15, .rs = 0, .re = 148, .gs = 0, .ge = 0, .bs = 0, .be = 211, .ef = EF_SCR_R },
    { .hs = 15, .he = 30, .rs = 148, .re = 0, .gs = 0, .ge = 0, .bs = 211, .be = 0, .ef = EF_SCR_R },
    { .end = 1 },
};

//Black with moving red stripe
led_setup_t leds_black_with_red_stripe[] = {
    { .hs = 0, .he = 15, .rs = 0, .re = 255, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_SCR_R },
    { .hs = 15, .he = 30, .rs = 255, .re = 0, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_SCR_R },
    { .end = 1 },
};

//Add new LED animations here using one from above as example
//The last entry must be { .end = 1 }
//Add the new animation name to the list below following its format

void *led_setups[] = {
    leds_gmk_laser,
    leds_gmk_laser_scroll,
    leds_purple,
    leds_white,
    leds_black_with_purple_stripe,
    leds_black_with_red_stripe,
    leds_off
};

const uint8_t led_setups_count = sizeof(led_setups) / sizeof(led_setups[0]);
