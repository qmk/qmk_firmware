/* Copyright 2019 MechMerlin
 * Copyright 2020 @ben_roe (keycapsss.com)
 * Copyright 2023 @Ex3c4Def
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

#define MASTER_RIGHT
#define ENABLE_RGB_MATRIX_ALPHAS_MODS    // Static dual hue, speed is hue for secondary hue
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON // Full tighter gradient spinning around center of keyboard

// These modes also require the RGB_MATRIX_FRAMEBUFFER_EFFECTS define to be available.
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP // How hot is your WPM!

#define RGB_MATRIX_VAL_STEP 4
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 0   // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL 60  // RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 60  // Sets the default animation speed, if none has been set

#if defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
#    define POINTING_DEVICE_ROTATION_180 // may be used for trackball in 2nd position
#endif
