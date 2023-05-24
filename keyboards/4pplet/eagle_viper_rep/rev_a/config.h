/*
Copyright 2021 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         Eagle Viper REP Rev A

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_COL_PINS { A0, B1, B0, A4, B5, B4, B3 }
#define MATRIX_ROW_PINS { A2, A1, B8, A10, C15, A15, B7, B6, C14, C13}
#define DIODE_DIRECTION COL2ROW

/* In switch leds */
#define BACKLIGHT_PIN           A3
#define BACKLIGHT_PWM_DRIVER    PWMD2
#define BACKLIGHT_PWM_CHANNEL   4
#define BACKLIGHT_PAL_MODE      2
#define BACKLIGHT_ON_STATE      1
#define BACKLIGHT_LEVELS        10
#define BACKLIGHT_BREATHING     TRUE

/* Underglow */
#define RGB_DI_PIN  A7
#define WS2812_SPI  SPID1
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PIN A5
#define WS2812_SPI_SCK_PAL_MODE 0
#define RGBLED_NUM  16
#define RGBLIGHT_ANIMATIONS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Indicator leds */
#define LOCK_LIGHTS     TRUE
#define DISPLAY_LAYERS  TRUE
#define CAPS_PIN        B2
#define NUM_PIN         B12
#define SCROLL_PIN      B13
#define LAYER_1         B14
#define LAYER_2         B15
#define LAYER_3         A8
#define LAYER_4         A9
#define LAYER_5         B9

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Added extra layer for use of layer leds */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
