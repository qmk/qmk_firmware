/*
Copyright 2015 Jun Wako <wakojun@gmail.com> <4sStylZ@protonmail.ch>

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


// Originally made for a Teensy 2++
#define MATRIX_COL_PINS { F0, E6, E7, B0, B1, B2, B3, B4, B5, B6, D3, D0, D1, D2 }
#define MATRIX_ROW_PINS { E0, E1, C0, C1, C2 }

#define DIODE_DIRECTION COL2ROW

/* Enable the space-cadet options */
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_PGUP
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_PGDN
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_HOME
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_END

/* Enable double tab */
#define TAPPING_TERM 175
