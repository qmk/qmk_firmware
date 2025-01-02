/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

/* Indication led */
#define LED_MAC_OS_PIN A4
#define LED_WIN_OS_PIN A5
#define LED_OS_PIN_ON_STATE 1

#ifdef LED_MATRIX_ENABLE
/* RGB Matrix Driver Configuration */
#    define DRIVER_COUNT 1
#    define DRIVER_ADDR_1 0b1110100

/* RGB Matrix Configuration */
#    define LED_MATRIX_LED_COUNT (87 + 12)

/* Use first 7 channels of LED driver */
#    define PHASE_CHANNEL MSKPHASE_7CHANNEL

/* Set LED driver current */
#    define CKLED2001_CURRENT_TUNE \
        { 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50 }

/* turn off effects when suspended */
#    define LED_DISABLE_WHEN_USB_SUSPENDED

/* Enable Reactive Animation */
#    define LED_MATRIX_KEYPRESSES
#endif
