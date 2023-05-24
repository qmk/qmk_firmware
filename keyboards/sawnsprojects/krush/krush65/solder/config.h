/* Copyright 2021 SawnsProjects
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
#define VENDOR_ID       0x5350
#define PRODUCT_ID      0x6B31
#define DEVICE_VER      0x0001
#define MANUFACTURER    SawnsProjects
#define PRODUCT         Krush65 - Solder

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B2, D1, D2, D4, D6, F6, F7, F5, F4 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D5, D3 }
#define UNUSED_PINS

/* indicator */
//  #define LED_CAPS_LOCK_PIN F0

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
/* Caps Lock */
#define LED_CAPS_LOCK_PIN F0
#define LED_PIN_ON_STATE 0

/* rotary */
#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { B3 }
#define ENCODER_RESOLUTION 4

#define RGB_DI_PIN F1
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 20
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#endif