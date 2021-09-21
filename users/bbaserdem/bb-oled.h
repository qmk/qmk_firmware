/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

// Contain the main oled writer here 
void oled_task_user(void);
// Some generic rendering functions
void render_qmk_logo(uint8_t row, uint8_t col);
void render_layer(uint8_t row, uint8_t col, uint8_t top_layer);
void render_modifiers_lite(uint8_t row, uint8_t col, uint8_t mods);
void render_encoder(uint8_t row, uint8_t col, uint8_t index, uint8_t layer);
void render_wpm(uint8_t row, uint8_t col);
void render_keymap(uint8_t row, uint8_t col, bool isLite);
#ifdef RGB_MATRIX_ENABLE
void render_rgb_lite(uint8_t row, uint8_t col);
#endif // RGB_MATRIX_ENABLE
void render_status_lite(uint8_t row, uint8_t col);
