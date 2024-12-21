/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LED_MAP {0,1,2,9,8,7,3,4,5,6,19,18,17,10,11,12,16,15,14,13}
#    undef RGBLIGHT_ANIMATIONS
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_KNIGHT 	
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD 
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL 
//#    define RGBLIGHT_EFFECT_RGB_TEST 	
//#    define RGBLIGHT_EFFECT_SNAKE 	
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT 
//#    define RGBLIGHT_EFFECT_TWINKLE 
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 220
#    define RGBLIGHT_DEFAULT_VAL 190
#endif

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

// reduce burn-in
#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 120000
//#    define OLED_FADE_OUT
//#    define OLED_FADE_OUT_INTERVAL 3
#    define OLED_BRIGHTNESS 200
// cosmetic
#    define SPLIT_WPM_ENABLE
#endif

// size reduction
#define DISABLE_LEADER
#define NO_ACTION_ONESHOT
// Disabled -> incompatible with LTO
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

