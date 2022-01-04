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

#ifdef RGB_STRANDS_ANIMATIONS
#    define RGB_STRANDS_EFFECT_BREATHING
#    define RGB_STRANDS_EFFECT_RAINBOW_MOOD
#    define RGB_STRANDS_EFFECT_RAINBOW_SWIRL
#    define RGB_STRANDS_EFFECT_SNAKE
#    define RGB_STRANDS_EFFECT_KNIGHT
#    define RGB_STRANDS_EFFECT_CHRISTMAS
#    define RGB_STRANDS_EFFECT_RGB_TEST
#    define RGB_STRANDS_EFFECT_ALTERNATING
#    define RGB_STRANDS_EFFECT_TWINKLE
#endif

// clang-format off

#if  defined(RGB_STRANDS_EFFECT_BREATHING)     \
  || defined(RGB_STRANDS_EFFECT_RAINBOW_MOOD)  \
  || defined(RGB_STRANDS_EFFECT_RAINBOW_SWIRL) \
  || defined(RGB_STRANDS_EFFECT_SNAKE)         \
  || defined(RGB_STRANDS_EFFECT_KNIGHT)        \
  || defined(RGB_STRANDS_EFFECT_CHRISTMAS)     \
  || defined(RGB_STRANDS_EFFECT_RGB_TEST)      \
  || defined(RGB_STRANDS_EFFECT_ALTERNATING)   \
  || defined(RGB_STRANDS_EFFECT_TWINKLE)
#    define RGB_STRANDS_USE_TIMER
#endif

// clang-format on

#include <stdint.h>
#include <stdbool.h>
#include "progmem.h"
#include "eeconfig.h"
#include "ws2812_strands.h"
#include "color.h"

#define RGB_STRAND_MAX_NUM_LEDS 16

void rgb_strands_init(void);
void rgb_strands_task(void);
void rgb_strands_suspend(void);
void rgb_strands_wakeup(void);

void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds);
