/* Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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

/* IS31FL3731 driver address (for status LEDs)
 * Using the default defines here, but using a custom implementation
 */
#define LED_DRIVER_ADDR_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_DRIVER_COUNT 1
#define LED_MATRIX_LED_COUNT 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack
 */
#define LOCKING_RESYNC_ENABLE
