/* Copyright 2020 Neil Brian Ramirez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "quantum.h"

enum work_louder_rgb_keycodes {
    RGB_MATRIX_TOGGLE = QK_KB,
    RGB_MATRIX_MODE_INC,
    RGB_MATRIX_MODE_DEC,
    RGB_MATRIX_HUE_INC,
    RGB_MATRIX_HUE_DEC,
    RGB_MATRIX_SAT_INC,
    RGB_MATRIX_SAT_DEC,
    RGB_MATRIX_VAL_INC,
    RGB_MATRIX_VAL_DEC, // QK_KB_8
};

#define R_M_TOG RGB_MATRIX_TOGGLE
#define R_M_MOD RGB_MATRIX_MODE_INC
#define R_M_RMOD RGB_MATRIX_MODE_DEC
#define R_M_HUI RGB_MATRIX_HUE_INC
#define R_M_HUD RGB_MATRIX_HUE_DEC
#define R_M_SAI RGB_MATRIX_SAT_INC
#define R_M_SAD RGB_MATRIX_SAT_DEC
#define R_M_VAI RGB_MATRIX_VAL_INC
#define R_M_VAD RGB_MATRIX_VAL_DEC

bool process_record_work_rgb(uint16_t keycode, keyrecord_t *record);
