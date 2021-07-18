/* Copyright 2019 Amber Holly
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

#define LAYER_TIMEOUT 10000
#define TIMEOUT_WARNING 3000
#define FLASH_PERIOD 250
#define SPEED_SCALE 2
#define TIMEOUT_SCALE 4
#define LAYER_SWITCH 1 // the layer to switch to
#define GET_FLASH_PERIOD ((layer_time_remaining <= TIMEOUT_WARNING/TIMEOUT_SCALE) ? FLASH_PERIOD/SPEED_SCALE : FLASH_PERIOD)
