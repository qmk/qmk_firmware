/* Copyright 2021 Basic I/O Instruments (@scottywei)
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

#define BLE_NAME "THINPAD BLE"

#define MATRIX_ROW_PINS { B2, B6, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { C6, D5, D0, D1 }

#define BACKLIGHT_PIN B5
#define BACKLIGHT_LEVELS 12

#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { E6, F1 }
#define ENCODERS_PAD_B { B0, F0 }
#define ENCODER_RESOLUTION 4

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))