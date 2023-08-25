/* Copyright 2020 MelGeek <melgeek001365@gmail.com>
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

#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 26

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL
#define DRIVER_ADDR_1 0b0110000
#define DRIVER_COUNT 1
#define	RGB_MATRIX_LED_COUNT 75
#define CAPS_LOCK_INDEX_LEFT 71
#define CAPS_LOCK_INDEX_RIGHT 72
#define NUM_LOCK_INDEX_LEFT 70
#define NUM_LOCK_INDEX_RIGHT 73
#define SCROLL_LOCK_INDEX_LEFT 69
#define SCROLL_LOCK_INDEX_RIGHT 74