/* Copyright 2021 Christoph Rehmann (crehmann)
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

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Using the right side as master
#define MASTER_RIGHT

#ifdef HAPTIC_ENABLE
// this configuration has no effect because the haptic exclusion is implemented with
// __attribute__((weak)) bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record)
// in the default keymap and reacts only to mouse clicks. 
//#define NO_HAPTIC_MOD
#define NO_HAPTIC_FN
#define NO_HAPTIC_ALPHA
#define NO_HAPTIC_PUNCTUATION
#define NO_HAPTIC_NAV 
#define NO_HAPTIC_NUMERIC
#define DRV_GREETING       alert_750ms
#define DRV_MODE_DEFAULT   sharp_tick1
#endif


#ifdef PS2_MOUSE_ENABLE
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BTN_RIGHT)   // using the right mouse button for scrolling (other buttons can be configured)
#define PS2_MOUSE_SCROLL_BTN_SEND 500
#endif