/* Copyright 2021 Dave Vandyke <kzar@kzar.co.uk>
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


// #undef LED_COMPOSE_PIN
// #define LEADER_PER_KEY_TIMING
// #define LEADER_TIMEOUT 250
#define TAPPING_TERM 200

// For TT swap hands SH_TT keycode
#define TAPPING_TOGGLE 2

// Enabling IGNORE_MOD_TAP_INTERRUPT is recommended when using Mod-Tap on alphanumeric keys to avoid hold function taking precendence when the next key is pressed quickly.

#define IGNORE_MOD_TAP_INTERRUPT
#define GRAVE_ESC_ALT_OVERRIDE
#define MK_KINETIC_SPEED0s0w

// Redefine Product and Vendor IDs for Apple Fn Key patch to work
// Anything from this list should work: https://usb-ids.gowdy.us/read/UD/05ac

#undef VENDOR_ID
#define VENDOR_ID 0x05AC
#undef PRODUCT_ID
#define PRODUCT_ID 0x0267

// Activate Command with Left Ctrl + Right Ctrl (and B key) because using both shift keys plus B is intercepted by the CAPSWORD module.
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL)