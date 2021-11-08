/**
 * @file aw9523b.c
 * @brief driver implementation of aw9523b
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

#include <stdbool.h>
#include "aw9523b.h"
#include "wait.h"
#include "i2c_master.h"

#define AW9523B_P0_INPUT    0x00
#define AW9523B_P1_INPUT    0x01
#define AW9523B_P0_OUTPUT   0x02
#define AW9523B_P1_OUTPUT   0x03
#define AW9523B_P0_CONF     0x04
#define AW9523B_P1_CONF     0x05
#define AW9523B_P0_INT      0x06
#define AW9523B_P1_INT      0x07

#define AW9523B_ID          0x10
#define AW9523B_CTL         0x11
#define AW9523B_P0_LED      0x12
#define AW9523B_P1_LED      0x13


#define AW9523B_RESET       0x7F

#define TIMEOUT             100

#define PWM2BUF(x) ((x) - AW9523B_PWM_BASE)
static uint8_t aw9523b_pwm_buf[AW9523B_PWM_SIZE];
static bool    aw9523b_pwm_dirty = false;

void aw9523b_init(uint8_t addr)
{
    i2c_init();
    // reset chip
    uint8_t data = 0;
    i2c_writeReg(addr, AW9523B_RESET, &data, 1, TIMEOUT);
    wait_ms(1);
    // set max led current
    data = 0x03; // 37mA/4
    i2c_writeReg(addr, AW9523B_CTL, &data, 1, TIMEOUT);
    // set port to led mode
    data = 0;
    i2c_writeReg(addr, AW9523B_P0_LED, &data, 1, TIMEOUT);
    i2c_writeReg(addr, AW9523B_P1_LED, &data, 1, TIMEOUT);
    // clear pwm buff
    for (uint8_t i = 0; i < 16; i++) {
        aw9523b_pwm_buf[i] = 0;
    }
    aw9523b_pwm_dirty = false;
}

void aw9523b_set_color(int index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (index >= AW9523B_RGB_NUM) return;

    aw9523b_led led = g_aw9523b_leds[index];
    aw9523b_pwm_buf[PWM2BUF(led.r)] = red;
    aw9523b_pwm_buf[PWM2BUF(led.g)] = green;
    aw9523b_pwm_buf[PWM2BUF(led.b)] = blue;
    aw9523b_pwm_dirty = true;
}

void aw9523b_set_color_all(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t i = 0; i < AW9523B_RGB_NUM; i++) {
        aw9523b_set_color(i, red, green, blue);
    }
    aw9523b_pwm_dirty = true;
}

void aw9523b_update_pwm_buffers(uint8_t addr)
{
    if (aw9523b_pwm_dirty) {
        for (uint8_t i = 0; i < AW9523B_RGB_NUM; i++){
            aw9523b_led led = g_aw9523b_leds[i];
            i2c_writeReg(addr, led.r, &aw9523b_pwm_buf[PWM2BUF(led.r)], 1, TIMEOUT);
            i2c_writeReg(addr, led.g, &aw9523b_pwm_buf[PWM2BUF(led.g)], 1, TIMEOUT);
            i2c_writeReg(addr, led.b, &aw9523b_pwm_buf[PWM2BUF(led.b)], 1, TIMEOUT);
        }
        aw9523b_pwm_dirty = false;
    }
}
