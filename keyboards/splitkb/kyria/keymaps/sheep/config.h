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
//#    define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13} // circle
#    define RBGLIGHT_LED_MAP {9,8,6,7,5,3,2,4,1,0,10,12,13,11,14,16,17,15,18,19} // horizontal
#    undef RGBLIGHT_ANIMATIONS
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_KNIGHT 	
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD 
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL 
//#    define RGBLIGHT_EFFECT_RGB_TEST 	
//#    define RGBLIGHT_EFFECT_SNAKE 	
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT 
//#    define RGBLIGHT_EFFECT_TWINKLE 
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_DEFAULT_HUE 144 //248
#    define RGBLIGHT_DEFAULT_SAT 255
#    define RGBLIGHT_LIMIT_VAL 224
#    define RGBLIGHT_SLAVE_HUE_OFFSET 40
//#    define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
#    define RGBLIGHT_DEFAULT_VAL 0
#    define RGBLIGHT_SLEEP
#endif

// mod-tap :
// Lets you roll mod-tap keys
//#define IGNORE_MOD_TAP_INTERRUPT 
#define PERMISSIVE_HOLD // mod if another key is pressed and released before the tapping term while the mod-tap key is pressed
#define TAPPING_FORCE_HOLD // upgrade to #define TAPPING_FORCE_HOLD_PER_KEY if issue with TT() keycodes appear : #define TAPPING_FORCE_HOLD_PER_KEYo
#define TAPPING_TERM 150

// dyn macros

#define DYNAMIC_MACRO_SIZE 48
//#define DYNAMIC_MACRO_USER_CALL
#define DYNAMIC_MACRO_NO_NESTING


// size reduction
#define DISABLE_LEADER
#define NO_ACTION_ONESHOT
// Disabled -> incompatible with LTO
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
