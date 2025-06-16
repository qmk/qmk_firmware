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

/* i2C Config */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4

#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9
#define I2C1_CLOCK_SPEED 400000

#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC
#define IS31FL3733_SDB_PIN B9

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS

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
