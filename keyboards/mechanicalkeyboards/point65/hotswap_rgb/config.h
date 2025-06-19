/* Copyright 2024 Sebastiaan Swinkels @ BeanBoards <sebastiaan.swinkels@googlemail.com>
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments
#define MATRIX_ROW_PINS { GP24, GP23, GP22, GP21, GP25 }
#define MATRIX_COL_PINS { GP28, GP27, GP26, GP29, GP0, GP11, GP10, GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP1 }
*/

#define DEBOUNCE 5

/* Double tap the side button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#ifdef RGB_MATRIX_ENABLE
    #define WS2812_PIO_USE_PIO1

    /* Enable Framebuffer and keypress effects */
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
#endif

/* couple of defaults */
#define RGB_INDICATOR_POS_OFFSET    48      /* Indicator LEDs additional brightness */

