/* Copyright 2025 Jose M Zelezarof (git@zelezarof.ca)
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

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

/* https://docs.qmk.fm/drivers/serial#usart-full-duplex */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

/* https://docs.qmk.fm/features/split_keyboard#handedness-by-eeprom */
#define EE_HANDS

/* https://docs.qmk.fm/tap_hold#tapping-term */
#define TAPPING_TERM 250

/* https://docs.qmk.fm/tap_hold#flow-tap */
#define FLOW_TAP_TERM 150

/* https://docs.qmk.fm/tap_hold#chordal-hold */
#define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

/* https://docs.qmk.fm/platformdev_rp2040#double-tap */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
