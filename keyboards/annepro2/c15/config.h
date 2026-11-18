/*
 * Copyright (c) 2018 Charlie Waters
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

#include "pin_defs.h"

#define LINE_UART_TX B0  // Master TX, LED RX
#define LINE_UART_RX B1  // Master RX, LED TX

#define LINE_BT_UART_TX A4  // Master TX, BLE RX
#define LINE_BT_UART_RX A5  // Master RX, BLE TX

// Obins stock firmware has something similar to this already enabled, but disabled by default in QMK
#define PERMISSIVE_HOLD

// SPI configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A0
#define SPI_MOSI_PIN A1
#define SPI_MISO_PIN A2

// Flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B6
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE 4096
#define EXTERNAL_FLASH_BLOCK_SIZE 4096
#define EXTERNAL_FLASH_SIZE (256 * 1024) // 2M-bit flash size

/* Give wait_us() a hardware timer to poll.
 *
 * Without this it falls back to chThdSleepMicroseconds(), because this is a
 * Cortex-M0 and has no DWT cycle counter for chSysPolledDelayX(). With
 * CH_CFG_ST_FREQUENCY at 1000 that rounds every delay up to a whole 1ms
 * tick, and matrix_output_unselect_delay() asks for 30us once per row: the
 * matrix scanned at exactly 200Hz, one millisecond per row.
 *
 * At 200Hz a 5ms DEBOUNCE is a single sample, which is why keys chattered.
 */
#define WAIT_US_TIMER GPTD_BFTM0
