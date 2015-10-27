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
#include "mbed_assert.h"
#include "serial_api.h"

// math.h required for floating point operations for baud rate calculation
#include <math.h>

#include <string.h>

#include "cmsis.h"
#include "pinmap.h"
#include "clk_freqs.h"
#include "PeripheralPins.h"

//Devices either user UART0 or UARTLP
#ifndef UARTLP_BASES
    #define UARTLP_C2_RE_MASK        UART0_C2_RE_MASK
    #define UARTLP_C2_TE_MASK        UART0_C2_TE_MASK
    #define UARTLP_BDH_SBNS_MASK    UART0_BDH_SBNS_MASK
    #define    UARTLP_BDH_SBNS_SHIFT    UART0_BDH_SBNS_SHIFT
    #define UARTLP_S1_TDRE_MASK        UART0_S1_TDRE_MASK
    #define UARTLP_S1_OR_MASK        UART0_S1_OR_MASK
    #define UARTLP_C2_RIE_MASK        UART0_C2_RIE_MASK
    #define UARTLP_C2_TIE_MASK        UART0_C2_TIE_MASK
    #define UARTLP_C2_SBK_MASK        UART0_C2_SBK_MASK
    #define UARTLP_S1_RDRF_MASK        UART0_S1_RDRF_MASK
#endif

#ifdef UART2
    #define UART_NUM        3
#else
    #define UART_NUM        1
#endif

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    // determine the UART to use
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);
    UARTName uart = (UARTName)pinmap_merge(uart_tx, uart_rx);
    MBED_ASSERT((int)uart != NC);

    obj->uart = (UARTLP_Type *)uart;
    // enable clk
    switch (uart) {
        case UART_0: if (mcgpllfll_frequency() != 0)                    //PLL/FLL is selected
                        SIM->SOPT2 |= (1<<SIM_SOPT2_UART0SRC_SHIFT);
                     else
                        SIM->SOPT2 |= (2<<SIM_SOPT2_UART0SRC_SHIFT);
                     SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; break;
    #if UART_NUM > 1
        case UART_1: SIM->SCGC4 |= SIM_SCGC4_UART1_MASK; break;
        case UART_2: SIM->SCGC4 |= SIM_SCGC4_UART2_MASK; break;
    #endif
    }
    // Disable UART before changing registers
    obj->uart->C2 &= ~(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);
    
    switch (uart) {
        case UART_0: obj->index = 0; break;
    #if UART_NUM > 1
        case UART_1: obj->index = 1; break;
        case UART_2: obj->index = 2; break;
    #endif
    }

    // set default baud rate and format
    serial_baud  (obj, 9600);
    serial_format(obj, 8, ParityNone, 1);

    // pinout the chosen uart
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);

    // set rx/tx pins in PullUp mode
    if (tx != NC) {
        pin_mode(tx, PullUp);
    }
    if (rx != NC) {
        pin_mode(rx, PullUp);
    }

    obj->uart->C2 |= (UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);

    if (uart == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj) {
    serial_irq_ids[obj->index] = 0;
}

