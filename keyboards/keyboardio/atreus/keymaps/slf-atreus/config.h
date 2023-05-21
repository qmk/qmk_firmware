/* Copyright 2023 @PoweredByPorridge
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

#define AUTO_SHIFT_TIMEOUT 210

#define NO_AUTO_SHIFT_NUMERIC
// #define NO_AUTO_SHIFT_SPECIAL

// retro shift is auto shift on home row mods
// I no longer use home row mods, but do find this setting helps
// avoid 'fat fingered' keypresses.

// If RETRO_SHIFT is defined to a value, hold times greater 
// than that value will not produce a tap on release. This enables 
// modifiers to be held for combining with mouse clicks without 
// generating taps on release.
#define RETRO_SHIFT 425

// can also be defined without a value
// #define RETRO_SHIFT

// Configure the global tapping term (default: 200ms)
// Lower than 210 and I can't tap dance brackets without a run up.
#define TAPPING_TERM 210

#define TAPPING_TERM_PER_KEY

// Apply the modifier on keys that are tapped during a short hold of a modtap
// Prevents slurred typing (of home row mods)
#define PERMISSIVE_HOLD
