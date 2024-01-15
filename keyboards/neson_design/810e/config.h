/**
 * Copyright 2024 astro
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

#define BOARD_OTG_NOVBUSSENS 1
#define STM32_HSECLK 16000000U

#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9

#define IS31FL3729_LED_BEGIN    0
#define IS31FL3729_LED_TOTAL    90
#define IS31FL3236_LED_BEGIN    90
#define IS31FL3236_LED_TOTAL    6
#define RGB_LED_TOTAL           (IS31FL3236_LED_TOTAL+IS31FL3729_LED_TOTAL)
