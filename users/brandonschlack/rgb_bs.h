/* Copyright 2020 Brandon Schlack
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
#include "quantum.h"
#ifdef RGB_THEME_ENABLE
#   include "rgb_theme.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#   include "rgb_matrix.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#define LED_FLAG_KEYS (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER)

void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
void rgb_matrix_cycle_flag(void);
#endif

void keyboard_post_init_rgb(void);
void rgb_layer_helper(uint8_t hue, uint8_t sat, uint8_t val);

layer_state_t layer_state_set_rgb(layer_state_t state);
