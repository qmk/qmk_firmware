/* Copyright 2018 Carlos Filoteo
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

// place overrides here
#define USB_MAX_POWER_CONSUMPTION 30
// #define MK_3_SPEED
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_TIME_TO_MAX 10
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSKEY_WHEEL_TO_MAX 5
// #define RETRO_TAPPING
// #define ONESHOT_TAP_TOGGLE 2 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 3000  /* Time (in ms) before the one shot key is released */
#define TAPPING_TERM 250	/* Custom max time between taps for Tap Dance */
#define IGNORE_MOD_TAP_INTERRUPT
// #define LEADER_TIMEOUT 300
// #define LEADER_PER_KEY_TIMING