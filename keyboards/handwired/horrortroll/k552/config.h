/*
Copyright 2021 HorrorTroll

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1265 //Redragon
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

/* Forcing to use NKRO instead 6KRO */
#define FORCE_NKRO

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming */
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Mapping I2C2 for OLED */
#define I2C1_SCL_BANK GPIOB
#define I2C1_SDA_BANK GPIOB
#define I2C1_SCL 10
#define I2C1_SDA 11
#define I2C_DRIVER I2CD2

/* Use the redragon version to get the Redragon logo instead of the qmk logo */
#define OLED_FONT_H "lib/glcdfont_redragon.c"

/* The pin connected to the data pin of the LEDs */
#define RGB_DI_PIN C14

/* The number of LEDs connected */
#define DRIVER_LED_TOTAL 24

/* RGB Matrix config */
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 225
#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS

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
