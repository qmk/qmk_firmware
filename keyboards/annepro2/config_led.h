/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#define BACKLIGHT_LEVELS 8

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_COLS 14

#define DRIVER_LED_TOTAL 61

/* Limit animations to 62.5 FPS to avoid tearing. (1/.016 = 62.5 FPS). */
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
