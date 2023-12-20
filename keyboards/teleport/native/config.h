/*
Copyright 2022 Moritz Plattner
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

/* Use 3 dynamic keymap layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/* i2C Config */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4

#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9
#define I2C1_CLOCK_SPEED 400000


/* RGB Matrix driver config */
#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC
#define DRIVER_1_LED_TOTAL 46
#define DRIVER_2_LED_TOTAL 39
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#define RGB_MATRIX_LED_FLUSH_LIMIT 32

#define RGB_MATRIX_SLEEP

#define RGB_MATRIX_DEFAULT_SPD 40
#define RGB_MATRIX_DEFAULT_VAL 220
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#define ENABLE_RGB_MATRIX_ALPHAS_MODS                   // 2 Alphas and mods have different colors
#define ENABLE_RGB_MATRIX_BREATHING                     // 3 Breath a static color
#define ENABLE_RGB_MATRIX_CYCLE_ALL                     // 4 Cycle all colors
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN                 // 5 Cycle vertically
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL                  // 6 Cycle in a spirals
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP                // 7 Heatmap of typing speed
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE                // 8 Static background, pressed keys light up
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE      // 9 Pressed keys and nearby keys light up
#define ENABLE_RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS // 0 Single color raindrops, random keys lighting up at randomized intensity
#define ENABLE_RGB_MATRIX_CUSTOM_STATIC_GAME_MODE       // - Game mode sets the entire matrix (static) once, then stops LED refreshes

/* Define indicator LED indices, used for lighting effects  */
#define W_LED_INDEX 33
#define A_LED_INDEX 47
#define S_LED_INDEX 48
#define D_LED_INDEX 49

#define CAPS_LED_INDEX 46

#define WIN_LED_INDEX 76

#define ANV_A_LED_INDEX 15
#define ANV_N_LED_INDEX 30
#define ANV_V_LED_INDEX 45
#define ANV_I_LED_INDEX 59
#define ANV_L_LED_INDEX 74

#define NUM_1_LED_INDEX 17
#define NUM_2_LED_INDEX 18
#define NUM_3_LED_INDEX 19
#define NUM_4_LED_INDEX 20
#define NUM_5_LED_INDEX 21

#define M_LED_INDEX 68
#define K_LED_INDEX 54
#define O_LED_INDEX 40
#define NUM_0_LED_INDEX 26
#define P_LED_INDEX 41
#define SCLN_LED_INDEX 56
#define SLSH_LED_INDEX 71

/* Since the typing heatmap is broken on duplex matrix boards, force it to "slim" mode */
#ifdef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #define RGB_MATRIX_TYPING_HEATMAP_SLIM
#endif


/* Set HSE clock since it differs from F411 default */
#define STM32_HSECLK 16000000
