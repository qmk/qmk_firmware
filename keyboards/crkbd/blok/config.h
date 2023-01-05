/*
Copyright 2023 Noah Pederson <@chiefnoah>

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
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

#define RGB_DI_PIN GP0
#define SOFT_SERIAL_PIN GP1
#define WS2812_PIO_USE_PIO1

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X32
#    define I2C1_SCL_PIN GP17
#    define I2C1_SDA_PIN GP16
#    define I2C_DRIVER I2CD1
#    define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#    define SPLIT_OLED_ENABLE
#endif

#define DIODE_DIRECTION COL2ROW

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET              // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25     // Specify a optional status led by GPIO number which blinks when entering the bootloader

#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 54 // Number of LEDs
#    define RGBLED_SPLIT \
        { 27, 27 }
#    define RGBLIGHT_SPLIT
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 54 // Number of LEDs
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    define RGB_MATRIX_SPLIT \
        { 27, 27 }
#    define SPLIT_TRANSPORT_MIRROR
#endif

#define MATRIX_ROW_PINS \
    { GP4, GP5, GP6, GP7 }
#define MATRIX_COL_PINS \
    { GP29, GP28, GP27, GP26, GP22, GP20 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order
