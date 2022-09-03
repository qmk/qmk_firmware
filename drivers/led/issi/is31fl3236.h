/* Copyright 2018 Jason Williams (Wilba)
 * Copyright 2021 Jamal Bouajjaj (Electro707)
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

typedef struct is31_led {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) is31_led;

extern const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL];

void IS31FL3236_init(uint8_t addr);
void IS31FL3236_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3236_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3236_update_pwm_buffers(uint8_t addr);

void IS31FL3236_set_led_control_register(uint8_t index, bool red, bool green, bool blue);
void IS31FL3236_update_led_control_registers(uint8_t addr);

#define OUT_1 0
#define OUT_2 1
#define OUT_3 2
#define OUT_4 3
#define OUT_5 4
#define OUT_6 5
#define OUT_7 6
#define OUT_8 7
#define OUT_9 8
#define OUT_10 9
#define OUT_11 10
#define OUT_12 11
#define OUT_13 12
#define OUT_14 13
#define OUT_15 14
#define OUT_16 15
#define OUT_17 16
#define OUT_18 17
#define OUT_19 18
#define OUT_20 19
#define OUT_21 20
#define OUT_22 21
#define OUT_23 22
#define OUT_24 23
#define OUT_25 24
#define OUT_26 25
#define OUT_27 26
#define OUT_28 27
#define OUT_29 28
#define OUT_30 29
#define OUT_31 30
#define OUT_32 31
#define OUT_33 32
#define OUT_34 33
#define OUT_35 34
#define OUT_36 35
