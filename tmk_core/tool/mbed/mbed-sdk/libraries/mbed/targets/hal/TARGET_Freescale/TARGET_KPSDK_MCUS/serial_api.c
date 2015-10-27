/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "serial_api.h"

#if DEVICE_SERIAL

// math.h required for floating point operations for baud rate calculation
#include <math.h>
#include "mbed_assert.h"

#include <string.h>

#include "cmsis.h"
#include "pinmap.h"
#include "fsl_uart_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_uart_features.h"
#include "PeripheralPins.h"

/* TODO:
    putchar/getchar 9 and 10 bits support
*/
#ifndef UART3_BASE
#define UART_NUM    3
#else
#define UART_NUM    5
#endif

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    uint32_t uart_tx = pinmap_peripheral(tx, PinMap_UART_TX);
    uint32_t uart_rx = pinmap_peripheral(rx, PinMap_UART_RX);
    obj->index = pinmap_merge(uart_tx, uart_rx);
    MBED_ASSERT((int)obj->index != NC);

    uint32_t uartSourceClock = CLOCK_SYS_GetUartFreq(obj->index);

    CLOCK_SYS_EnableUartClock(obj->index);
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    UART_HAL_Init(uart_addrs[obj->index]);
    UART_HAL_SetBaudRate(uart_addrs[obj->index], uartSourceClock, 9600);
    UART_HAL_SetParityMode(uart_addrs[obj->index], kUartParityDisabled);
    #if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    UART_HAL_SetStopBitCount(uart_addrs[obj->index], kUartOneStopBit);
    #endif
    UART_HAL_SetBitCountPerChar(uart_addrs[obj->index], kUart8BitsPerChar);
    UART_HAL_EnableTransmitter(uart_addrs[obj->index]);
    UART_HAL_EnableReceiver(uart_addrs[obj->index]);

    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);

    if (tx != NC) {
        pin_mode(tx, PullUp);
    }
    if (rx != NC) {
        pin_mode(rx, PullUp);
    }

    if (obj->index == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
    while(!UART_HAL_IsTxDataRegEmpty(uart_addrs[obj->index]));
}

void serial_free(serial_t *obj) {
    serial_irq_ids[obj->index] = 0;
}

void serial_baud(serial_t *obj, int baudrate) {
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    UART_HAL_SetBaudRate(uart_addrs[obj->index], CLOCK_SYS_GetUartFreq(obj->index), (uint32_t)baudrate);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    UART_HAL_SetBitCountPerChar(uart_addrs[obj->index], (uart_bit_count_per_char_t)data_bits);
    UART_HAL_SetParityMode(uart_addrs[obj->index], (uart_parity_mode_t)parity);
    #if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    UART_HAL_SetStopBitCount(uart_addrs[obj->index], (uart_stop_bit_count_t)--stop_bits);
    #endif
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint32_t transmit_empty, uint32_t receive_full, uint32_t index) {
    if (serial_irq_ids[index] != 0) {
        if (transmit_empty)
            irq_handler(serial_irq_ids[index], TxIrq);

    if (receive_full)
        irq_handler(serial_irq_ids[index], RxIrq);
    }
}

void uart0_irq() {
    uart_irq(UART_HAL_IsTxDataRegEmpty(UART0_BASE), UART_HAL_IsRxDataRegFull(UART0_BASE), 0);
    if (UART_HAL_GetStatusFlag(UART0_BASE, kUartRxOverrun))
        UART_HAL_ClearStatusFlag(UART0_BASE, kUartRxOverrun);
}
void uart1_irq() {
    uart_irq(UART_HAL_IsTxDataRegEmpty(UART1_BASE), UART_HAL_IsRxDataRegFull(UART1_BASE), 1);
}

void uart2_irq() {
    uart_irq(UART_HAL_IsTxDataRegEmpty(UART2_BASE), UART_HAL_IsRxDataRegFull(UART2_BASE), 2);
}

#if (UART_NUM > 3)

void uart3_irq() {
    uart_irq(UART_HAL_IsTxDataRegEmpty(UART3_BASE), UART_HAL_IsRxDataRegFull(UART3_BASE), 3);
}

void uart4_irq() {
    uart_irq(UART_HAL_IsTxDataRegEmpty(UART4_BASE), UART_HAL_IsRxDataRegFull(UART4_BASE), 4);
}
#endif

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;

    switch (obj->index) {
        case 0: irq_n=UART0_RX_TX_IRQn; vector = (uint32_t)&uart0_irq; break;
        case 1: irq_n=UART1_RX_TX_IRQn; vector = (uint32_t)&uart1_irq; break;
        case 2: irq_n=UART2_RX_TX_IRQn; vector = (uint32_t)&uart2_irq; break;
#if (UART_NUM > 3)
        case 3: irq_n=UART3_RX_TX_IRQn; vector = (uint32_t)&uart3_irq; break;
        case 4: irq_n=UART4_RX_TX_IRQn; vector = (uint32_t)&uart4_irq; break;
#endif
    }
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    if (enable) {
        switch (irq) {
            case RxIrq: UART_HAL_SetRxDataRegFullIntCmd(uart_addrs[obj->index], true); break;
            case TxIrq: UART_HAL_SetTxDataRegEmptyIntCmd(uart_addrs[obj->index], true); break;
        }
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);

    } else { // disable
        int all_disabled = 0;
        SerialIrq other_irq = (irq == RxIrq) ? (TxIrq) : (RxIrq);
        switch (irq) {
            case RxIrq: UART_HAL_SetRxDataRegFullIntCmd(uart_addrs[obj->index], false); break;
            case TxIrq: UART_HAL_SetTxDataRegEmptyIntCmd(uart_addrs[obj->index], false); break;
        }
        switch (other_irq) {
            case RxIrq: all_disabled = UART_HAL_GetRxDataRegFullIntCmd(uart_addrs[obj->index]) == 0; break;
            case TxIrq: all_disabled = UART_HAL_GetTxDataRegEmptyIntCmd(uart_addrs[obj->index]) == 0; break;
        }
        if (all_disabled)
            NVIC_DisableIRQ(irq_n);
    }
}

int serial_getc(serial_t *obj) {
    while (!serial_readable(obj));
    uint8_t data;
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    UART_HAL_Getchar(uart_addrs[obj->index], &data);

    return data;
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    uint32_t uart_addrs[] = UART_BASE_ADDRS;
    UART_HAL_Putchar(uart_addrs[obj->index], (uint8_t)c);
}

int serial_readable(serial_t *obj) {
    uint32_t uart_address[] = UART_BASE_ADDRS;
    if (UART_HAL_GetStatusFlag(uart_address[obj->index], kUartRxOverrun))
        UART_HAL_ClearStatusFlag(uart_address[obj->index], kUartRxOverrun);
    return UART_HAL_IsRxDataRegFull(uart_address[obj->index]);
}

int serial_writable(serial_t *obj) {
    uint32_t uart_address[] = UART_BASE_ADDRS;
    if (UART_HAL_GetStatusFlag(uart_address[obj->index], kUartRxOverrun))
        UART_HAL_ClearStatusFlag(uart_address[obj->index], kUartRxOverrun);

    return UART_HAL_IsTxDataRegEmpty(uart_address[obj->index]);
}

void serial_clear(serial_t *obj) {
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    uint32_t uart_address[] = UART_BASE_ADDRS;
    UART_HAL_SetBreakCharCmd(uart_address[obj->index], true);
}

void serial_break_clear(serial_t *obj) {
    uint32_t uart_address[] = UART_BASE_ADDRS;
    UART_HAL_SetBreakCharCmd(uart_address[obj->index], false);
}

#endif
