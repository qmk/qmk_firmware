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

/* LED Matrix Driver Configuration */
#define CKLED2001_DRIVER_COUNT 1
#define DRIVER_ADDR_1 CKLED2001_I2C_ADDRESS_GND

/* Set LED driver current */
#define CKLED2001_CURRENT_TUNE \
    { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0 }

/* LED Matrix Configuration */
#define LED_MATRIX_LED_COUNT 108

/* Enable indicator LED*/
#define NUM_LED_INDEX 16
#define CAPS_LED_INDEX 17
#define MAC_LED_INDEX 18
#define WIN_LED_INDEX 19

/* turn off effects when suspended */
#define LED_DISABLE_WHEN_USB_SUSPENDED

// LED Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
// #if defined(LED_MATRIX_KEYPRESSES) || defined(LED_MATRIX_KEYRELEASES)
#define LED_MATRIX_KEYPRESSES
#define LED_MATRIX_KEYRELEASES
