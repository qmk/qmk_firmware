/* Copyright 2022 ANWC Limited d.b.a. ChonkerKeys
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
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "wait.h"
#include "progmem.h"
#include "sync_timer.h"
#include "rgb_strands.h"
#include "color.h"
#include "debug.h"
#include <lib/lib8tion/lib8tion.h>

bool is_rgb_strands_initialized = false;

void rgb_strands_timer_init(void);

void sethsv_rs(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) {
    val = val > RGB_STRAND_LIMIT_VAL ? RGB_STRAND_LIMIT_VAL : val;
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    led1->r = rgb.r;
    led1->g = rgb.g;
    led1->b = rgb.b;
}

void rgb_strands_init(void) {
    if (is_rgb_strands_initialized) {
        return;
    }

    rgb_strands_timer_init();

    is_rgb_strands_initialized = true;
}

void rgb_strands_task(void) {
    LED_TYPE leds[RGB_STRAND_2_NUM];
    sethsv_rs(HSV_WHITE, (LED_TYPE *)&leds[0]);
    sethsv_rs(HSV_RED, (LED_TYPE *)&leds[1]);
    sethsv_rs(HSV_ORANGE, (LED_TYPE *)&leds[2]);
    sethsv_rs(HSV_GOLD, (LED_TYPE *)&leds[3]);
    sethsv_rs(HSV_GREEN, (LED_TYPE *)&leds[4]);
    sethsv_rs(HSV_BLUE, (LED_TYPE *)&leds[5]);
    sethsv_rs(HSV_CYAN, (LED_TYPE *)&leds[6]);
    rgb_strand_set(2, leds, RGB_STRAND_2_NUM);
}

void rgb_strands_suspend(void) {
}

void rgb_strands_wakeup(void) {
}

void rgb_strands_timer_init(void) {
}

__attribute__((weak)) void rgb_strand2_call_driver(LED_TYPE *start_led, uint8_t num_leds) { ws2812_strand2_setleds(start_led, num_leds); }

void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds) {
    // TODO: find less tedious way of calling individual strands
    rgb_strand2_call_driver(leds, num_leds);
}

