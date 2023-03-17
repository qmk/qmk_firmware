/* Copyright 2023 Ning (@ningjx)
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
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define TAPPING_TERM 200

#define RGB_DI_PIN B5
#define RGB_MATRIX_LED_COUNT 16

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

led_config_t g_led_config = { {
  { 0, 1, 2, 3 },
  { 4, 5, 6, 7 },
  { 8, 9, 10, 11 },
  { 12, 13, 14, 15 }
}, {
  {0,0},{75,0},{150,0},{224,0},
  {0,21},{75,21},{150,21},{224,21},
  {0,42},{75,42},{150,42},{224,42},
  {0,64},{75,64},{150,64},{224,64}
}, {
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
} };
