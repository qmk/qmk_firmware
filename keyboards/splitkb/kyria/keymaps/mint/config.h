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
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    ifndef RGBLIGHT_LIMIT_VAL
#    	define RGBLIGHT_LIMIT_VAL 150
#    endif
#endif

// `SPLIT_HAND_PIN` can currently be defined in `info.json`,
// but can't yet be given a value
#define SPLIT_HAND_PIN B5

// Not yet available in `info.json`
#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#endif

#define I2C_DRIVER I2CD1
//#define I2C1_SDA_PIN GP6
//#define I2C1_SCL_PIN GP7 
#define MASTER_LEFT

#define POINTING_DEVICE_COMBINED
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll. #define POINTING_DEVICE_AUTO_MOUSE_ENABLE 
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
#define SPLIT_POINTING_ENABLE

#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define MOUSEKEY_INERTIA	undefined	//Enable Inertia mode
#define MOUSEKEY_DELAY	        150	//Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL	16	//Time between cursor movements in milliseconds (16 = 60fps)
#define MOUSEKEY_MAX_SPEED	32	//Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX	32	//Number of frames until maximum cursor speed is reached
#define MOUSEKEY_FRICTION	24	//How quickly the cursor stops after releasing a key
#define MOUSEKEY_MOVE_DELTA	1	//How much to move on first frame (1 strongly recommended)

#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_ADDR 0x2A

// #define CIRQUE_PINNACLE_DISABLE_TAP
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
// #define CIRQUE_PINNACLE_CURVED_OVERLAY
#define CIRQUE_PINNACLE_DISABLE_SMOOTHING
#define CIRQUE_PINNACLE_ENABLE_CURSOR_GLIDE
#define CIRQUE_PINNACLE_ENABLE_CIRCULAR_SCROLL