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

static bool is_rgb_strands_initialized = false;

typedef struct _rgb_strand_status_t {
    rgb_strands_anim_t effect;
    uint8_t            hue;
    uint8_t            sat;
    uint8_t            val;
    uint16_t           last_timer;
    bool               restart;
    uint8_t            step;
    uint8_t            pos;
} rgb_strand_status_t;

typedef void (*strand_effect_func_t)(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_dummy(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_static(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_drainswirl(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_momentary(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_like(uint8_t strand, rgb_strand_status_t *status);
void rgb_strand_effect_blinky(uint8_t strand, rgb_strand_status_t *status);

void sethsv_rs(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led) {
    val = val > RGB_STRAND_LIMIT_VAL ? RGB_STRAND_LIMIT_VAL : val;
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    led->r = rgb.r;
    led->g = rgb.g;
    led->b = rgb.b;
}

static rgb_strand_status_t rgb_strand_status[RGB_STRANDS_MAX] = {};

void rgb_strands_init(void) {
    if (is_rgb_strands_initialized) {
        return;
    }

    for (uint8_t i = 0; i < RGB_STRANDS_MAX; i++) {
        rgb_strand_status_t * status = &rgb_strand_status[i];
        status->effect = RGB_STRAND_EFFECT_STATIC;
        status->hue = 0;
        status->sat = 0;
        status->val = 0;
    }

    is_rgb_strands_initialized = true;
}

void rgb_strands_task(void) {
    strand_effect_func_t effect_func = rgb_strand_effect_dummy;
    for (uint8_t i = 0; i < RGB_STRANDS_MAX; i++) {
        rgb_strand_status_t * status = &rgb_strand_status[i];
        switch (status->effect) {
            case RGB_STRAND_EFFECT_STATIC:
                effect_func = rgb_strand_effect_static;
                break;
            case RGB_STRAND_EFFECT_DRAINSWIRL:
                effect_func = rgb_strand_effect_drainswirl;
                break;
            case RGB_STRAND_EFFECT_MOMENTARY:
                effect_func = rgb_strand_effect_momentary;
                break;
            case RGB_STRAND_EFFECT_LIKE:
                effect_func = rgb_strand_effect_like;
                break;
            case RGB_STRAND_EFFECT_BLINKY:
                effect_func = rgb_strand_effect_blinky;
                break;
            default:
                break;
        }
        effect_func(i, status);
    }
}

void rgb_strands_suspend(void) {
}

void rgb_strands_wakeup(void) {
}

void rgb_strand_set_color(uint8_t strand, uint8_t h, uint8_t s, uint8_t v) {
    if (strand < 0 || strand >= RGB_STRANDS_MAX) return;
    rgb_strand_status_t * status = &rgb_strand_status[strand];
    status->effect = RGB_STRAND_EFFECT_STATIC;
    status->hue = h;
    status->sat = s;
    status->val = v;
}

void rgb_strand_start_animation(uint8_t strand, rgb_strands_anim_t effect, void *config) {
    if (strand < 0 || strand >= RGB_STRANDS_MAX) return;
    // TODO
}

void rgb_strand_effect_dummy(uint8_t strand, rgb_strand_status_t *status) {
}

void rgb_strand_effect_static(uint8_t strand, rgb_strand_status_t *status) {
    uint8_t i;
    LED_TYPE leds[RGB_STRAND_MAX_NUM_LEDS];
    uint8_t h = status->hue;
    uint8_t s = status->sat;
    uint8_t v = status->val;

#define _SET_ONE_COLOR(stn, strandnum) \
    for (i = 0; i < RGB_STRAND_##stn##_NUM; i++) { sethsv_rs(h, s, v, (LED_TYPE *)&leds[i]); } \
    rgb_strand_set(strandnum, leds, RGB_STRAND_##stn##_NUM)

    switch (strand) {
#ifdef RGB_STRAND_0_DI_PIN
        case 0:
            _SET_ONE_COLOR(0, 0);
            break;
#endif
#ifdef RGB_STRAND_1_DI_PIN
        case 1:
            _SET_ONE_COLOR(1, 1);
            break;
#endif
#ifdef RGB_STRAND_2_DI_PIN
        case 2:
            _SET_ONE_COLOR(2, 2);
            break;
#endif
#ifdef RGB_STRAND_3_DI_PIN
        case 3:
            _SET_ONE_COLOR(3, 3);
            break;
#endif
#ifdef RGB_STRAND_4_DI_PIN
        case 4:
            _SET_ONE_COLOR(4, 4);
            break;
#endif
#ifdef RGB_STRAND_5_DI_PIN
        case 5:
            _SET_ONE_COLOR(5, 5);
            break;
#endif
#ifdef RGB_STRAND_6_DI_PIN
        case 6:
            _SET_ONE_COLOR(6, 6);
            break;
#endif
#ifdef RGB_STRAND_7_DI_PIN
        case 7:
            _SET_ONE_COLOR(7, 7);
            break;
#endif
#ifdef RGB_STRAND_8_DI_PIN
        case 8:
            _SET_ONE_COLOR(8, 8);
            break;
#endif
#ifdef RGB_STRAND_9_DI_PIN
        case 9:
            _SET_ONE_COLOR(9, 9);
            break;
#endif
#ifdef RGB_STRAND_A_DI_PIN
        case 10:
            _SET_ONE_COLOR(A, 10);
            break;
#endif
#ifdef RGB_STRAND_B_DI_PIN
        case 11:
            _SET_ONE_COLOR(B, 11);
            break;
#endif
        default:
            break;
    }
}

void rgb_strand_effect_drainswirl(uint8_t strand, rgb_strand_status_t *status) {
    // TODO
}

void rgb_strand_effect_momentary(uint8_t strand, rgb_strand_status_t *status) {
    // TODO
}

void rgb_strand_effect_like(uint8_t strand, rgb_strand_status_t *status) {
    // TODO
}

void rgb_strand_effect_blinky(uint8_t strand, rgb_strand_status_t *status) {
    // TODO
}

__attribute__((weak)) void rgb_strand_call_driver(uint8_t strand, LED_TYPE *start_led, uint8_t num_leds) {
    ws2812_strand_setleds(strand, start_led, num_leds);
}

void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds) {
    rgb_strand_call_driver(strand, leds, num_leds);
}

