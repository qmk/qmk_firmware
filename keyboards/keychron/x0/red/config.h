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
/* RGB Matrix Driver Configuration */
#    define DRIVER_COUNT 1
#    define SNLED27351_I2C_ADDRESS_1 0b1110100

/* RGB Matrix Configuration */
#    define LED_MATRIX_LED_COUNT 35
#    define LED_MATRIX_CENTER \
        { 28, 16 }

/* Scan phase of led driver set as MSKPHASE_6CHANNEL(defined as 0x03 in CKLED2001.h) */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_6_CHANNEL
#    define SNLED27351_CURRENT_TUNE \
        { 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60 }

/* turn off effects when suspended */
#    define LED_DISABLE_WHEN_USB_SUSPENDED

// LED Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
// #if defined(LED_MATRIX_KEYPRESSES) || defined(LED_MATRIX_KEYRELEASES)
#    define LED_MATRIX_KEYPRESSES
#    define LED_MATRIX_KEYRELEASES
#endif
