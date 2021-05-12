/* Copyright 2021 Jessica Sullivan and Don Kjer 
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

#include "quantum.h"

#ifdef KEYBOARD_durgod_dgk6x_hades
#   include "hades.h"
#endif

#ifndef WINLOCK_DISABLED
// Define the TGUI key here so it is available in QMK configurator
enum DGK6X_keycodes {
    KC_TGUI = SAFE_RANGE,   // Toggle between GUI Lock or Unlock
    NEW_SAFE_RANGE
};

#undef SAFE_RANGE
#define SAFE_RANGE NEW_SAFE_RANGE
#endif /* WINLOCK_DISABLED */

/* Function Prototype */
void off_all_leds(void);
void on_all_leds(void);

