/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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
#define VENDOR_ID       0x7516 //Redragon
#define PRODUCT_ID      0x5104
#define DEVICE_VER      0x0001
#define MANUFACTURER    Redragon
#define PRODUCT         K552 Kumara

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* Key matrix pin           0    1,   2,  3,  4,  5,  6,   7,   8,  9, 10, 11, 12,  13, 14, 15, 16 */
#define MATRIX_ROW_PINS { C12, C10, A10, A8, C8, C9 }
#define MATRIX_COL_PINS { B15,  C6,  C7, A3, A1, C3, C1, B14, B13, A9, B3, B4, A0, C11, A2, C0, C2 }

/* Direction of diode (COL2ROW or ROW2COL) */
#define DIODE_DIRECTION ROW2COL

/* Bootmagic reset */
#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 6

/* Forcing to use NKRO instead 6KRO */
#define FORCE_NKRO

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming */
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* EEPROM size */
#define EEPROM_PAGE_SIZE
#define FEE_PAGE_SIZE 0x800
#define FEE_PAGE_COUNT 4

#define FEE_MCU_FLASH_SIZE_IGNORE_CHECK
#define FEE_MCU_FLASH_SIZE                              \
({                                                      \
    uint16_t flash_size = *(uint16_t*)FLASHSIZE_BASE;   \
    (flash_size <= 512) ? flash_size : 512;             \
})

#ifdef OLED_ENABLE
    /* Mapping I2C2 for OLED */
    #define I2C1_SCL_PIN B10
    #define I2C1_SDA_PIN B11
    #define I2C_DRIVER I2CD2

    /* Use the custom font */
    #define OLED_FONT_H "lib/glcdfont.c"
#endif

#ifdef RGB_MATRIX_ENABLE
    #define DRIVER_LED_TOTAL 24
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
    #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

    /* RGB Matrix config */
    #define RGB_DI_PIN C14

    /* RGB Matrix effect */
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_BAND_VAL
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define ENABLE_RGB_MATRIX_CYCLE_ALL
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define ENABLE_RGB_MATRIX_DUAL_BEACON
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
    #define ENABLE_RGB_MATRIX_RAINDROPS
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    #define ENABLE_RGB_MATRIX_HUE_BREATHING
    #define ENABLE_RGB_MATRIX_HUE_PENDULUM
    #define ENABLE_RGB_MATRIX_HUE_WAVE
    #define ENABLE_RGB_MATRIX_PIXEL_RAIN
#endif
