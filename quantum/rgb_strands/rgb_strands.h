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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "progmem.h"
#include "eeconfig.h"
#include "ws2812_strands.h"
#include "color.h"

#define RGB_STRANDS_MAX 12
#define RGB_STRAND_MAX_NUM_LEDS 16

typedef enum {
    RGB_STRAND_EFFECT_NONE = 0,
    RGB_STRAND_EFFECT_STATIC,
    RGB_STRAND_EFFECT_DRAINSWIRL,
    RGB_STRAND_EFFECT_MOMENTARY,
    RGB_STRAND_EFFECT_LIKE,
    RGB_STRAND_EFFECT_BLINKY,
    RGB_STRAND_EFFECT_MAX,
} rgb_strands_anim_t;

void rgb_strands_init(void);
void rgb_strands_task(void);
void rgb_strands_suspend(void);
void rgb_strands_wakeup(void);

/** Set all LEDs in the specified strand to the same color */
void rgb_strand_set_color(uint8_t strand, uint8_t r, uint8_t g, uint8_t b);

void rgb_strand_start_animation(uint8_t strand, rgb_strands_anim_t effect, void *config);

/** Low(er) level color setting.
 * @param strand Strand ID, 0 to 11
 * @param leds pointer to LEDs
 * @param num_leds number of LEDs in leds array */
void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds);
