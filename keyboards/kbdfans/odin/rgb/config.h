/* Copyright 2021 Dztech
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
#include "config_common.h"

#define VENDOR_ID       0x4B42
#define PRODUCT_ID      0x0102
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFANS
#define PRODUCT         ODIN_RGB

#define MATRIX_ROWS 6
#define MATRIX_COLS 20

#define MATRIX_ROW_PINS { A10, A9, A8, B14, B13, A2 }
#define MATRIX_COL_PINS { A3, A4, A5, A6, A7, B0, B1, B2, B12, A15, B3, B4, B5, B6, B7, B8, C13, C14, C15, A0}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5
#define RGBLED_NUM 110
#define DRIVER_LED_TOTAL 110
#define RGB_DI_PIN B15

#ifdef RGB_MATRIX_ENABLE
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_KEYPRESSES 
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#endif
