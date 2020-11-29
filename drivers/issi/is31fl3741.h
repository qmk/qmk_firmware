/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
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

typedef struct is31_led {
    uint8_t driver : 2;
    uint8_t rcs;
    uint8_t rsw;
    uint8_t gcs;
    uint8_t gsw;
    uint8_t bcs;
    uint8_t bsw;
} __attribute__((packed)) is31_led;

extern const is31_led g_is31_leds[DRIVER_LED_TOTAL];
extern const is31_led g_is31_indicator_leds[DRIVER_INDICATOR_LED_TOTAL];

void IS31FL3741_init(uint8_t addr);
void IS31FL3741_write_register(uint8_t addr, uint8_t reg, uint8_t data);
bool IS31FL3741_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void IS31FL3741_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3741_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void IS31FL3741_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3741_update_pwm_buffers(uint8_t addr1, uint8_t addr2);
void IS31FL3741_update_led_control_registers(uint8_t addr1, uint8_t addr2);
void IS31FL3741_set_scaling_registers(const is31_led *pled, uint8_t red, uint8_t green, uint8_t blue);

void IS31FL3741_set_pwm_buffer(const is31_led *pled, uint8_t red, uint8_t green, uint8_t blue);
