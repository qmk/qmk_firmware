/* Copyright 2025 MHooijberg
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

#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0

#if defined(CAPS_WORD_ENABLE )
    #define IS_COMMAND() (get_mods() == MOD_MASK_CTRL) // Activate Command with Left Ctrl + Right Ctrl.
    // #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD          // Activate by pressing Left Shift + Right Shift
    // #define CAPS_WORD_IDLE_TIMEOUT 3000             // Caps Word turns off automatically if no keys are pressed for CAPS_WORD_IDLE_TIMEOUT milliseconds.
    // #define CAPS_WORD_INVERT_ON_SHIFT               // Pressing the Shift key continues Caps Word and inverts the shift state.
    // #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD     // Activate by double tapping Left Shift
#endif

// #define COMBO_TERM 40 // Set the timeout period.


#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_TIMEOUT 3000