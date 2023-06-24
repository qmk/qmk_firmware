/* 
 * Copyright 2023 owlab
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

#define USB_POLLING_INTERVAL_MS 1

/* RGB Strip*/
#define RGB_DI_PIN B3   
#ifdef RGB_DI_PIN
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT  
#    define RGBLED_NUM 123
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_LIMIT_VAL 100
#    define RGBLIGHT_DEFAULT_VAL 50
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL + 5
#    define RGBLIGHT_SLEEP
/*== customize breathing effect ==*/
#    define RGBLIGHT_BREATHE_TABLE_SIZE 256  
#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.0
#    define RGBLIGHT_EFFECT_BREATHE_MAX    100
#endif