/**
 * @file aw9523b.h
 * @brief driver for aw9523b
 * 
 * Copyright 2020 astro <yuleiz@gmail.com>
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

#ifndef AW9523B_ADDR
    #define AW9523B_ADDR 0xB6
#endif

#define AW9523B_PWM_BASE    0x20

#define AW9523B_P10_PWM     0x20
#define AW9523B_P11_PWM     0x21
#define AW9523B_P12_PWM     0x22
#define AW9523B_P13_PWM     0x23
#define AW9523B_P00_PWM     0x24
#define AW9523B_P01_PWM     0x25
#define AW9523B_P02_PWM     0x26
#define AW9523B_P03_PWM     0x27
#define AW9523B_P04_PWM     0x28
#define AW9523B_P05_PWM     0x29
#define AW9523B_P06_PWM     0x2A
#define AW9523B_P07_PWM     0x2B
#define AW9523B_P14_PWM     0x2C
#define AW9523B_P15_PWM     0x2D
#define AW9523B_P16_PWM     0x2E
#define AW9523B_P17_PWM     0x2F

#define AW9523B_PWM_SIZE    16

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} aw9523b_led;

extern const aw9523b_led g_aw9523b_leds[AW9523B_RGB_NUM];

void aw9523b_init(uint8_t addr);

void aw9523b_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void aw9523b_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void aw9523b_update_pwm_buffers(uint8_t addr);
