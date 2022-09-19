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

// OLED layout images writer function
void render_modifiers(uint8_t row, uint8_t col, uint8_t mods);
void render_layout(uint8_t row, uint8_t col, uint8_t mods, bool isLeft);
void render_rgb(uint8_t row, uint8_t col);
void render_status_left(uint8_t row, uint8_t col);
void render_status_right(uint8_t row, uint8_t col);
