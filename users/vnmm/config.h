/*
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

#define RGB_MATRIX_TIMEOUT 1200000     // 20 minutes (20 * 60 * 1000ms)

// When caps lock is pressed, the letter keys, caps lock, and both shift keys, will light up this color.
#define CAPS_LOCK_INDICATOR_COLOR RGB_RED

// When caps lock is pressed, all other keys will light up this color. If undefined, they keys will adhere to the rgb profile
// #define CAPS_LOCK_INDICATOR_OTHER RGB_WHITE

// If defined, all alphabet keys will light up, otherwise just caps lock.
#define CAPS_LOCK_INDICATOR_LIGHT_ALPHAS

// If defined, keys not defined in the current layer will turn off their RGB
#define FN_LAYER_TRANSPARENT_KEYS_OFF

// Below added per: https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#suspended-state-id-suspended-state
#define RGB_DISABLE_WHEN_USB_SUSPENDED

