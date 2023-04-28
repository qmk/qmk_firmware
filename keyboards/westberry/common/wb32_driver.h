/* Copyright (C) 2023 Westberry Technology Corp., Ltd
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
#include "quantum.h"

typedef struct wbrgb_led {
    uint8_t sw: 5;
    uint8_t id: 3;
} __attribute__((packed)) wbrgb_led;

extern const wbrgb_led PROGMEM g_wbrgb_leds[RGB_MATRIX_LED_COUNT];

void rgb_driver_init(void);

#define RS_COL0 0
#define RS_COL1 1
#define RS_COL2 2
#define RS_COL3 3
#define RS_COL4 4

#define RS_ROW0 0
#define RS_ROW1 1
#define RS_ROW2 2
#define RS_ROW3 3
#define RS_ROW4 4
#define RS_ROW5 5
#define RS_ROW6 6
#define RS_ROW7 7
#define RS_ROW8 8
#define RS_ROW9 9
#define RS_ROW10 10
#define RS_ROW11 11
#define RS_ROW12 12
#define RS_ROW13 13
#define RS_ROW14 14
#define RS_ROW15 15
#define RS_ROW16 16
#define RS_ROW17 17
#define RS_ROW18 18
#define RS_ROW19 19
#define RS_ROW20 20
#define RS_ROW21 21
#define RS_ROW22 22
