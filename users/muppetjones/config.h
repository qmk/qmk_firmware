/* Copyright 2020 Stephen J. Bush @muppetjones
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

#ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 16
#    define RGBLIGHT_VAL_STEP 16
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SLEEP
// #    define RGBLIGHT_LAYERS
#endif

#ifdef TAP_DANCE_ENABLE
// Change "hold" time (default is 200 ms)
// -- used for tap dance and other tap mods
#    define TAPPING_TERM 175

// Prevent normal rollover on alphas from accidentally triggering mods.
#    define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#    define TAPPING_FORCE_HOLD

#endif


#define COMBO_COUNT 3
#define COMBO_TERM 40
