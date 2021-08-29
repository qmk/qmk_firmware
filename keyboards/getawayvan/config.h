/*
Copyright 2020

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xE5CA
#define PRODUCT_ID      0x0401
#define DEVICE_VER      0x0001
#define MANUFACTURER    esca
#define PRODUCT         GetawayVan

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A4, A13, A10, C13, C14 }
#define MATRIX_ROW_PINS { A9, A8, A3, A5 }
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B15
#define DRIVER_LED_TOTAL 51
#define RGBLED_NUM 51
#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
#define WS2812_SPI_SCK_PIN B13
#define WS2812_EXTERNAL_PULLUP

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 20
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_LIMIT_VAL 128

#define DEBOUNCE    5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
