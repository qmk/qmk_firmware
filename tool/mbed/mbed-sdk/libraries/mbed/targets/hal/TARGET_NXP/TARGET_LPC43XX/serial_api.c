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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
// math.h required for floating point operations for baud rate calculation
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "gpio_api.h"

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/
#define UART_NUM    4

// SCU mode for UART pins
#define SCU_PINIO_UART_TX   SCU_MODE_PULLDOWN
#define SCU_PINIO_UART_RX   SCU_PINIO_PULLNONE

static const PinMap PinMap_UART_TX[] = {
    {P1_13, UART_1, (SCU_PINIO_UART_TX | 1)},
    {P1_15, UART_2, (SCU_PINIO_UART_TX | 1)},
    {P2_0,  UART_0, (SCU_PINIO_UART_TX | 1)},
    {P2_3,  UART_3, (SCU_PINIO_UART_TX | 2)},
    {P2_10, UART_2, (SCU_PINIO_UART_TX | 2)},
    {P3_4,  UART_1, (SCU_PINIO_UART_TX | 4)},
    {P4_1,  UART_3, (SCU_PINIO_UART_TX | 6)},
    {P5_6,  UART_1, (SCU_PINIO_UART_TX | 4)},
    {P6_4,  UART_0, (SCU_PINIO_UART_TX | 2)},
    {P7_1,  UART_2, (SCU_PINIO_UART_TX | 6)},
    {P9_3,  UART_3, (SCU_PINIO_UART_TX | 7)},
    {P9_5,  UART_0, (SCU_PINIO_UART_TX | 7)},
    {PA_1,  UART_2, (SCU_PINIO_UART_TX | 3)},
    {PC_13, UART_1, (SCU_PINIO_UART_TX | 2)},
    {PE_11, UART_1, (SCU_PINIO_UART_TX | 2)},
    {PF_2,  UART_3, (SCU_PINIO_UART_TX | 1)},
    {PF_10, UART_0, (SCU_PINIO_UART_TX | 1)},
    {NC,    NC,     0}
};

static const PinMap PinMap_UART_RX[] = {
    {P1_14, UART_1, (SCU_PINIO_UART_RX | 1)},
    {P1_16, UART_2, (SCU_PINIO_UART_RX | 1)},
    {P2_1,  UART_0, (SCU_PINIO_UART_RX | 1)},
    {P2_4,  UART_3, (SCU_PINIO_UART_RX | 2)},
    {P2_11, UART_2, (SCU_PINIO_UART_RX | 2)},
    {P3_5,  UART_1, (SCU_PINIO_UART_RX | 4)},
    {P4_2,  UART_3, (SCU_PINIO_UART_RX | 6)},
    {P5_7,  UART_1, (SCU_PINIO_UART_RX | 4)},
    {P6_5,  UART_0, (SCU_PINIO_UART_RX | 2)},
    {P7_2,  UART_2, (SCU_PINIO_UART_RX | 6)},
    {P9_4,  UART_3, (SCU_PINIO_UART_RX | 7)},
    {P9_6,  UART_0, (SCU_PINIO_UART_RX | 7)},
    {PA_2,  UART_2, (SCU_PINIO_UART_RX | 3)},
    {PC_14, UART_1, (SCU_PINIO_UART_RX | 2)},
    {PE_12, UART_1, (SCU_PINIO_UART_RX | 2)},
    {PF_3,  UART_3, (SCU_PINIO_UART_RX | 1)},
    {PF_11, UART_0, (SCU_PINIO_UART_RX | 1)},
    {NC,    NC,     0}
};

#if (DEVICE_SERIAL_FC)
// RTS/CTS PinMap for flow control
static const PinMap PinMap_UART_RTS[] = {
    {P1_9,  UART_1, (SCU_PINIO_FAST | 1)},
    {P5_2,  UART_1, (SCU_PINIO_FAST | 4)},
    {PC_3,  UART_1, (SCU_PINIO_FAST | 2)},
    {PE_5,  UART_1, (SCU_PINIO_FAST | 2)},
    {NC,    NC,     0}
};

