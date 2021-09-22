/* Copyright 2021 Harrison Chan (Xelus)
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5845 // "XE"
#define PRODUCT_ID      0x5653 // Valor "VR" + 1
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Xelus Valor Rev2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B11, B10, A3, A1, A2 }
#define MATRIX_COL_PINS { B2, B1, B0, A7, A6, A5, A4, A13, B7, B6, B5, B4, B3, A15, A14 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// I2C setup
#define I2C1_SCL            8
#define I2C1_SDA            9
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 11U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   14U
#define I2C1_TIMINGR_SCLL   42U

// I2C EEPROM
#define EEPROM_I2C_24LC64

// More EEPROM for layers
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

/* RGB Matrix */
#define RGB_DI_PIN A9
#define RGBLED_NUM 28
#define DRIVER_LED_TOTAL 28
#define NOP_FUDGE 0.4

// RGB PWM
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM6
#define WS2812_DMA_CHANNEL 7
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM1_UP

// RGB Pullup
#define WS2812_EXTERNAL_PULLUP

// RGB Matrix settings
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_test_mode
