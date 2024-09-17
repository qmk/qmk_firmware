/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix Driver Configuration */
#    define DRIVER_COUNT 2
#    define DRIVER_ADDR_1 0b1110111
#    define DRIVER_ADDR_2 0b1110100

/* RGB Matrix Configuration */
#    define DRIVER_1_LED_COUNT 29
#    define DRIVER_2_LED_COUNT 36
#    define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_COUNT + DRIVER_2_LED_COUNT)

/* Set to infinite, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE

/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48

#    define DIM_CAPS_LOCK
#    define CAPS_LOCK_INDEX 28
#    define LOW_BAT_IND_INDEX 59

#    ifdef KC_BLUETOOTH_ENABLE
#        undef HOST_LED_MATRIX_LIST
#        define HOST_LED_MATRIX_LIST \
            { 16, 17, 18 }
#    endif

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

/* Use first 9 channels of LED driver */
#    define PHASE_CHANNEL MSKPHASE_9CHANNEL

/* Set LED driver current */
#    define CKLED2001_CURRENT_TUNE \
        { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 }
#endif
