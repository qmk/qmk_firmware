/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */
#define MASTER_LEFT

#define DEBOUNCE 3

#define QUICK_TAP_TERM 0
#define PERMISSIVE_HOLD
#define TAPPING_TERM 150

// Configure Caps Word
#define DOUBLE_TAP_RSHIFT_TURNS_ON_CAPS_WORD // Custom function in process_caps_word.c
#define CAPS_WORD_IDLE_TIMEOUT 2500  // 2.5 seconds

// Enable button flashing
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 3000U // Timeout window in ms in which the double tap can occur.

#undef RGBLED_NUM

#define OLED_TIMEOUT 600000 // Timesout the OLED after 10mins

//#define DEBUG_MATRIX_SCAN_RATE
