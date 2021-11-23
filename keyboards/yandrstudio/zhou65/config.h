/* Copyright 2021 JasonRen(biu)
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
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAAD
#define DEVICE_VER      0x0001
#define MANUFACTURER    ZHOU_Y&R
#define PRODUCT         zhou65

/* enable the nkro when using the VIA. */
#define FORCE_NKRO

/* fix VIA RGB_light */
#define VIA_HAS_BROKEN_KEYCODES


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4
