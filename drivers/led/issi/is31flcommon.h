/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
 * Copyright 2021 MasterSpoon
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

// Which variant header file to use
#ifdef IS31FL3742A
#    include "is31fl3742.h"
#elif defined(IS31FL3743A)
#    include "is31fl3743.h"
#elif defined(IS31FL3745)
#    include "is31fl3745.h"
#elif defined(IS31FL3746A)
#    include "is31fl3746.h"
#endif

#ifdef RGB_MATRIX_ENABLE
typedef struct is31_led {
    uint8_t driver;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) is31_led;

extern const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT];

#elif defined(LED_MATRIX_ENABLE)
typedef struct is31_led {
    uint8_t driver;
    uint8_t v;
} __attribute__((packed)) is31_led;

extern const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT];
#endif

#ifdef ISSI_MANUAL_SCALING
extern const is31_led PROGMEM g_is31_scaling[];
void                          IS31FL_set_manual_scaling_buffer(void);
#endif

void IS31FL_write_single_register(uint8_t addr, uint8_t reg, uint8_t data);
bool IS31FL_write_multi_registers(uint8_t addr, uint8_t *source_buffer, uint8_t buffer_size, uint8_t transfer_size, uint8_t start_reg_addr);
void IS31FL_unlock_register(uint8_t addr, uint8_t page);
void IS31FL_common_init(uint8_t addr, uint8_t ssr);

void IS31FL_common_update_pwm_register(uint8_t addr, uint8_t index);
void IS31FL_common_update_scaling_register(uint8_t addr, uint8_t index);

#ifdef RGB_MATRIX_ENABLE
// RGB Matrix Specific scripts
void IS31FL_RGB_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL_RGB_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void IS31FL_RGB_set_scaling_buffer(uint8_t index, bool red, bool green, bool blue);
#elif defined(LED_MATRIX_ENABLE)
// LED Matrix Specific scripts
void IS31FL_simple_set_scaling_buffer(uint8_t index, bool value);
void IS31FL_simple_set_brightness(int index, uint8_t value);
void IS31FL_simple_set_brigntness_all(uint8_t value);
#endif
