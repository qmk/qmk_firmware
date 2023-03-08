/* Copyright 2021 Gigahawk
 * Modified 2021 by usrfriendly for vial-qmk
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

#define DRIVER_1_LED_TOTAL 31
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL)

//enable RGB Matrix Effects for Vial
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

//Vial Keyboard UID
#define VIAL_KEYBOARD_UID {0x0C, 0x9F, 0xA6, 0xD3, 0x31, 0xF6, 0x2F, 0xE3}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }
