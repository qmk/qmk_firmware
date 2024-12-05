/* Copyright 2017 Jason Williams
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
#include "util.h"

// clang-format off

/*
 * RGB Colors
 */
#define RGB_AZURE       0x99, 0xF5, 0xFF
#define RGB_BLACK       0x00, 0x00, 0x00
#define RGB_BLUE        0x00, 0x00, 0xFF
#define RGB_CHARTREUSE  0x80, 0xFF, 0x00
#define RGB_CORAL       0xFF, 0x7C, 0x4D
#define RGB_CYAN        0x00, 0xFF, 0xFF
#define RGB_GOLD        0xFF, 0xD9, 0x00
#define RGB_GOLDENROD   0xD9, 0xA5, 0x21
#define RGB_GREEN       0x00, 0xFF, 0x00
#define RGB_MAGENTA     0xFF, 0x00, 0xFF
#define RGB_ORANGE      0xFF, 0x80, 0x00
#define RGB_PINK        0xFF, 0x80, 0xBF
#define RGB_PURPLE      0x7A, 0x00, 0xFF
#define RGB_RED         0xFF, 0x00, 0x00
#define RGB_SPRINGGREEN 0x00, 0xFF, 0x80
#define RGB_TEAL        0x00, 0x80, 0x80
#define RGB_TURQUOISE   0x47, 0x6E, 0x6A
#define RGB_WHITE       0xFF, 0xFF, 0xFF
#define RGB_YELLOW      0xFF, 0xFF, 0x00
#define RGB_OFF         RGB_BLACK

/*
 * HSV Colors
 *
 * All values (including hue) are scaled to 0-255
 */
#define HSV_AZURE       132, 102, 255
#define HSV_BLACK         0,   0,   0
#define HSV_BLUE        170, 255, 255
#define HSV_CHARTREUSE   64, 255, 255
#define HSV_CORAL        11, 176, 255
#define HSV_CYAN        128, 255, 255
#define HSV_GOLD         36, 255, 255
#define HSV_GOLDENROD    30, 218, 218
#define HSV_GREEN        85, 255, 255
#define HSV_MAGENTA     213, 255, 255
#define HSV_ORANGE       21, 255, 255
#define HSV_PINK        234, 128, 255
#define HSV_PURPLE      191, 255, 255
#define HSV_RED           0, 255, 255
#define HSV_SPRINGGREEN 106, 255, 255
#define HSV_TEAL        128, 255, 128
#define HSV_TURQUOISE   123,  90, 112
#define HSV_WHITE         0,   0, 255
#define HSV_YELLOW       43, 255, 255
#define HSV_OFF         HSV_BLACK

// clang-format on

typedef struct PACKED rgb_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

// DEPRECATED
typedef rgb_t RGB;
typedef rgb_t rgb_led_t;

typedef struct PACKED hsv_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} hsv_t;

// DEPRECATED
typedef hsv_t HSV;

rgb_t hsv_to_rgb(hsv_t hsv);
rgb_t hsv_to_rgb_nocie(hsv_t hsv);
