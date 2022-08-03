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

#include "stdint.h"

#ifdef BT_DRIVER_UART_BANK
#    define BT_DRIVER_UART_TX_BANK BT_DRIVER_UART_BANK
#    define BT_DRIVER_UART_RX_BANK BT_DRIVER_UART_BANK
#endif

#ifndef BT_DRIVER_UART_TX_BANK
#    define BT_DRIVER_UART_TX_BANK GPIOA
#endif

#ifndef BT_DRIVER_UART_RX_BANK
#    define BT_DRIVER_UART_RX_BANK GPIOA
#endif

#ifndef BT_DRIVER_UART_TX
#    define BT_DRIVER_UART_TX 2
#endif

#ifndef BT_DRIVER_UART_RX
#    define BT_DRIVER_UART_RX 3
#endif

#ifndef BT_DRIVER
#    define BT_DRIVER SD2
#endif

#ifdef USE_GPIOV1
#    ifndef BT_DRIVER_UART_TX_PAL_MODE
#        define BT_DRIVER_UART_TX_PAL_MODE PAL_MODE_STM32_ALTERNATE_PUSHPULL
#    endif
#    ifndef BT_DRIVER_UART_RX_PAL_MODE
#        define BT_DRIVER_UART_RX_PAL_MODE PAL_MODE_STM32_ALTERNATE_PUSHPULL
#    endif
#else
// The default PAL alternate modes are used to signal that the pins are used for I2C
#    ifndef BT_DRIVER_UART_TX_PAL_MODE
#        define BT_DRIVER_UART_TX_PAL_MODE 7
#    endif
#    ifndef BT_DRIVER_UART_RX_PAL_MODE
#        define BT_DRIVER_UART_RX_PAL_MODE 7
#    endif
#endif

// Error checking
#if !STM32_SERIAL_USE_USART1 && !STM32_SERIAL_USE_USART2 && !STM32_SERIAL_USE_USART3 && !STM32_SERIAL_USE_UART4 && !STM32_SERIAL_USE_UART5 && !STM32_SERIAL_USE_USART6 && !STM32_SERIAL_USE_UART7 && !STM32_SERIAL_USE_UART8 && !STM32_SERIAL_USE_LPUART1
#    error "BT driver activated but no USART/UART peripheral assigned"
#endif

#define PACKECT_HEADER_LEN 5
#define BDA_LEN 6
#define PACKET_MAX_LEN 64

enum { 
    PAIRING_MODE_DEFAULT = 0x00, 
    PAIRING_MODE_JUST_WORK, 
    PAIRING_MODE_PASSKEY_ENTRY, 
    PAIRING_MODE_LESC_OR_SSP, 
    PAIRING_MODE_INVALID 
};

enum {
    BT_MODE_DEFAUL,
    BT_MODE_CLASSIC,
    BT_MODE_LE,     // Note: CKBT51 doesn't support BLE
    BT_MODE_INVALID,
};

typedef struct {
    uint8_t     hostIndex;
    uint16_t    timeout;     /* Pairing timeout, valid value range from 30 to 3600 seconds, 0 for default */
    uint8_t     pairingMode; /* 0: default, 1: Just Works, 2: Passkey Entry */
    uint8_t     BRorLE;      /* Only available for dual mode module. Keep 0 for single mode module */
    uint8_t     txPower;     /* Only available for BLE module */
    const char* leName;      /* Only available for BLE module */
} pairing_param_t;

typedef struct {
    uint8_t  type;
    uint16_t full_votage;
    uint16_t empty_voltage;
    uint16_t shutdown_voltage;
} battery_param_t;

typedef struct {
    uint8_t  model_name[11];
    uint8_t  mode;
    uint8_t  bluetooth_version;
    uint8_t  firmware_version[11];
    uint8_t  hardware_version[11];
    uint16_t cmd_set_verson;
} __attribute__((packed)) module_info_t;

typedef struct {
    uint8_t  event_mode; /* Must be 0x02 */
    uint16_t connected_idle_timeout;
    uint16_t pairing_timeout;   /* Range: 30 ~ 3600 second, 0 for default */
    uint8_t  pairing_mode;      /* 0: default, 1: Just Works, 2: Passkey Entry */
    uint16_t reconnect_timeout; /* 0: default, 0xFF: Unlimited time, 2 ~ 254 seconds */
    uint8_t  report_rate;       /* 90 or 133 */
    uint8_t  rsvd1;
    uint8_t  rsvd2;
    uint8_t  vendor_id_source; /* 0: From Bluetooth SIG, 1: From USB-IF */
    uint16_t verndor_id;       /* No effect, the vendor ID is 0x3434 */
    uint16_t product_id;
    /* Below parametes is only available for BLE module  */
    uint16_t le_connection_interval_min;
    uint16_t le_connection_interval_max;
    uint16_t le_connection_interval_timeout;
} __attribute__((packed)) module_param_t;

void ckbt51_init(bool wakeup_from_low_power_mode);
void ckbt51_send_cmd(uint8_t* payload, uint8_t len, bool ack_enable);

void ckbt51_send_keyboard(uint8_t* report);
void ckbt51_send_nkro(uint8_t* report);
void ckbt51_send_consumer(uint16_t report);
void ckbt51_send_system(uint16_t report);

void ckbt51_become_discoverable(uint8_t host_idx, void* param);
void ckbt51_connect(uint8_t hostIndex, uint16_t timeout);
void ckbt51_disconnect(void);
void ckbt51_switch_host(uint8_t hostIndex);
void ckbt51_read_state_reg(uint8_t reg, uint8_t len);

void ckbt51_get_info(module_info_t* info);
void ckbt51_set_param(module_param_t* param);
void ckbt51_get_param(module_param_t* param);
void ckbt51_set_local_name(const char* name);
void ckbt51_get_local_name(char* name);

void ckbt51_factory_reset(void);
void ckbt51_int_pin_test(bool enable);
void ckbt51_dfu_rx(uint8_t* data, uint8_t length);

void ckbt51_task(void);