static const PinMap PinMap_UART_CTS[] = {
    {P1_11, UART_1, (SCU_PINIO_FAST | 1)},
    {P5_4,  UART_1, (SCU_PINIO_FAST | 4),
    {PC_2,  UART_1, (SCU_PINIO_FAST | 2)},
    {PE_7,  UART_1, (SCU_PINIO_FAST | 2)},
    {NC,    NC,     0}
};
#endif

static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

struct serial_global_data_s {
    uint32_t serial_irq_id;
    gpio_t sw_rts, sw_cts;
    uint8_t count, rx_irq_set_flow, rx_irq_set_api;
};

static struct serial_global_data_s uart_data[UART_NUM];

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    int is_stdio_uart = 0;
    
    // determine the UART to use
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);
    UARTName uart = (UARTName)pinmap_merge(uart_tx, uart_rx);
    if ((int)uart == NC) {
        error("Serial pinout mapping failed");
    }

    obj->uart = (LPC_USART_T *)uart;

    // enable fifos and default rx trigger level
    obj->uart->FCR = 1 << 0  // FIFO Enable - 0 = Disables, 1 = Enabled
                   | 0 << 1  // Rx Fifo Reset
                   | 0 << 2  // Tx Fifo Reset
                   | 0 << 6; // Rx irq trigger level - 0 = 1 char, 1 = 4 chars, 2 = 8 chars, 3 = 14 chars

    // disable irqs
    obj->uart->IER = 0 << 0  // Rx Data available irq enable
                   | 0 << 1  // Tx Fifo empty irq enable
                   | 0 << 2; // Rx Line Status irq enable
    
    // set default baud rate and format
    is_stdio_uart = (uart == STDIO_UART) ? (1) : (0);   
    serial_baud  (obj, is_stdio_uart ? 115200 : 9600);
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
    
    switch (uart) {
        case UART_0: obj->index = 0; break;
        case UART_1: obj->index = 1; break;
        case UART_2: obj->index = 2; break;
        case UART_3: obj->index = 3; break;
    }
    uart_data[obj->index].sw_rts.pin = NC;
    uart_data[obj->index].sw_cts.pin = NC;
    serial_set_flow_control(obj, FlowControlNone, NC, NC);
    
    if (is_stdio_uart) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj) {
    uart_data[obj->index].serial_irq_id = 0;
}

// serial_baud
// set the baud rate, taking in to account the current SystemFrequency
void serial_baud(serial_t *obj, int baudrate) {
    uint32_t PCLK = SystemCoreClock;
    
    // First we check to see if the basic divide with no DivAddVal/MulVal
    // ratio gives us an integer result. If it does, we set DivAddVal = 0,
    // MulVal = 1. Otherwise, we search the valid ratio value range to find
    // the closest match. This could be more elegant, using search methods
    // and/or lookup tables, but the brute force method is not that much
    // slower, and is more maintainable.
    uint16_t DL = PCLK / (16 * baudrate);

    uint8_t DivAddVal = 0;
    uint8_t MulVal = 1;
    int hit = 0;
    uint16_t dlv;
    uint8_t mv, dav;
    if ((PCLK % (16 * baudrate)) != 0) {     // Checking for zero remainder
        int err_best = baudrate, b;
        for (mv = 1; mv < 16 && !hit; mv++)
        {
            for (dav = 0; dav < mv; dav++)
            {
                // baudrate = PCLK / (16 * dlv * (1 + (DivAdd / Mul))
                // solving for dlv, we get dlv = mul * PCLK / (16 * baudrate * (divadd + mul))
                // mul has 4 bits, PCLK has 27 so we have 1 bit headroom which can be used for rounding
                // for many values of mul and PCLK we have 2 or more bits of headroom which can be used to improve precision
                // note: X / 32 doesn't round correctly. Instead, we use ((X / 16) + 1) / 2 for correct rounding

                if ((mv * PCLK * 2) & 0x80000000) // 1 bit headroom
                    dlv = ((((2 * mv * PCLK) / (baudrate * (dav + mv))) / 16) + 1) / 2;
                else // 2 bits headroom, use more precision
                    dlv = ((((4 * mv * PCLK) / (baudrate * (dav + mv))) / 32) + 1) / 2;

                // datasheet says if DLL==DLM==0, then 1 is used instead since divide by zero is ungood
                if (dlv == 0)
                    dlv = 1;

                // datasheet says if dav > 0 then DL must be >= 2
                if ((dav > 0) && (dlv < 2))
                    dlv = 2;

                // integer rearrangement of the baudrate equation (with rounding)
                b = ((PCLK * mv / (dlv * (dav + mv) * 8)) + 1) / 2;

                // check to see how we went
                b = abs(b - baudrate);
                if (b < err_best)
                {
                    err_best  = b;

                    DL        = dlv;
                    MulVal    = mv;
                    DivAddVal = dav;

                    if (b == baudrate)
                    {
                        hit = 1;
                        break;
                    }
                }
            }
        }
    }
    
    // set LCR[DLAB] to enable writing to divider registers
    obj->uart->LCR |= (1 << 7);
    
    // set divider values
    obj->uart->DLM = (DL >> 8) & 0xFF;
    obj->uart->DLL = (DL >> 0) & 0xFF;
    obj->uart->FDR = (uint32_t) DivAddVal << 0
                   | (uint32_t) MulVal    << 4;
    
    // clear LCR[DLAB]
    obj->uart->LCR &= ~(1 << 7);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    // 0: 1 stop bits, 1: 2 stop bits
    if (stop_bits != 1 && stop_bits != 2) {
        error("Invalid stop bits specified");
    }
    stop_bits -= 1;
    
    // 0: 5 data bits ... 3: 8 data bits
    if (data_bits < 5 || data_bits > 8) {
        error("Invalid number of bits (%d) in serial format, should be 5..8", data_bits);
    }
    data_bits -= 5;

    int parity_enable, parity_select;
    switch (parity) {
        case ParityNone: parity_enable = 0; parity_select = 0; break;
        case ParityOdd : parity_enable = 1; parity_select = 0; break;
        case ParityEven: parity_enable = 1; parity_select = 1; break;
        case ParityForced1: parity_enable = 1; parity_select = 2; break;
        case ParityForced0: parity_enable = 1; parity_select = 3; break;
        default:
            error("Invalid serial parity setting");
            return;
    }
    
    obj->uart->LCR = data_bits            << 0
                   | stop_bits            << 2
                   | parity_enable        << 3
                   | parity_select        << 4;
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint32_t iir, uint32_t index, LPC_USART_T *puart) {
    // [Chapter 14] LPC17xx UART0/2/3: UARTn Interrupt Handling
    SerialIrq irq_type;
    switch (iir) {
        case 1: irq_type = TxIrq; break;
        case 2: irq_type = RxIrq; break;
        default: return;
    }
    if ((RxIrq == irq_type) && (NC != uart_data[index].sw_rts.pin)) {
        gpio_write(&uart_data[index].sw_rts, 1);
        // Disable interrupt if it wasn't enabled by other part of the application
        if (!uart_data[index].rx_irq_set_api)
            puart->IER &= ~(1 << RxIrq);
    }
    if (uart_data[index].serial_irq_id != 0)
        if ((irq_type != RxIrq) || (uart_data[index].rx_irq_set_api))
            irq_handler(uart_data[index].serial_irq_id, irq_type);
}

