/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xA109
#define DEVICE_VER      0x000F
#define MANUFACTURER    monksoffunk
#define PRODUCT         NumAttack16
#define DESCRIPTION     4x4 Keyboard Pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/* key matrix pins */
    #define MATRIX_ROW_PINS { B5, B6, B2, B4 }
    #define MATRIX_COL_PINS { D0, D4, B1, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define BACKLIGHT_PIN C6
#define BACKLIGHT_LEVELS 8    //The number of brightness levels (maximum 31 excluding off)
//#define BACKLIGHT_CAPS_LOCK //Enable Caps Lock indicator using backlight (for keyboards without dedicated LED)
#define BACKLIGHT_BREATHING   //Enable backlight breathing, if supported
#define BREATHING_PERIOD 6    //The length of one backlight "breath" in seconds
//#define BACKLIGHT_ON_STATE 1  //The state of the backlight pin when the backlight is "on" - 1 for high, 0 for low

#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN D3
    #ifdef RGBLED_BOTH
    //  #define RGBLED_NUM 30
    #else
        #ifdef RGBLED_BACK
            #define RGBLED_NUM 25
        #else
            #ifdef RGBLED_1LED
                // #define RGBLED_NUM 1
            #else
                #define RGBLED_NUM 5
            #endif
        #endif
    #endif

    #ifndef IOS_DEVICE_ENABLE
        #if RGBLED_NUM <= 6
            #define RGBLIGHT_LIMIT_VAL 255
        #else
            #if RGBLED_NUM <= 16
                #define RGBLIGHT_LIMIT_VAL 130
            #else
                #define RGBLIGHT_LIMIT_VAL 120
            #endif
        #endif
        #define RGBLIGHT_VAL_STEP 17
    #else
        #if RGBLED_NUM <= 6
            #define RGBLIGHT_LIMIT_VAL 90
        #else
            #if RGBLED_NUM <= 16
                #define RGBLIGHT_LIMIT_VAL 45
            #else
                #define RGBLIGHT_LIMIT_VAL 35
            #endif
        #endif
        #define RGBLIGHT_VAL_STEP 4
    #endif

    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17

    #if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
    // USB_MAX_POWER_CONSUMPTION value
    //  120  RGBoff
    //  330  RGB 6
    //  300  RGB 32
        #define USB_MAX_POWER_CONSUMPTION 400
    #else
        // fix iPhone and iPad power adapter issue
        // iOS device need lessthan 100
        #define USB_MAX_POWER_CONSUMPTION 100
    #endif
#endif

#define rgb_sethsv_noeeprom rgblight_sethsv_noeeprom
#define RGB_current_config_hue  RGB_current_config.hue
#define RGB_current_config_sat  RGB_current_config.sat
#define RGB_current_config_val  RGB_current_config.val
#define RGB_CONFIG_hue RGB_CONFIG.hue
#define RGB_CONFIG_sat RGB_CONFIG.sat
#define RGB_CONFIG_val RGB_CONFIG.val
#define RGB_CONFIG rgblight_config
#define RGB_CONFIG_t rgblight_config_t
