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

#ifdef LED_MATRIX_ENABLE
/* LED matrix driver configuration */
#    define DRIVER_COUNT 1
#    define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND
#    define LED_MATRIX_LED_COUNT 100

/* Set to infinit, which is use in USB mode by default */
#    define LED_MATRIX_TIMEOUT LED_MATRIX_TIMEOUT_INFINITE
/* Allow shutdown of led driver to save power */
#    define LED_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#    define LED_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

/* Indicatoon led */
#    define CAPS_LOCK_INDEX 55
#    define NUM_LOCK_INDEX 33
#    define LOW_BAT_IND_INDEX 91

/* LED Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
 */
#    define LED_MATRIX_KEYPRESSES

/* Use first 6 channels of LED driver */
#    define PHASE_CHANNEL MSKPHASE_7CHANNEL

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60 }

#endif