void uart0_irq() {uart_irq((LPC_USART0->IIR >> 1) & 0x7, 0, (LPC_USART_T*)LPC_USART0);}
void uart1_irq() {uart_irq((LPC_UART1->IIR  >> 1) & 0x7, 1, (LPC_USART_T*)LPC_UART1);}
void uart2_irq() {uart_irq((LPC_USART2->IIR >> 1) & 0x7, 2, (LPC_USART_T*)LPC_USART2);}
void uart3_irq() {uart_irq((LPC_USART3->IIR >> 1) & 0x7, 3, (LPC_USART_T*)LPC_USART3);}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    uart_data[obj->index].serial_irq_id = id;
}

static void serial_irq_set_internal(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    switch ((int)obj->uart) {
        case UART_0: irq_n=USART0_IRQn; vector = (uint32_t)&uart0_irq; break;
        case UART_1: irq_n=UART1_IRQn;  vector = (uint32_t)&uart1_irq; break;
        case UART_2: irq_n=USART2_IRQn; vector = (uint32_t)&uart2_irq; break;
        case UART_3: irq_n=USART3_IRQn; vector = (uint32_t)&uart3_irq; break;
    }
    
    if (enable) {
        obj->uart->IER |= 1 << irq;
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);
    } else if ((TxIrq == irq) || (uart_data[obj->index].rx_irq_set_api + uart_data[obj->index].rx_irq_set_flow == 0)) { // disable
        int all_disabled = 0;
        SerialIrq other_irq = (irq == RxIrq) ? (TxIrq) : (RxIrq);
        obj->uart->IER &= ~(1 << irq);
        all_disabled = (obj->uart->IER & (1 << other_irq)) == 0;
        if (all_disabled)
            NVIC_DisableIRQ(irq_n);
    }
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    if (RxIrq == irq)
        uart_data[obj->index].rx_irq_set_api = enable;
    serial_irq_set_internal(obj, irq, enable);
}

#if (DEVICE_SERIAL_FC)
static void serial_flow_irq_set(serial_t *obj, uint32_t enable) {
    uart_data[obj->index].rx_irq_set_flow = enable;
    serial_irq_set_internal(obj, RxIrq, enable);
}
#endif

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj) {
    while (!serial_readable(obj));
    int data = obj->uart->RBR;
    if (NC != uart_data[obj->index].sw_rts.pin) {
        gpio_write(&uart_data[obj->index].sw_rts, 0);
        obj->uart->IER |= 1 << RxIrq;
    }
    return data;
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    obj->uart->THR = c;
    uart_data[obj->index].count++;
}

int serial_readable(serial_t *obj) {
    return obj->uart->LSR & 0x01;
}

int serial_writable(serial_t *obj) {
    int isWritable = 1;
    if (NC != uart_data[obj->index].sw_cts.pin)
        isWritable = (gpio_read(&uart_data[obj->index].sw_cts) == 0) && (obj->uart->LSR & 0x40);  //If flow control: writable if CTS low + UART done
    else {
        if (obj->uart->LSR & 0x20)
            uart_data[obj->index].count = 0;
        else if (uart_data[obj->index].count >= 16)
            isWritable = 0;
    }
    return isWritable;
}

void serial_clear(serial_t *obj) {
    obj->uart->FCR = 1 << 0  // FIFO Enable - 0 = Disables, 1 = Enabled
                   | 1 << 1  // rx FIFO reset
                   | 1 << 2  // tx FIFO reset
                   | 0 << 6; // interrupt depth
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    obj->uart->LCR |= (1 << 6);
}

void serial_break_clear(serial_t *obj) {
    obj->uart->LCR &= ~(1 << 6);
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow) {
#if (DEVICE_SERIAL_FC)
#endif
}
