/* Copyright 2022 3araht
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
#define DYNAMIC_KEYMAP_LAYER_COUNT 13

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h
// #define HSV_BLUE        170, 255, 255
// but the RGB_MATRIX_DEFAULT_VAL = RGB_MATRIX_MAXIMUM_BRIGHTNESS should be 50, which is done by default in
// quantum/rgb_matrix/rgb_matrix.c
#define RGB_MATRIX_DEFAULT_HUE 170
#define RGB_MATRIX_DEFAULT_SAT 255
