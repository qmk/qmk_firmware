/* Copyright 2023 temp4gh
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


#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010011

#define IS31FL3733_DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 45
#define DRIVER_2_LED_TOTAL 45

#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL+DRIVER_2_LED_TOTAL)

#define    ENABLE_RGB_MATRIX_SOLID_COLOR
#define    ENABLE_RGB_MATRIX_ALPHAS_MODS
#define    ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define    ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define    ENABLE_RGB_MATRIX_BREATHING
#define    ENABLE_RGB_MATRIX_BAND_SAT
#define    ENABLE_RGB_MATRIX_BAND_VAL
#define    ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define    ENABLE_RGB_MATRIX_CYCLE_ALL
#define    ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define    ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define    ENABLE_RGB_MATRIX_HUE_WAVE
#define    ENABLE_RGB_MATRIX_PIXEL_FLOW
