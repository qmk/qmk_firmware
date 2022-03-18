/* Copyright 2018 MakotoKurauchi
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

#include "helix.h"

bool is_mac_mode(void);
void set_mac_mode_kb(bool macmode);

#ifndef SPLIT_KEYBOARD
    extern bool is_helix_master(void);
    #define is_keyboard_master() is_helix_master()
#endif

// Each keymap.c should use is_keyboard_master() instead of 'is_master', 'has_usb()'.
// But keep 'is_master' for a while for backwards compatibility
//  for the old keymap.c.
extern uint8_t is_master; // 'is_master' will be obsolete, it is recommended to use 'is_keyboard_master ()' instead.
#define has_usb() is_keyboard_master()

#if MATRIX_ROWS == 8 // HELIX_ROWS == 4
    #ifndef FLIP_HALF
        // Standard Keymap
        // (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
        #define LAYOUT( \
            L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
            L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
            L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
            L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35 \
        ) { \
            { L00, L01, L02, L03, L04, L05, KC_NO }, \
            { L10, L11, L12, L13, L14, L15, KC_NO }, \
            { L20, L21, L22, L23, L24, L25, KC_NO }, \
            { L30, L31, L32, L33, L34, L35, L36 }, \
            { R05, R04, R03, R02, R01, R00, KC_NO }, \
            { R15, R14, R13, R12, R11, R10, KC_NO }, \
            { R25, R24, R23, R22, R21, R20, KC_NO }, \
            { R35, R34, R33, R32, R31, R30, R36 } \
        }
    #else
        // Keymap with right side flipped
        // (TRRS jack on both halves are to the right)
        #define LAYOUT( \
            L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
            L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
            L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
            L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35 \
        ) { \
            { L00, L01, L02, L03, L04, L05, KC_NO }, \
            { L10, L11, L12, L13, L14, L15, KC_NO }, \
            { L20, L21, L22, L23, L24, L25, KC_NO }, \
            { L30, L31, L32, L33, L34, L35, L36 }, \
            { KC_NO, R00, R01, R02, R03, R04, R05 }, \
            { KC_NO, R10, R11, R12, R13, R14, R15 }, \
            { KC_NO, R20, R21, R22, R23, R24, R25 }, \
            { R36, R30, R31, R32, R33, R34, R35 } \
        }
    #endif
#else // HELIX_ROWS == 5
    #ifndef FLIP_HALF
        // Standard Keymap
        // (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35, \
    L40, L41, L42, L43, L44, L45, L46, R46, R40, R41, R42, R43, R44, R45 \
) { \
    { L00, L01, L02, L03, L04, L05, KC_NO }, \
    { L10, L11, L12, L13, L14, L15, KC_NO }, \
    { L20, L21, L22, L23, L24, L25, KC_NO }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { L40, L41, L42, L43, L44, L45, L46 }, \
    { R05, R04, R03, R02, R01, R00, KC_NO }, \
    { R15, R14, R13, R12, R11, R10, KC_NO }, \
    { R25, R24, R23, R22, R21, R20, KC_NO }, \
    { R35, R34, R33, R32, R31, R30, R36 }, \
    { R45, R44, R43, R42, R41, R40, R46 } \
}
    #else
        // Keymap with right side flipped
        // (TRRS jack on both halves are to the right)
        #define LAYOUT( \
            L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
            L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
            L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
            L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35, \
            L40, L41, L42, L43, L44, L45, L46, R46, R40, R41, R42, R43, R44, R45 \
        ) { \
            { L00, L01, L02, L03, L04, L05, KC_NO }, \
            { L10, L11, L12, L13, L14, L15, KC_NO }, \
            { L20, L21, L22, L23, L24, L25, KC_NO }, \
            { L30, L31, L32, L33, L34, L35, L36 }, \
            { L40, L41, L42, L43, L44, L45, L46 }, \
            { KC_NO, R00, R01, R02, R03, R04, R05 }, \
            { KC_NO, R10, R11, R12, R13, R14, R15 }, \
            { KC_NO, R20, R21, R22, R23, R24, R25 }, \
            { R36, R30, R31, R32, R33, R34, R35 }, \
            { R46, R40, R41, R42, R43, R44, R45 } \
        }
    #endif
#endif
