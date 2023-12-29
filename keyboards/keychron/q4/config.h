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

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {4,4} }

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* turn off effects when suspended */
#define RGB_MATRIX_SLEEP

#define SNLED27351_CURRENT_TUNE \
    { 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60 }

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS