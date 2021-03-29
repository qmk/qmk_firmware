/* Copyright 2021 Andrew Fahmy
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


#ifdef RGB_MATRIX_ENABLE
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINDROPS

// #    define DEBUG_MATRIX_SCAN_RATE

#    define RGB_MATRIX_LED_FLUSH_LIMIT 100
// #    define RGB_MATRIX_LED_PROCESS_LIMIT 2

// i2c_master defines
#    define I2C_COUNT 2

#    define I2C1_BANK GPIOB
#    define I2C1_SCL 0 // A2 on pinout = B0
#    define I2C1_SDA 1 // A2 on pinout = B1
#    define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#    define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2

#    define USE_I2C2
#    define I2C2_BANK GPIOC
#    define I2C2_SCL 10 // A2 on pinout = C10
#    define I2C2_SDA 11 // A2 on pinout = C11
#    define I2C2_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#    define I2C2_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2

#    define DRIVER_ADDR_1 0b1010000
#    define DRIVER_ADDR_2 0b1010000
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 64
#    define DRIVER_2_LED_TOTAL 55
#    define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#endif
