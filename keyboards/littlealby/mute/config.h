/* Copyright 2019 albybarber
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
#define VENDOR_ID       0x4142 // "AB"
#define PRODUCT_ID      0x4D55 // "MU"
#define DEVICE_VER      0x0001
#define MANUFACTURER    Little Alby
#define PRODUCT         Mute

#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Default pinout */
/* See arduino micro pinout: https://content.arduino.cc/assets/Pinout-Micro_latest.png
 * for pins e.g.
 * PB5 = digital pin 9 / analog pin 9
 */
#define DIRECT_PINS { \
    {B5} \
}
#define UNUSED_PINS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B6
#define RGBLED_NUM 1
#endif
