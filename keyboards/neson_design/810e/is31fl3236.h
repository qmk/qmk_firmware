/**
 * Copyright 2023 astro
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

typedef struct is31_led {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) is31_led;

extern const is31_led g_is31_leds[RGB_LED_TOTAL];

void IS31FL3236_init(uint8_t addr, uint8_t index);
void IS31FL3236_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void IS31FL3236_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void IS31FL3236_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3236_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3236_update_pwm_buffers(uint8_t addr, uint8_t index);

#define OUT_1 0x01
#define OUT_2 0x02
#define OUT_3 0x03
#define OUT_4 0x04
#define OUT_5 0x05
#define OUT_6 0x06
#define OUT_7 0x07
#define OUT_8 0x08
#define OUT_9 0x09
#define OUT_10 0x0A
#define OUT_11 0x0B
#define OUT_12 0x0C
#define OUT_13 0x0D
#define OUT_14 0x0E
#define OUT_15 0x0F
#define OUT_16 0x10
#define OUT_17 0x11
#define OUT_18 0x12
#define OUT_19 0x13
#define OUT_20 0x14
#define OUT_21 0x15
#define OUT_22 0x16
#define OUT_23 0x17
#define OUT_24 0x18
#define OUT_25 0x19
#define OUT_26 0x1A
#define OUT_27 0x1B
#define OUT_28 0x1C
#define OUT_29 0x1D
#define OUT_30 0x1E
#define OUT_31 0x1F
#define OUT_32 0x20
#define OUT_33 0x21
#define OUT_34 0x22
#define OUT_35 0x23
#define OUT_36 0x24