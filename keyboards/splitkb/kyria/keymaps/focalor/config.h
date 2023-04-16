/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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
//QMK
#define AUTO_SHIFT_TIMEOUT 250
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC
#define TAPPING_TERM 175
#define IGNORE_MOD_TAP_INTERRUPT
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
//RP2040
#define RP2040_FLASH_W25Q080
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
//OLED SETTING
#define OLED_SCROLL_TIMEOUT 500
#define OLED_BRIGHTNESS 255

#define SPLIT_LED_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR