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

#pragma once

#define MATRIX_ROW_PINS          { B12, B13, B14, B15, A8 , A9, A10}
#define MATRIX_COL_PINS          { B1, B0, A7, A6, A5, A4}
/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

// in col2row col is input, and row is output
// #define SPLIT_HAND_MATRIX_GRID A10, A4
// 68kohm
#define SPLIT_HAND_PIN              B10

/* connection */
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_RX_PIN B7     // USART RX pin
#define SERIAL_USART_TX_PIN B6     // USART TX pin

#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of TX and RX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20
