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
#include "debug.h"

#include "km_printf.h"
#define bhq_printf(format, ...) km_printf(format, ##__VA_ARGS__)


// Error checking
#if !STM32_SERIAL_USE_USART1 && !STM32_SERIAL_USE_USART2 && !STM32_SERIAL_USE_USART3 && !STM32_SERIAL_USE_UART4 && !STM32_SERIAL_USE_UART5 && !STM32_SERIAL_USE_USART6 && !STM32_SERIAL_USE_UART7 && !STM32_SERIAL_USE_UART8 && !STM32_SERIAL_USE_LPUART1
#    error "BT driver activated but no USART/UART peripheral assigned"
#endif

typedef struct bhkDevConfigInfo_t
{
    uint8_t  vendor_id_source; /* 0: From Bluetooth SIG, 1: From USB-IF */
    uint16_t verndor_id;       /* No effect, the vendor ID is 0x3434 */
    uint16_t product_id;

    uint16_t le_connection_interval_min;        // Minimum Connection interval Connection interval (unit: 1.25ms)
    uint16_t le_connection_interval_max;        // Maximum Connection interval Connection interval (unit: 1.25ms)
    uint16_t le_connection_interval_timeout;    // Connection interval timeout
    uint8_t  tx_poweer;                         // tx power

    uint8_t     mk_is_read_battery_voltage;     // Whether the battery voltage is read by the module.
    uint8_t     mk_adc_pga;                     // ADC pag
    uint16_t    mk_rvd_r1;                      // resistive voltage divider  
    uint16_t    mk_rvd_r2;

    uint16_t sleep_1_s;                         // light sleep (unit: 1s)
    uint16_t sleep_2_s;                         // deep  sleep (unit: 1s)

    uint8_t bleNameStrLength;                   // ble name max length: 31
    uint8_t bleNameStr[32];
} bhkDevConfigInfo_t;
enum { 
    BHQ_ACK_RUN_STA_CMDID = 0x93,
    BHQ_ACK_LED_LOCK_CMDID = 0x26
};


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

#define BHQ_GET_BLE_ADVERT_STA(var) ((var) & 0x01)          // 0x13->0x93:bat[1]->bit0:     ble Advert state
#define BHQ_GET_BLE_CONNECT_STA(var) (((var) >> 1) & 0x03)  // 0x13->0x93:bat[1]->bit1~2:   ble connect state
#define BHQ_GET_BLE_PAIRING_STA(var) (((var) >> 3) & 0x01)  // 0x13->0x93:bat[1]->bit3:     ble Pairing state

#define BHQ_SUCCESS     0


// -------------------- bhq protocol Small terminal mode --------------------
#define BHQ_RUN_OR_INT_LEVEL       1             // Module operating status and qmk have the level status of data transmission       
#ifndef BHQ_IQR_PIN
#    error "BHQ_IQR_PIN is not defined"
#endif
#ifndef BHQ_INT_PIN
#    error "BHQ_INT_PIN is not defined"
#endif


void bhq_init(void);
void bhq_Disable(void);
void BHQ_SendCmd(uint8_t isack, uint8_t *dat, uint8_t datLength);

void bhq_ConfigRunParam(bhkDevConfigInfo_t parma);

void BHQ_Protocol_Process_user(uint8_t *dat, uint16_t length) ;


void bhq_SetPairingMode(uint8_t host_index, uint16_t timeout_1S);
void bhq_OpenBleAdvertising(uint8_t host_index, uint16_t timeout_1S);
void bhq_AnewOpenBleAdvertising(uint8_t host_index, uint16_t timeout_1S);
void bhq_CloseBleAdvertising(void);
void bhq_switch_rf_easy_kb(void);

void bhq_update_battery_percent(uint8_t percent, uint16_t bat_mv);



void bhq_send_keyboard(uint8_t* report);
void bhq_send_nkro(uint8_t* report);
void bhq_send_consumer(uint16_t report);
void bhq_send_system(uint16_t report);
void bhq_send_mouse(uint8_t* report);
void bhq_send_hid_raw(uint8_t *data, uint8_t length);


void bhq_task(void);
