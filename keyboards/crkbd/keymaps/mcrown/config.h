/** @file config.h
 *  @brief config header that includes function prototypes and external variables.
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
 *
 * @author Mario Corona (mariocc@comunidad.unam.mx) 2021
 *
 */

#pragma once

/* Select hand configuration */
#define MASTER_LEFT

/* Comment this definition out if you want the main display to be output in horizontal mode */
#define OLED_VERTICAL

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
    #define RGB_MATRIX_HUE_STEP 30
    #define RGB_MATRIX_SAT_STEP 30
    #define RGB_MATRIX_VAL_STEP 30
    #define RGB_MATRIX_SPD_STEP 30
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS

    #define ENABLE_RGB_MATRIX_SOLID_COLOR
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_BAND_VAL
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    // #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL   /* @TODO: this effect is worling just in main kerboard. Needs to be fixed or properly configured. */
    #define ENABLE_RGB_MATRIX_BAND_VAL

#endif /* End of RGB_MATRIX_ENABLE */

/* To tell the compiler to use custom font */
#define OLED_FONT_H "keyboards/crkbd/keymaps/mcrown/glcdfont.c"
