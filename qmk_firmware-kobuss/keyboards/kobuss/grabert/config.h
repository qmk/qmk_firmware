/* Copyright 2020 Cameron Buss camrbuss@vt.edu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

/* USB Device descriptor parameter */
#define VENDOR_ID 0x1209
#define PRODUCT_ID 0xBA01
#define DEVICE_VER 0x0001
#define MANUFACTURER KoBuss
#define PRODUCT Grabert
#define DESCRIPTION Grabert Sixty

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
// clang-format off
#define DIRECT_PINS { \
    { D2, D4, B3, E0, E5, C0, F2, A2, B0, E9, E14, B14, D10, C6, C7 }, \
    { D3, D7, B9, E4, F10, C3, A1, A7, B1, E10, E15, B15, D11, D15, NO_PIN }, \
    { D5, B8, E3, F9, C2, A0, A3, C4, B2, E11, B10, D8, D12, NO_PIN, NO_PIN }, \
    { D6, B5, E2, C13, C1, F3, A4, A6, C5, E7, E12, B11, D9, D13, NO_PIN }, \
    { B4, E1, E6, A5, E8, E13, B12, B13, D14, C8, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN } \
}
// clang-format on

#define DEBOUNCE 5

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A \
        { C9 }
#    define ENCODERS_PAD_B \
        { A8 }
#    define ENCODER_RESOLUTION 4
#endif
#define TAP_CODE_DELAY 10

#ifdef OLED_DRIVER_ENABLE
#    define I2C1_SCL_BANK GPIOB
#    define I2C1_SDA_BANK GPIOB
#    define I2C1_SDA 7
#    define I2C1_SCL 6
#    define I2C1_SCL_PAL_MODE 1
#    define I2C1_SDA_PAL_MODE 1
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 3U
#    define I2C1_TIMINGR_SDADEL 1U
#    define I2C1_TIMINGR_SCLH 3U
#    define I2C1_TIMINGR_SCLL 9U

#    define OLED_DISPLAY_WIDTH 128
#    define OLED_DISPLAY_HEIGHT 32
#    define OLED_UPDATE_INTERVAL 20
#    define OLED_TIMEOUT 30000
#endif