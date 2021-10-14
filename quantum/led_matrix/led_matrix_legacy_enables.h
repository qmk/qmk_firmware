/* Copyright 2021 QMK
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

// to-do: remove this

#pragma once

#ifndef DISABLE_LED_MATRIX_ALPHAS_MODS
#    define ENABLE_LED_MATRIX_ALPHAS_MODS
#endif
#ifndef DISABLE_LED_MATRIX_BREATHING
#    define ENABLE_LED_MATRIX_BREATHING
#endif
#ifndef DISABLE_LED_MATRIX_BAND
#    define ENABLE_LED_MATRIX_BAND
#endif
#ifndef DISABLE_LED_MATRIX_BAND_PINWHEEL
#    define ENABLE_LED_MATRIX_BAND_PINWHEEL
#endif
#ifndef DISABLE_LED_MATRIX_BAND_SPIRAL
#    define ENABLE_LED_MATRIX_BAND_SPIRAL
#endif
#ifndef DISABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#endif
#ifndef DISABLE_LED_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
#endif
#ifndef DISABLE_LED_MATRIX_CYCLE_OUT_IN
#    define ENABLE_LED_MATRIX_CYCLE_OUT_IN
#endif
#ifndef DISABLE_LED_MATRIX_DUAL_BEACON
#    define ENABLE_LED_MATRIX_DUAL_BEACON
#endif
#if defined(LED_MATRIX_KEYREACTIVE_ENABLED)
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
#    endif
#    ifndef DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    endif
#    ifndef DISABLE_LED_MATRIX_SPLASH
#        define ENABLE_LED_MATRIX_SPLASH
#    endif
#    ifndef DISABLE_LED_MATRIX_MULTISPLASH
#        define ENABLE_LED_MATRIX_MULTISPLASH
#    endif
#endif
#ifndef DISABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#    define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#endif
#ifndef DISABLE_LED_MATRIX_WAVE_UP_DOWN
#    define ENABLE_LED_MATRIX_WAVE_UP_DOWN
#endif
