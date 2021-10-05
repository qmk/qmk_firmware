/* Copyright 2021 Jonavin Eng
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

#define TAPPING_TOGGLE 2
// TT set to two taps

/*  Handle GRAVESC combo keys */
#define GRAVE_ESC_ALT_OVERRIDE
    //Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
    //Always send Escape if Control is pressed

#define TAPPING_TERM 180

#ifdef RGBLIGHT_ENABLE
    // Define RGB_DI_PIN if not defien and associated define
    #ifndef RGB_DI_PIN
        #define RGB_DI_PIN A0
        #define RGBLIGHT_HUE_STEP 8
        #define RGBLIGHT_SAT_STEP 8
        #define RGBLIGHT_VAL_STEP 8
        #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
        #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */

        #define RGBLIGHT_EFFECT_BREATHING
        #define RGBLIGHT_EFFECT_RAINBOW_MOOD
        #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//      #define RGBLIGHT_EFFECT_SNAKE
//      #define RGBLIGHT_EFFECT_KNIGHT
        #define RGBLIGHT_EFFECT_CHRISTMAS
        #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//      #define RGBLIGHT_EFFECT_RGB_TEST
//      #define RGBLIGHT_EFFECT_ALTERNATING
    #endif

    // Redefine number of LED
    #ifdef RGBLED_NUM
        #undef RGBLED_NUM
    #endif // DEBUG
    #define RGBLED_NUM 30

    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE
