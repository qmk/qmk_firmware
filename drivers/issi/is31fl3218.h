/* Copyright 2018 Jason Williams (Wilba)
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

#include <stdint.h>
#include <stdbool.h>

void IS31FL3218_init(void);
void IS31FL3218_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3218_set_color_all( uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3218_update_pwm_buffers(void);
