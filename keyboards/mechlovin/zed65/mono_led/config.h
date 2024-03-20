/*
Copyright 2022 Mechlovin'

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


#define MATRIX_ROW_PINS { B12, A6, A5, A4, A3 }
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B2, B1, A15, B3, B9, B8, B7, B6, B5, B4 }


#ifdef LED_MATRIX_ENABLE
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define LED_DRIVER_ADDR_1 0b1110110
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define LED_DRIVER_COUNT 1
#define LED_MATRIX_LED_COUNT 70
#define LED_MATRIX_KEYPRESSES // reacts to keypresses
#define LED_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define LED_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#define ENABLE_LED_MATRIX_ALPHAS_MODS	
#define ENABLE_LED_MATRIX_BREATHING	
#define ENABLE_LED_MATRIX_BAND	
#define ENABLE_LED_MATRIX_BAND_PINWHEEL	
#define ENABLE_LED_MATRIX_BAND_SPIRAL	
#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT	
#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN	
#define ENABLE_LED_MATRIX_CYCLE_OUT_IN	
#define ENABLE_LED_MATRIX_DUAL_BEACON	
#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT	
#define ENABLE_LED_MATRIX_WAVE_UP_DOWN	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS	
#define ENABLE_LED_MATRIX_SOLID_SPLASH	
#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH	

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define VIA_QMK_LED_MATRIX_ENABLE
#endif

#define RGB_DI_PIN A7
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 24
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
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
#endif
