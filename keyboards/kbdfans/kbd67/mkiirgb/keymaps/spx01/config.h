/* Copyright 2022 spx01 (@spx01)
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

/* --- custom defines only used in my own code --- */

/* easily switch on debugging features */
#define CUSTOM_DEBUG false

/* hexrgb mode special keys, these shouldn't be KC_A to KC_F or KC_0 to KC_9 */
/* keycode that triggers saving the current rgb_static color into eeprom */
#define HEXRGB_SAVE_KC KC_S
/* keycode that triggers resetting rgb_static to the color saved in the eeprom */
#define HEXRGB_RESET_KC KC_R

/* --- keyboard configuration macros --- */

#if CUSTOM_DEBUG
#    define NO_DEBUG
#    define NO_PRINT
#endif

#define RETRO_TAPPING
#define PERMISSIVE_HOLD

#undef RGB_MATRIX_STARTUP_MODE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_RGB_STATIC
