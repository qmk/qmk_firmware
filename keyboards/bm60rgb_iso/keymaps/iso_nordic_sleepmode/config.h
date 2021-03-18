/* Copyright 2020 jakobst1n
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

/*****************************
 * SLEEPMODE CONFIG
 *****************************/
#define SLEEPMODE_ENABLE  // see keymap readme for info about this function.

/* How long the backlight should stay on
   without any interaction before turning off. */
#define SLEEPMODE_TIMEOUT 10  // in minutes
/* Which mode we should enter after the timeout,
   RGB_MATRIX_NONE to turn off.
   I thinks RGB_MATRIX_DIGITAL RAIN is pretty :) */
#define SLEEPMODE_RGB_MODE RGB_MATRIX_NONE
/* The desired animation speed when in "sleep mode" */
#define SLEEPMODE_RGB_ANIMATION_SPEED 10
/* The desired brightness when in "sleep mode" */
#define SLEEPMODE_RGB_VAL 10