// serial_baud
//
// set the baud rate, taking in to account the current SystemFrequency
void serial_baud(serial_t *obj, int baudrate) {
    
    // save C2 state
    uint8_t c2_state = (obj->uart->C2 & (UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK));
    
    // Disable UART before changing registers
    obj->uart->C2 &= ~(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);
    
    uint32_t PCLK;
    if (obj->uart == UART0) {
        if (mcgpllfll_frequency() != 0)
            PCLK = mcgpllfll_frequency();
        else
            PCLK = extosc_frequency();
    } else
        PCLK = bus_frequency();

    // First we check to see if the basic divide with no DivAddVal/MulVal
    // ratio gives us an integer result. If it does, we set DivAddVal = 0,
    // MulVal = 1. Otherwise, we search the valid ratio value range to find
    // the closest match. This could be more elegant, using search methods
    // and/or lookup tables, but the brute force method is not that much
    // slower, and is more maintainable.
    uint16_t DL = PCLK / (16 * baudrate);

    // set BDH and BDL
    obj->uart->BDH = (obj->uart->BDH & ~(0x1f)) | ((DL >> 8) & 0x1f);
    obj->uart->BDL = (obj->uart->BDL & ~(0xff)) | ((DL >> 0) & 0xff);
    
    // restore C2 state
    obj->uart->C2 |= c2_state;
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2));
    MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) || (parity == ParityEven));
    MBED_ASSERT(data_bits == 8); // TODO: Support other number of data bits (also in the write method!)

    // save C2 state
    uint8_t c2_state = (obj->uart->C2 & (UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK));
    
    // Disable UART before changing registers
    obj->uart->C2 &= ~(UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK);
    

    uint8_t parity_enable, parity_select;
    switch (parity) {
        case ParityNone: parity_enable = 0; parity_select = 0; break;
        case ParityOdd : parity_enable = 1; parity_select = 1; data_bits++; break;
        case ParityEven: parity_enable = 1; parity_select = 0; data_bits++; break;
        default:
            break;
    }

    stop_bits -= 1;

    // data bits, parity and parity mode
    obj->uart->C1 = ((parity_enable << 1)
                  |  (parity_select << 0));
    
    // stop bits
    obj->uart->BDH &= ~UARTLP_BDH_SBNS_MASK;
    obj->uart->BDH |= (stop_bits << UARTLP_BDH_SBNS_SHIFT);
    
    // restore C2 state
    obj->uart->C2 |= c2_state;
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint8_t status, uint32_t index) {
    if (serial_irq_ids[index] != 0) {
        if (status & UARTLP_S1_TDRE_MASK)
            irq_handler(serial_irq_ids[index], TxIrq);

        if (status & UARTLP_S1_RDRF_MASK)
            irq_handler(serial_irq_ids[index], RxIrq);
    }
}

void uart0_irq() {
    uart_irq(UART0->S1, 0);
    if (UART0->S1 & UARTLP_S1_OR_MASK)
        UART0->S1 |= UARTLP_S1_OR_MASK;
}
#if UART_NUM > 1
void uart1_irq() {uart_irq(UART1->S1, 1);}
void uart2_irq() {uart_irq(UART2->S1, 2);}
#endif

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    switch ((int)obj->uart) {
        case UART_0: irq_n=UART0_IRQn; vector = (uint32_t)&uart0_irq; break;
        #if UART_NUM > 1
        case UART_1: irq_n=UART1_IRQn; vector = (uint32_t)&uart1_irq; break;
        case UART_2: irq_n=UART2_IRQn; vector = (uint32_t)&uart2_irq; break;
        #endif
    }

    if (enable) {
        switch (irq) {
            case RxIrq: obj->uart->C2 |= (UARTLP_C2_RIE_MASK); break;
            case TxIrq: obj->uart->C2 |= (UARTLP_C2_TIE_MASK); break;
        }
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);

    } else { // disable
        int all_disabled = 0;
        SerialIrq other_irq = (irq == RxIrq) ? (TxIrq) : (RxIrq);
        switch (irq) {
            case RxIrq: obj->uart->C2 &= ~(UARTLP_C2_RIE_MASK); break;
            case TxIrq: obj->uart->C2 &= ~(UARTLP_C2_TIE_MASK); break;
        }
        switch (other_irq) {
            case RxIrq: all_disabled = (obj->uart->C2 & (UARTLP_C2_RIE_MASK)) == 0; break;
            case TxIrq: all_disabled = (obj->uart->C2 & (UARTLP_C2_TIE_MASK)) == 0; break;
        }
        if (all_disabled)
            NVIC_DisableIRQ(irq_n);
    }
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj) {
    while (!serial_readable(obj));
    return obj->uart->D;
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    obj->uart->D = c;
}

int serial_readable(serial_t *obj) {
    // check overrun
    if (obj->uart->S1 &  UARTLP_S1_OR_MASK) {
        obj->uart->S1 |= UARTLP_S1_OR_MASK;
    }
    return (obj->uart->S1 & UARTLP_S1_RDRF_MASK);
}

int serial_writable(serial_t *obj) {
    // check overrun
    if (obj->uart->S1 &  UARTLP_S1_OR_MASK) {
        obj->uart->S1 |= UARTLP_S1_OR_MASK;
    }
    return (obj->uart->S1 & UARTLP_S1_TDRE_MASK);
}

void serial_clear(serial_t *obj) {
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    obj->uart->C2 |= UARTLP_C2_SBK_MASK;
}

void serial_break_clear(serial_t *obj) {
    obj->uart->C2 &= ~UARTLP_C2_SBK_MASK;
}

