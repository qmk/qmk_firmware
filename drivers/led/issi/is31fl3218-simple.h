/* Copyright 2018 Jason Williams (Wilba)
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

#define IS31FL3218_I2C_ADDRESS 0x54

#if defined(LED_MATRIX_IS31FL3218)
#    define IS31FL3218_LED_COUNT LED_MATRIX_LED_COUNT
#endif

typedef struct is31fl3218_led_t {
    uint8_t v;
} __attribute__((packed)) is31fl3218_led_t;

extern const is31fl3218_led_t PROGMEM g_is31fl3218_leds[LED_MATRIX_LED_COUNT];

void is31fl3218_init(void);

void is31fl3218_set_value(int index, uint8_t value);

void is31fl3218_set_value_all(uint8_t value);

void is31fl3218_set_led_control_register(uint8_t index, bool value);

void is31fl3218_update_pwm_buffers(void);

void is31fl3218_update_led_control_registers(void);

#define OUT1 0x01
#define OUT2 0x02
#define OUT3 0x03
#define OUT4 0x04
#define OUT5 0x05
#define OUT6 0x06
#define OUT7 0x07
#define OUT8 0x08
#define OUT9 0x09
#define OUT10 0x0A
#define OUT11 0x0B
#define OUT12 0x0C
#define OUT13 0x0D
#define OUT14 0x0E
#define OUT15 0x0F
#define OUT16 0x10
#define OUT17 0x11
#define OUT18 0x12
