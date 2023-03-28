/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#define BLE_NAME "BIOI C11 BLE"

#define MATRIX_ROW_PINS { D4, B3 }
#define MATRIX_COL_PINS { D0, D1, D5, B0, B2, D6 }

#define DIODE_DIRECTION COL2ROW

#define RGB_UG_CONTROL_PIN F0
#define BATT_LEVEL_PIN F7

#define RGBLIGHT_LIMIT_VAL 127

#define RGB_MATRIX_KEYRELEASES
#define RGB_DI_PIN B7
#define RGB_MATRIX_LED_COUNT 11

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))