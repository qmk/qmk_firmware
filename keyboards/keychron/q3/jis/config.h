/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

/* If PH3 used with a stronger pull resistor then the following definition needs be included */
// #define MATRIX_UNSELECT_DRIVE_HIGH

/* RGB Matrix Configuration */
#define RGB_MATRIX_LED_COUNT 91

#define SNLED27351_CURRENT_TUNE \
    { 0x94, 0x94, 0x44, 0x94, 0x94, 0x44, 0x94, 0x94, 0x44, 0x94, 0x94, 0x44 }

/* Enable CapsLcok LED */
#define CAPS_LOCK_LED_INDEX 50

