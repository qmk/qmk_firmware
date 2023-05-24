/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define VENDOR_ID 0xA8F8
#define PRODUCT_ID 0x1833
#define DEVICE_VER 0x0001
#define MANUFACTURER Bastard Keyboards
#define PRODUCT Charybdis

/* Key matrix configuration. */

// Rows are doubled-up.
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// Wiring configuration for each half.
#define MATRIX_ROW_PINS \
    { F1, B7, C6, D4, B5 }
#define MATRIX_COL_PINS \
    { D5, C7, F0, D7, E6, B4 }

#define MATRIX_ROW_PINS_RIGHT \
    { D5, F0, C6, D4, B5 }
#define MATRIX_COL_PINS_RIGHT \
    { F1, C7, B7, D7, E6, B4 }

#define DIODE_DIRECTION ROW2COL

#define ROTATIONAL_TRANSFORM_ANGLE -25

/* Handedness. */
#define MASTER_RIGHT

/* Bootmagic Lite configuration. */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

/* serial.c configuration (for split keyboard) */
#define SOFT_SERIAL_PIN D2

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* PMW3360 settings. */
#define PMW3360_CS_PIN B0

#define RGB_DI_PIN D3
#define RGBLED_NUM 56
#define RGBLED_SPLIT \
    { 29, 27 }

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif
