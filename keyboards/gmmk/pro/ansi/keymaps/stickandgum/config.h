/* Copyright 2021 stickandgum
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

// I like NKRO.. force it! - You can still toggle it if you want to disable.
#define FORCE_NKRO


// At the time of this, there are 41 effects! That may be a bit too many to cycle through - keeping what I believe is the best.
#ifdef RGB_MATRIX_ENABLE
    // #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
    // Below added per: https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#suspended-state-id-suspended-state
    #define RGB_DISABLE_WHEN_USB_SUSPENDED

    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS // Heatmap, Rain
    #define RGB_MATRIX_KEYPRESSES // REACTIVE, SPLASH modes

    #define ENABLE_RGB_MATRIX_SOLID_COLOR               // BUILT IN (MAPPED!) Static single color.
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS               // Accenting various keys on the keyboard.
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN          // Top down rainbow!
    #define ENABLE_RGB_MATRIX_BREATHING                 // Built in (MAPPED!)
    #define ENABLE_RGB_MATRIX_BAND_SAT                  // Single hue band fading saturation scrolling left to right (with white)
    #define ENABLE_RGB_MATRIX_BAND_VAL                  // Single hue band fading brightness scrolling left to right (with black)
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL           // Single hue spinning spiral fades brightness (with black)
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT          // BUILT IN (MAPPED!) Full Rainbow Left to Right
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL            // BUILT IN (MAPPED!) - Consider disabling this - my poor eyes.
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS       // Randomly changes a single key's hue and saturation - better than above.
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP            // Hot keys!
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN              // The Matrix!
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse around a single key hit then fades value out (black otherwise)
#endif

