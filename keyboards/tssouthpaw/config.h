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

 // LED indices for indicator LEDs
 #define CAPS_LOCK_LED  62  // LED index for Caps Lock indicator
 #define NUM_LOCK_LED   2   // LED index for Num Lock indicator
 #define MIC_MUTE_LED   3   // LED index for KC_MICMUTE
  
 // Work Timer LED indices
 #define WORK_TIMER_LED_START 4          // F1 key LED
 #define WORK_TIMER_LED_END   15         // F12 key LED
  
 // Work Timer EEPROM addresses
 // Using built-in wear leveling for RP2040
 #define EEPROM_WORK_TIMER_ACTIVE 32    // 1 byte - active state
 #define EEPROM_WORK_TIMER_START  33    // 4 bytes - start time
 #define EEPROM_WORK_TIMER_ELAPSED 37   // 4 bytes - elapsed work time
                                        // 4 bytes - total break time (37+4)
                                        // 1 byte - timer type (37+8) 
                                        // 1 byte - break state (37+9)
                                        // 4 bytes - break start time (37+10)
                                        // Total: 15 bytes
  
 // Work Timer Notification Configuration
 #define WORK_TIMER_NOTIFICATION_BRIGHTNESS 250  // Brightness for work timer notifications
  
 // Minimum brightness for timer notifications to ensure visibility
 #define RGB_MATRIX_MINIMUM_BRIGHTNESS 64  // Ensures timer notifications remain visible
  
 // Dynamic macro configuration
 #define DYNAMIC_MACRO_SIZE 128         // More efficient macro size
 
 // RP2040 Settings
 #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Enable double-tap reset
 #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms
 #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // LED for reset indication