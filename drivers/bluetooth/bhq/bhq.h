/* Copyright 2024 keymagichorse
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

#include "stdint.h"
#include <stdbool.h>

// Error checking
#if !STM32_SERIAL_USE_USART1 && !STM32_SERIAL_USE_USART2 && !STM32_SERIAL_USE_USART3 && !STM32_SERIAL_USE_UART4 && !STM32_SERIAL_USE_UART5 && !STM32_SERIAL_USE_USART6 && !STM32_SERIAL_USE_UART7 && !STM32_SERIAL_USE_UART8 && !STM32_SERIAL_USE_LPUART1
#    error "BT driver activated but no USART/UART peripheral assigned"
#endif


#define PACKECT_HEADER_LEN 4
#define PACKET_MAX_LEN 256

// -------------------- bhq protocol Small terminal mode --------------------

#define BHQ_FRAME_HEADER_1  0x5D
#define BHQ_FRAME_HEADER_2  0x7E

#define BHQ_FRAME_END_1     0x5E

#define BHQ_ACK             0x51
#define BHQ_NOT_ACK         0x50
#define BHQ_CMD_TO_ACKCMD(value) ((value) |= (1 << 7))

#define BHQ_H_UINT16(a) (((a) >> 8) & 0xFF) 
#define BHQ_L_UINT16(a) ((a) & 0xFF)       
#define BHQ_BUILD_UINT16(loByte, hiByte) ((uint16_t)(((loByte) & 0x00FF)|(((hiByte) & 0x00FF)<<8)))

#define BHQ_SET_BIT_VALUE(var, xbit, value) ((value) ? ((var) |= (1 << (xbit))) : ((var) &= ~(1 << (xbit))))

#define BHQ_SUCCESS     0
// -------------------- bhq protocol Small terminal mode --------------------
#define BHQ_RUN_OR_INT_LEVEL       1             // Module operating status and qmk have the level status of data transmission       
#ifndef BHQ_RUN_STATE_INPUT_PIN
#    error "BHQ_RUN_STATE_INPUT_PIN is not defined"
#endif
#ifndef QMK_RUN_OUTPUT_PIN
#    error "QMK_RUN_OUTPUT_PIN is not defined"
#endif


void bhq_init(void);
void bhq_Disable(void);


void bhq_SetPairingMode(uint8_t host_index, uint8_t timeout_10s);
void bhq_OpenBleAdvertising(uint8_t host_index, uint8_t timeout_10s);
void bhq_CloseBleAdvertising(void);



void bhq_send_keyboard(uint8_t* report);
void bhq_send_nkro(uint8_t* report);
void bhq_send_consumer(uint16_t report);
void bhq_send_system(uint16_t report);
void bhq_send_mouse(uint8_t* report);
void bhq_send_hid_raw(uint8_t *data, uint8_t length);


void bhq_task(void);
