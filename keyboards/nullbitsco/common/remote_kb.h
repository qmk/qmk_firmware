/* Copyright 2021 Jay Greco
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

#include <stdint.h>
#include "action.h"

#define SERIAL_UART_BAUD 76800 //low error rate for 32u4 @ 16MHz

#define UART_PREAMBLE 0x69
#define UART_MSG_LEN  5
#define UART_NULL     0

#define IDX_PREAMBLE  0
#define IDX_KCLSB     1
#define IDX_KCMSB     2
#define IDX_PRESSED   3
#define IDX_CHECKSUM  4

#define IS_HID_KC(x) ((x > 0) && (x < 0xFF))
#define IS_RM_KC(x) ((x >= RM_BASE) && (x <= 0xFFFF))

#define RM_BASE 0xFFFF-16
enum remote_macros {
  RM_1 = RM_BASE,
  RM_2,  RM_3,
  RM_4,  RM_5,
  RM_6,  RM_7,
  RM_8,  RM_9,
  RM_10, RM_11,
  RM_12, RM_13,
  RM_14, RM_15,
};


// Public functions
void
 matrix_init_remote_kb(void),
 process_record_remote_kb(uint16_t keycode, keyrecord_t *record),
 matrix_scan_remote_kb(void);