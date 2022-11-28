/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

/* RGB Matrix Driver Configuration */
#define DRIVER_COUNT 2
#define DRIVER_ADDR_1 0b1110111
#define DRIVER_ADDR_2 0b1110100

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 31
#define DRIVER_2_LED_TOTAL 30
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in CKLED2001.h) */
#define PHASE_CHANNEL MSKPHASE_9CHANNEL
#define CKLED2001_CURRENT_TUNE \
    { 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60 }

/* Enable CapsLcok LED*/
#define CAPS_LOCK_LED_INDEX 28
