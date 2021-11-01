/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID       0x4145 // "AE"
#define PRODUCT_ID      0xA652 // AEboards EXT65 Rev2
#define DEVICE_VER      0x0001
#define MANUFACTURER    AEBoards
#define PRODUCT         AEBoards Ext65 Rev2

/* key matrix size */
/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS { A10, A9, A8, B7, A2, A1, B12, B11, B10, B2 }
#define MATRIX_COL_PINS { B14, B6, A0, B1, B0, A7, A6, A5, A4, A3 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//RGB Underglow WS2812
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 24
#define RGB_DI_PIN B15

//SPI
#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
#define WS2812_SPI_SCK_PIN B13
#define WS2812_EXTERNAL_PULLUP

// I2C OLED defines
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9

#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH 	3U
#define I2C1_TIMINGR_SCLL   9U

// LED defines
#define BACKLIGHT_PIN           B5
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   2
#define BACKLIGHT_PAL_MODE      1

#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

#define SLEEP_LED_GPT_DRIVER GPTD1
