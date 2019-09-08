/**
 * Copyright (C) 2016 Austin Glaser
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */
#pragma once

#include "hal.h"
#include "color.h"

#define CONCAT_SYMBOLS(s1, s2)              s1##s2
#define CONCAT_EXPANDED_SYMBOLS(s1, s2)     CONCAT_SYMBOLS(s1, s2)
#define PWMD(n)                             CONCAT_EXPANDED_SYMBOLS(PWMD, n)

#define sign(x) (( x > 0 ) - ( x < 0 ))     // why is this here?

typedef struct Color Color;
struct Color {
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

void ws2812_init(void);
void ws2812_write_led(int index, uint8_t r, uint8_t g, uint8_t b);
void ws2812_setled(int i, uint8_t r, uint8_t g, uint8_t b);
void ws2812_setleds(LED_TYPE *led_colors, uint16_t num_leds);
void ws2812_setleds_rgbw(LED_TYPE *led_colors, uint16_t nul_leds);
void ws2812_setled_all(uint8_t r, uint8_t g, uint8_t b);
