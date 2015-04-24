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

// math.h required for floating point operations for baud rate calculation
#include "mbed_assert.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"

#if DEVICE_SERIAL

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/

#define UART_NUM      5

// CFG
#define UART_EN       (0x01<<0)

// CTL
#define TXBRKEN       (0x01<<1)

// STAT
#define RXRDY         (0x01<<0)
#define TXRDY         (0x01<<2)
#define DELTACTS      (0x01<<5)
#define RXBRK         (0x01<<10)
#define DELTARXBRK    (0x01<<11)

static const PinMap PinMap_UART_TX[] = {
    {P0_19, UART_0, 1},
    {P1_18, UART_0, 2},
    {P1_27, UART_0, 2},
    {P1_8 , UART_1, 2},
    {P1_0 , UART_2, 3},
    {P1_23, UART_2, 3},
    {P2_4 , UART_3, 1},
    {P2_12, UART_4, 1},
    { NC  , NC    , 0}
};

static const PinMap PinMap_UART_RX[] = {
    {P0_18, UART_0, 1},
    {P1_17, UART_0, 2},
    {P1_26, UART_0, 2},
    {P1_2 , UART_1, 3},
    {P0_20, UART_2, 2},
    {P1_6 , UART_2, 2},
    {P2_3 , UART_3, 1},
    {P2_11, UART_4, 1},
    {NC   , NC    , 0}
};

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    int is_stdio_uart = 0;
    
    // determine the UART to use
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);
    UARTName uart = (UARTName)pinmap_merge(uart_tx, uart_rx);
    MBED_ASSERT((int)uart != NC);
    
    switch (uart) {
        case UART_0:
            obj->index = 0;
            LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
            break;
        case UART_1:
            obj->index = 1;
            LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 20);
            LPC_SYSCON->PRESETCTRL |= (1 << 5);
            break;
        case UART_2:
            obj->index = 2;
            LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 21);
            LPC_SYSCON->PRESETCTRL |= (1 << 6);
            break;
        case UART_3:
            obj->index = 3;
            LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 22);
            LPC_SYSCON->PRESETCTRL |= (1 << 7);
            break;
        case UART_4:
            obj->index = 4;
            LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 22);
            LPC_SYSCON->PRESETCTRL |= (1 << 8);
            break;
    }

    if (obj->index == 0)
        obj->uart = (LPC_USART0_Type *)uart;
    else
        obj->mini_uart = (LPC_USART4_Type *)uart;
    
    if (obj->index == 0) {
        // enable fifos and default rx trigger level
        obj->uart->FCR = 1 << 0  // FIFO Enable - 0 = Disables, 1 = Enabled
                       | 0 << 1  // Rx Fifo Clear
                       | 0 << 2  // Tx Fifo Clear
                       | 0 << 6; // Rx irq trigger level - 0 = 1 char, 1 = 4 chars, 2 = 8 chars, 3 = 14 chars
        // disable irqs
        obj->uart->IER = 0 << 0  // Rx Data available irq enable
                       | 0 << 1  // Tx Fifo empty irq enable
                       | 0 << 2; // Rx Line Status irq enable
    }
    else {
        // Clear all status bits
        obj->mini_uart->STAT = (DELTACTS | DELTARXBRK);
        // Enable UART
        obj->mini_uart->CFG |= UART_EN;
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
    
    is_stdio_uart = (uart == STDIO_UART) ? (1) : (0);
    
    if (is_stdio_uart && (obj->index == 0)) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj) {
    serial_irq_ids[obj->index] = 0;
}

