/**
 * Copyright 2023 astro
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

#define STM32_HSECLK 16000000U

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 15

#define L_MASK 0x08
#define R_MASK 0x10

#define MATRIX_ROW_PINS {B1, B0, A7, A6}
#define MATRIX_COL_CHANNELS {L_MASK|0, L_MASK|1, L_MASK|2, L_MASK|3, L_MASK|4, L_MASK|5, L_MASK|6, L_MASK|7, \
                        R_MASK|4, R_MASK|7, R_MASK|6, R_MASK|5, R_MASK|3, R_MASK|0, R_MASK|1};

#define MAG_TH_LOW      2000
#define MAG_TH_HIGH     2300

#define LEFT_EN_PIN     B12 
#define RIGHT_EN_PIN    B13
#define COL_A_PIN       A8
#define COL_B_PIN       B15
#define COL_C_PIN       B14
