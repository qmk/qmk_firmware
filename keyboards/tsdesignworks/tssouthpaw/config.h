/* Copyright 2025 TS Design Works LLC
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

// Dynamic macro configuration
#define DYNAMIC_MACRO_SIZE 128         // More efficient macro size

// RP2040 Settings
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Enable double-tap reset
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // LED for reset indication
