/* Copyright 2023 luckycat70
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

#define RGBLED_NUM 78
#define RGB_MATRIX_LED_COUNT 255
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGBLIGHT_LIMIT_VAL 255
#ifdef RGB_MATRIX_ENABLE
#   define RGB_DISABLE_WHEN_USB_SUSPENDED
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_BREATHING
#endif
