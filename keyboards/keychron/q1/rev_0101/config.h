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
#define PRODUCT_ID      0x0101
#define DEVICE_VER      0x0100

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { D5, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4, F1, F0 }

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 59
#define DRIVER_2_LED_TOTAL 23
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* Encoder used pins */
#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B7 }

/* Specifies the number of pulses the encoder registers between each detent */
#define ENCODER_RESOLUTION 4
