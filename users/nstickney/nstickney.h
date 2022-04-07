/* Copyright 2021 @nstickney
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
#include QMK_KEYBOARD_H

// Specialty keycodes
#define CC_ESC LCTL_T(KC_ESC)
#define CC_QUOT RCTL_T(KC_QUOT)
#define AC_SLSH LALT_T(KC_SLSH)
#define AC_EQL RALT_T(KC_EQL)
#define FC_BSLS LT(FCTN, KC_BSLS)
#define FC_MINS LT(FCTN, KC_MINS)

// Layers
enum {
    BASE,  // Base layer
    SYMB,  // Symbols
    NUMP,  // Numpad
    FCTN   // Function
};

// Tap dance
enum {
    LOCKS,  // Activate NUM/CAPS/SCROLL lock
    LAYERS  // Activate NUMP and SYMB layers
};
