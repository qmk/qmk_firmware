/* Copyright 2021
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
#include "color.h"

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#    define RGB_MATRIX_KEYREACTIVE_ENABLED
#endif

// Last led hit
#ifndef LED_HITS_TO_REMEMBER
#    define LED_HITS_TO_REMEMBER 8
#endif // LED_HITS_TO_REMEMBER

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
typedef struct PACKED {
    uint8_t  count;
    uint8_t  x[LED_HITS_TO_REMEMBER];
    uint8_t  y[LED_HITS_TO_REMEMBER];
    uint8_t  index[LED_HITS_TO_REMEMBER];
    uint16_t tick[LED_HITS_TO_REMEMBER];
} last_hit_t;
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

typedef enum rgb_task_states { STARTING, RENDERING, FLUSHING, SYNCING } rgb_task_states;

typedef uint8_t led_flags_t;

typedef struct PACKED {
    uint8_t     iter;
    led_flags_t flags;
    bool        init;
} effect_params_t;

typedef struct PACKED {
    uint8_t x;
    uint8_t y;
} led_point_t;

#define HAS_FLAGS(bits, flags) ((bits & flags) == flags)
#define HAS_ANY_FLAGS(bits, flags) ((bits & flags) != 0x00)

#define LED_FLAG_ALL 0xFF
#define LED_FLAG_NONE 0x00
#define LED_FLAG_MODIFIER 0x01
#define LED_FLAG_UNDERGLOW 0x02
#define LED_FLAG_KEYLIGHT 0x04
#define LED_FLAG_INDICATOR 0x08

#define NO_LED 255

typedef struct PACKED {
    uint8_t     matrix_co[MATRIX_ROWS][MATRIX_COLS];
    led_point_t point[RGB_MATRIX_LED_COUNT];
    uint8_t     flags[RGB_MATRIX_LED_COUNT];
} led_config_t;

typedef union {
    uint64_t raw;
    struct PACKED {
        uint8_t     enable : 2;
        uint8_t     mode : 6;
        HSV         hsv;
        uint8_t     speed;
        led_flags_t flags;
    };
} rgb_config_t;

_Static_assert(sizeof(rgb_config_t) == sizeof(uint64_t), "RGB Matrix EECONFIG out of spec.");

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif
