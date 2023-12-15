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

// All of these config options can be changed by keyboard in their config.h
// These are all just the defaults I like for most of my keyboards

#ifndef RGB_MATRIX_TIMEOUT
// If the keyboard is unused for 20 minutes then just turn off RGB
#    define RGB_MATRIX_TIMEOUT 1200000 // 20 minutes (20 * 60 * 1000ms)

#endif

#ifndef CAPS_LOCK_INDICATOR_COLOR
// When caps lock is pressed, the letter keys, caps lock, and both shift keys, will light up this color.
#    define CAPS_LOCK_INDICATOR_COLOR RGB_RED
#endif

#ifndef SHIFT_INDICATOR_COLOR
// If defined also light up alphabet keys when either shift is held
#    define SHIFT_INDICATOR_COLOR RGB_WHITE
#endif

#ifndef CAPS_LOCK_INDICATOR_OTHER
// When caps lock is pressed, all other keys will light up this color
// #define CAPS_LOCK_INDICATOR_OTHER RGB_WHITE
#endif

#ifndef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
// All alphabet keys will light up, othe rwise just caps lock.
#    define CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
#endif

#ifndef FN_LAYER_TRANSPARENT_KEYS_COLOR
// Keys not defined in the current layer will use this color
#    define FN_LAYER_TRANSPARENT_KEYS_COLOR RGB_OFF
#endif

// Keys defined in the current layer will use this color
#ifndef FN_LAYER_KEYS_COLOR
// #define FN_LAYER_KEYS_COLOR RGB_WHITE
#endif

#ifndef CURRENT_LAYER_INDICATOR_COLOR
// If a key on a FN layer changes the default layer to the current layer, light up this color
#    define CURRENT_LAYER_INDICATOR_COLOR RGB_WHITE
#endif

#ifndef NKRO_INDICATOR_COLOR
// If NKRO is enabled, the key on the fn layer that toggles it will light up this color
#    define NKRO_INDICATOR_COLOR RGB_WHITE
#endif

// Don't light up my whole room when the pc is asleep
#ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