// serial_baud
// set the baud rate, taking in to account the current SystemFrequency
void serial_baud(serial_t *obj, int baudrate) {
    LPC_SYSCON->USART0CLKDIV = 1;
    LPC_SYSCON->FRGCLKDIV = 1;

    if (obj->index == 0) {
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
    else {
        uint32_t UARTSysClk = SystemCoreClock / LPC_SYSCON->FRGCLKDIV;
        obj->mini_uart->BRG = UARTSysClk / 16 / baudrate - 1;
        
        LPC_SYSCON->UARTFRGDIV = 0xFF;
        LPC_SYSCON->UARTFRGMULT = ( ((UARTSysClk / 16) * (LPC_SYSCON->UARTFRGDIV + 1)) /
                                    (baudrate * (obj->mini_uart->BRG + 1))
                                  ) - (LPC_SYSCON->UARTFRGDIV + 1);
    }
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2)); // 0: 1 stop bits, 1: 2 stop bits

    stop_bits -= 1;

    if (obj->index == 0) {
        MBED_ASSERT((data_bits > 4) && (data_bits < 9)); // 0: 5 data bits ... 3: 8 data bits
        MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) || (parity == ParityEven) ||
                    (parity == ParityForced1) || (parity == ParityForced0));
        data_bits -= 5;
    
        int parity_enable, parity_select;
        switch (parity) {
            case ParityNone: parity_enable = 0; parity_select = 0; break;
            case ParityOdd : parity_enable = 1; parity_select = 0; break;
            case ParityEven: parity_enable = 1; parity_select = 1; break;
            case ParityForced1: parity_enable = 1; parity_select = 2; break;
            case ParityForced0: parity_enable = 1; parity_select = 3; break;
            default:
                return;
        }
        
        obj->uart->LCR = data_bits       << 0
                       | stop_bits       << 2
                       | parity_enable   << 3
                       | parity_select   << 4;
    }
    else {
        // 0: 7 data bits ... 2: 9 data bits
        MBED_ASSERT((data_bits > 6) && (data_bits < 10));
        MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) || (parity == ParityEven));
        data_bits -= 7;

        int paritysel;
        switch (parity) {
            case ParityNone: paritysel = 0; break;
            case ParityEven: paritysel = 2; break;
            case ParityOdd : paritysel = 3; break;
            default:
                return;
        }
        obj->mini_uart->CFG = (data_bits << 2)
                            | (paritysel << 4)
                            | (stop_bits << 6)
                            | UART_EN;
    }
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint32_t iir, uint32_t index) {
    SerialIrq irq_type;
    switch (iir) {
        case 1: irq_type = TxIrq; break;
        case 2: irq_type = RxIrq; break;
        default: return;
    }
    
    if (serial_irq_ids[index] != 0)
        irq_handler(serial_irq_ids[index], irq_type);
}

void uart0_irq()
{
    uart_irq((LPC_USART0->IIR >> 1) & 0x7, 0);
}

void uart1_irq()
{
    uart_irq((LPC_USART1->STAT & (1 << 2)) ? 2 : 1, 1);
}

void uart2_irq()
{
    uart_irq((LPC_USART1->STAT & (1 << 2)) ? 2 : 1, 2);
}

void uart3_irq()
{
    uart_irq((LPC_USART1->STAT & (1 << 2)) ? 2 : 1, 3);
}

void uart4_irq()
{
    uart_irq((LPC_USART1->STAT & (1 << 2)) ? 2 : 1, 4);
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    switch ((int)obj->uart) {
        case UART_0: irq_n = USART0_IRQn;   vector = (uint32_t)&uart0_irq; break;
        case UART_1: irq_n = USART1_4_IRQn; vector = (uint32_t)&uart1_irq; break;
        case UART_2: irq_n = USART2_3_IRQn; vector = (uint32_t)&uart2_irq; break;
        case UART_3: irq_n = USART2_3_IRQn; vector = (uint32_t)&uart3_irq; break;
        case UART_4: irq_n = USART1_4_IRQn; vector = (uint32_t)&uart4_irq; break;
    }
    
    if (enable) {
        if (obj->index == 0) {
            obj->uart->IER |= (1 << irq);
        }
        else {
            obj->mini_uart->INTENSET = (1 << ((irq == RxIrq) ? 0 : 2));
        }
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);
    } else { // disable
        int all_disabled = 0;
        SerialIrq other_irq = (irq == RxIrq) ? (TxIrq) : (RxIrq);

        if (obj->index == 0) {
            obj->uart->IER &= ~(1 << irq);
            all_disabled = (obj->uart->IER & (1 << other_irq)) == 0;
        }
        else {
            obj->mini_uart->INTENSET &= ~(1 << ((irq == RxIrq) ? 0 : 2));
            all_disabled = (obj->mini_uart->INTENSET & (1 << ((other_irq == RxIrq) ? 0 : 2))) == 0;
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
    if (obj->index == 0) {
        return obj->uart->RBR;
    }
    else {
        return obj->mini_uart->RXDAT;
    }
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    if (obj->index == 0) {
        obj->uart->THR = c;
    }
    else {
        obj->mini_uart->TXDAT = c;
    }
}

int serial_readable(serial_t *obj) {
    if (obj->index == 0) {
        return obj->uart->LSR & 0x01;
    }
    else {
        return obj->mini_uart->STAT & RXRDY;
    }
}

int serial_writable(serial_t *obj) {
    if (obj->index == 0) {
        return obj->uart->LSR & 0x20;
    }
    else {
        return obj->mini_uart->STAT & TXRDY;
    }
}

void serial_clear(serial_t *obj) {
    if (obj->index == 0) {
        obj->uart->FCR = 1 << 1  // rx FIFO reset
                       | 1 << 2  // tx FIFO reset
                       | 0 << 6; // interrupt depth
    }
    else {
        obj->mini_uart->STAT = 0;
    }
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    if (obj->index == 0) {
        obj->uart->LCR |= (1 << 6);
    }
    else {
        obj->mini_uart->CTL |= TXBRKEN;
    }
}

void serial_break_clear(serial_t *obj) {
    if (obj->index == 0) {
        obj->uart->LCR &= ~(1 << 6);
    }
    else {
        obj->mini_uart->CTL &= ~TXBRKEN;
    }
}


#endif
