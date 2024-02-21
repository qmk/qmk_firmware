/* Copyright 2023 Florent Linguenheld (@FLinguenheld)
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

/* Flash */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET              // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // In ms in which the double tap can occur

/* OLED */
#undef OLED_FONT_H
#define OLED_FONT_H "./oled/glcdfont.c"

#define OLED_TIMEOUT 25000
#define OLED_BRIGHTNESS 50 // Protect my eyesss
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE

/* Auto shift ♥ */
#define AUTO_SHIFT_TIMEOUT 115
#define TAPPING_TERM 155

/* Unicode */
// #define UNICODE_SELECTED_MODES UC_LNX
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

/* leader */
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 280
#define LEADER_NO_TIMEOUT

/* Mouse */
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#define MK_C_OFFSET_0 1
#define MK_C_INTERVAL_0 12

#define MK_C_OFFSET_1 4
#define MK_C_INTERVAL_1 18

#define MK_C_OFFSET_UNMOD 13
#define MK_C_INTERVAL_UNMOD 15

#define MK_C_OFFSET_2 25
#define MK_C_INTERVAL_2 10

#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 160

#define MK_W_OFFSET_1 2
#define MK_W_INTERVAL_1 120

#define MK_W_OFFSET_UNMOD 4
#define MK_W_INTERVAL_UNMOD 70

#define MK_W_OFFSET_2 10
#define MK_W_INTERVAL_2 30
