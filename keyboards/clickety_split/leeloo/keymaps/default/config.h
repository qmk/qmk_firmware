/* Copyright 2023 Clickety Split Ltd.
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

// If rotary encoders are used, and they require more or less resolution/sensitivity
// you may try increasing or decreasing the value.
// #define ENCODER_RESOLUTION 2

    #define RGB_MATRIX_KEYPRESSES               // reacts to keypresses
//  #define RGB_MATRIX_KEYRELEASES              // reacts to keyreleases (instead of keypresses)
//  #define RGB_DISABLE_AFTER_TIMEOUT 0         // number of ticks to wait until disabling effects
    #define RGB_DISABLE_WHEN_USB_SUSPENDED      // turn off effects when suspended
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 115   // limits maximum brightness of LEDs to 150 out of 255.
                                                // Higher may cause the controller to crash.
    #define RGB_MATRIX_HUE_STEP 10
    #define RGB_MATRIX_SAT_STEP 10
    #define RGB_MATRIX_VAL_STEP 10
    #define RGB_MATRIX_SPD_STEP 10


/* By default, the RGB_MATRIX effects are disabled.
 * 
 * For a complete list, visit: https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects.
 * Some of the effects take up a lot of memory, so you may need to manage the number of
 * effects that are loaded at any given time.
*/
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #define ENABLE_RGB_MATRIX_SPLASH
