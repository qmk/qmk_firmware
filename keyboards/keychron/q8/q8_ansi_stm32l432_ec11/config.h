/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0181
#define DEVICE_VER      0x0100

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 52
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in CKLED2001.h) */
#define PHASE_CHANNEL MSKPHASE_9CHANNEL

/* Encoder used pins */
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { B4 }

/* Specifies the number of pulses the encoder registers between each detent */
#define ENCODER_RESOLUTION 4
