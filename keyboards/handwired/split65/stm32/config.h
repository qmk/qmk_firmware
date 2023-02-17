/* Copyright 2020-2021 PercyJW-2 <joris.wachsmuth@gmail.com>
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


// Audio
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

#define MATRIX_COL_PINS {A2, A1, A0, B8, B13, B14, B15, B9}
#define MATRIX_ROW_PINS {B5, B4, B3, B2, B1}

// COL2ROW, ROW2COL
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 100

// Feature diable options
//#define NO_DEBUG
//#define NO_PRINT

#define OLED_DISPLAY_128X64
