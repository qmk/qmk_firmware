/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

/* key matrix pins */
#define MATRIX_ROW_PINS \
    { B5, B4, B3, A15, A14, A13 }
#define MATRIX_COL_PINS \
    { C14, C15, A0, A1, A2, A3, A4, A5, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 49
#define DRIVER_2_LED_TOTAL 43
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#define SNLED27351_CURRENT_TUNE \
    { 0x94, 0x94, 0x44, 0x94, 0x94, 0x44, 0x94, 0x94, 0x44, 0x94, 0x94, 0x44 }

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable CapsLcok LED */
#define CAPS_LOCK_LED_INDEX 51
