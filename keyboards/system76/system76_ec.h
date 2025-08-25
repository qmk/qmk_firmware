/*
 * Copyright (C) 2022-2025 Jimmy Cassis <KernelOops@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

enum Command {
    CMD_PROBE         = 1,  // Probe for System76 EC protocol
    CMD_BOARD         = 2,  // Read board string
    CMD_VERSION       = 3,  // Read version string
    CMD_RESET         = 6,  // Reset to bootloader
    CMD_KEYMAP_GET    = 9,  // Get keyboard map index
    CMD_KEYMAP_SET    = 10, // Set keyboard map index
    CMD_LED_GET_VALUE = 11, // Get LED value by index
    CMD_LED_SET_VALUE = 12, // Set LED value by index
    CMD_LED_GET_COLOR = 13, // Get LED color by index
    CMD_LED_SET_COLOR = 14, // Set LED color by index
    CMD_LED_GET_MODE  = 15, // Get LED matrix mode and speed
    CMD_LED_SET_MODE  = 16, // Set LED matrix mode and speed
    CMD_MATRIX_GET    = 17, // Get currently pressed keys
    CMD_LED_SAVE      = 18, // Save LED settings to ROM
    CMD_SET_NO_INPUT  = 19, // Enable/disable no input mode
};

void system76_ec_rgb_eeprom(bool write);
void system76_ec_rgb_layer(layer_state_t state);
#ifdef SYSTEM76_EC
void system76_ec_unlock(void);
#endif
bool system76_ec_is_unlocked(void);
