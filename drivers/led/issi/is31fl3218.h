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
#include "util.h"

#define IS31FL3218_REG_SHUTDOWN 0x00
#define IS31FL3218_REG_PWM 0x01
#define IS31FL3218_REG_LED_CONTROL_1 0x13
#define IS31FL3218_REG_LED_CONTROL_2 0x14
#define IS31FL3218_REG_LED_CONTROL_3 0x15
#define IS31FL3218_REG_UPDATE 0x16
#define IS31FL3218_REG_RESET 0x17

#define IS31FL3218_I2C_ADDRESS 0x54

#if defined(RGB_MATRIX_IS31FL3218)
#    define IS31FL3218_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

typedef struct is31fl3218_led_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED is31fl3218_led_t;

extern const is31fl3218_led_t PROGMEM g_is31fl3218_leds[IS31FL3218_LED_COUNT];

void is31fl3218_init(void);

void is31fl3218_write_register(uint8_t reg, uint8_t data);

void is31fl3218_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3218_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3218_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

void is31fl3218_update_pwm_buffers(void);

void is31fl3218_update_led_control_registers(void);

#define OUT1 0x00
#define OUT2 0x01
#define OUT3 0x02
#define OUT4 0x03
#define OUT5 0x04
#define OUT6 0x05
#define OUT7 0x06
#define OUT8 0x07
#define OUT9 0x08
#define OUT10 0x09
#define OUT11 0x0A
#define OUT12 0x0B
#define OUT13 0x0C
#define OUT14 0x0D
#define OUT15 0x0E
#define OUT16 0x0F
#define OUT17 0x10
#define OUT18 0x11
