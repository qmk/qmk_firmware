/*
Copyright 2021 Danny Nguyen <danny@keeb.io>

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
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x6256
#define DEVICE_VER      0x0600
#define MANUFACTURER    Keebio
#define PRODUCT         Iris Rev. 6

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { B1, F0, F5, B4, D7 }
#define MATRIX_COL_PINS { F1, F4, B5, C7, D4, D6 }
#define MATRIX_ROW_PINS_RIGHT { B1, F0, F5, B4, B5 }
#define MATRIX_COL_PINS_RIGHT { D4, D6, D7, C7, F1, F4 }
#define SPLIT_HAND_PIN D5

#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }
#define ENCODERS_PAD_A_RIGHT { B2 }
#define ENCODERS_PAD_B_RIGHT { B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* ws2812 RGB LED */
#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 68
#    define RGBLED_SPLIT { 34, 34 }
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 120 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== enabled animations ==*/
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_DEFAULT_VAL 120
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 2)
// RGB Matrix
#    ifdef RGB_MATRIX_ENABLE
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS 160
#        define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define DRIVER_LED_TOTAL RGBLED_NUM
#        define RGB_MATRIX_SPLIT { 34, 34 }
#        define RGB_DISABLE_WHEN_USB_SUSPENDED
//#        define RGB_MATRIX_KEYPRESSES
#    endif
#endif
