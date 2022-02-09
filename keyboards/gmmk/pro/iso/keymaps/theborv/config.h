/* Copyright 2021 Jasper Chan
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

#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 33
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001
#define VENDOR_ID       0x320F
#define PRODUCT_ID      0x5044
#define MANUFACTURER    Glorious
#define PRODUCT         GMMK Pro

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED true
#endif // RGB_MATRIX_ENABLE
