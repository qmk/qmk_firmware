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

#define RGB_STRAND_MAX_NUM_LEDS 16

typedef enum {
    RGB_STRAND_EFFECT_NONE = 0,
    RGB_STRAND_EFFECT_STATIC,
    RGB_STRAND_EFFECT_DRAINSWIRL,
    RGB_STRAND_EFFECT_MOMENTARY,
    RGB_STRAND_EFFECT_LIKE,
    RGB_STRAND_EFFECT_BLINKY,
    RGB_STRAND_EFFECT_RAINBOW,
    RGB_STRAND_EFFECT_BREATHING,
    RGB_STRAND_EFFECT_INVALID,
} rgb_strands_anim_t;

typedef struct _rgb_strand_anim_config_t {
   HSV color;
   union {
       uint16_t period;     // period for repeating animations
       uint16_t time_step;  // time interval in ms
   };
   union {
       uint8_t  num_times;  // total number of times to repeat animation, 0 means forever
       uint8_t  val_step;   // how much val to change per timestep
       uint8_t  hue_step;   // how much hue to change per timestep
   };
} rgb_strand_anim_config_t;

typedef enum {
    RGB_STRAND_ANIM_STATE_OFF = 0,
    RGB_STRAND_ANIM_STATE_STEADY = 1,
    RGB_STRAND_ANIM_STATE_START = 2,

    RGB_STRAND_ANIM_STATE_DRAINSWIRL_SWIRL = 2,
    RGB_STRAND_ANIM_STATE_DRAINSWIRL_FINAL = 3,

    RGB_STRAND_ANIM_STATE_MOMENTARY_DECAY = 2,

    RGB_STRAND_ANIM_STATE_LIKE_SWIRL = 2,
    RGB_STRAND_ANIM_STATE_LIKE_BLINKON = 3,
    RGB_STRAND_ANIM_STATE_LIKE_BLINKOFF = 4,

    RGB_STRAND_ANIM_STATE_BLINKY_BLINKON = 2,
    RGB_STRAND_ANIM_STATE_BLINKY_BLINKOFF = 3,

    RGB_STRAND_ANIM_STATE_RAINBOW = 2,

    RGB_STRAND_ANIM_STATE_BREATHING = 2,
 } rgb_strand_anim_state_t;

const rgb_strand_anim_config_t * get_default_rgb_strand_anim_config(rgb_strands_anim_t anim);

bool is_valid_strand(uint8_t strand);

void rgb_strands_init(void);
void rgb_strands_task(void);
void rgb_strands_suspend(void);
void rgb_strands_wakeup(void);

/** Set all LEDs in the specified strand to the same color, no animation. */
void rgb_strand_set_color(uint8_t strand, uint8_t r, uint8_t g, uint8_t b);

/** Start animation on the strand. Config is optional */
void rgb_strand_animation_start(
        uint8_t strand,
        rgb_strands_anim_t effect,
        const rgb_strand_anim_config_t *config,
        rgb_strand_anim_state_t initial_state);

void rgb_strand_animation_set_state(uint8_t strand, rgb_strand_anim_state_t state);
