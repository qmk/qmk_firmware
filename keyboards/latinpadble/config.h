/*
Copyright 2021 haierwangwei2005

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "config_common.h"
#define VENDOR_ID       0x7C88 // "hw" = haierwangwei2005
#define PRODUCT_ID      0x7C98 // "lp" = latinpadble
#define DEVICE_VER      0x0001
#define MANUFACTURER    haierwangwei2005
#define PRODUCT         latinpadble
#define DESCRIPTION     Panasonic rotary encoder BLE pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F0, F6, F5, F4, F1 }
#define MATRIX_COL_PINS { D6, D7, B5, B6 }
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define SSD1306OLED
#define RGB_DI_PIN B7

#define RGBLED_NUM 4
#define DRIVER_LED_TOTAL RGBLED_NUM

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 25
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 20

/*
//#ifdef RGB_MATRIX_ENABLE
//#define DRIVER_LED_TOTAL RGBLED_NUM
//#define RGB_MATRIX_KEYPRESSES
//#endif
*/
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_KEYPRESSES         // reacts to keypresses
// #define RGB_MATRIX_KEYRELEASES        // reacts to keyreleases (instead of keypresses)
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS // Sets the default mode, if none has been set
// #define RGBLIGHT_HUE_STEP 12        // Units to step when in/decreasing hue
// #define RGBLIGHT_SAT_STEP 25        // Units to step when in/decreasing saturation
// #define RGBLIGHT_VAL_STEP 12        // Units to step when in/decreasing value (brightness)
// #define RGB_DISABLE_AFTER_TIMEOUT 0   // number of ticks to wait until disabling effects
// #define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
// #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
// #define RGBLIGHT_ANIMATIONS             // Run RGB animations
// #define RGBLIGHT_ANIMATIONS             // Enable all additional animation modes.
// #define RGBLIGHT_EFFECT_ALTERNATING     // Enable alternating animation mode.
#define RGBLIGHT_EFFECT_BREATHING       // Enable breathing animation mode.
// #define RGBLIGHT_EFFECT_CHRISTMAS       // Enable christmas animation mode.
// #define RGBLIGHT_EFFECT_KNIGHT          // Enable knight animation mode.
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD    // Enable rainbow mood animation mode.
// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL   // Enable rainbow swirl animation mode.
// #define RGBLIGHT_EFFECT_RGB_TEST        // Enable RGB test animation mode.
// #define RGBLIGHT_EFFECT_SNAKE           // Enable snake animation mode.
 //#define RGBLIGHT_EFFECT_STATIC_GRADIENT // Enable static gradient mode.


/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE


#define OLED_FONT_H "./lib/glcdfont.c"

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { F7 }

#define ENCODER_RESOLUTION 4
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
