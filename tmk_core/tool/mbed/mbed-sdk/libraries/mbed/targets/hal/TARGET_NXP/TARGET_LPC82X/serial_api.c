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

#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

#if DEVICE_SERIAL

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/
#define UART_NUM    3

static const SWM_Map SWM_UART_TX[] = {
    {0, 0},
    {1, 8},
    {2, 16},
};

static const SWM_Map SWM_UART_RX[] = {
    {0, 8},
    {1, 16},
    {2, 24},
};

static const SWM_Map SWM_UART_RTS[] = {
    {0, 16},
    {1, 24},
    {3, 0},
};
 
static const SWM_Map SWM_UART_CTS[] = {
    {0, 24},
    {2, 0},
    {3, 8}
};

// bit flags for used UARTs
static unsigned char uart_used = 0;

static int get_available_uart(void)
{
    int i;
    for (i=0; i<UART_NUM; i++) {
        if ((uart_used & (1 << i)) == 0)
            return i;
    }
    return -1;
}

#define UART_EN       (0x01<<0)

#define CTS_DELTA     (0x01<<5)
#define RXBRK         (0x01<<10)
#define DELTA_RXBRK   (0x01<<11)

#define RXRDY         (0x01<<0)
#define TXRDY         (0x01<<2)

#define RXRDYEN       RXRDY
#define TXRDYEN       TXRDY

#define TXBRKEN       (0x01<<1)
#define CTSEN         (0x01<<9)

static uint32_t UARTSysClk;

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

static int check_duplication(serial_t *obj, PinName tx, PinName rx)
{
    if (uart_used == 0)
        return 0;

    const SWM_Map *swm;
    uint32_t assigned_tx, assigned_rx;
    int ch;
    for (ch=0; ch<UART_NUM; ch++)  {
        // read assigned TX in the UART channel of switch matrix
        swm = &SWM_UART_TX[ch];
        assigned_tx = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
        assigned_tx = assigned_tx >> swm->offset;
        // read assigned RX in the UART channel of switch matrix
        swm = &SWM_UART_RX[ch];
        assigned_rx = LPC_SWM->PINASSIGN[swm->n] & (0xFF << swm->offset);
        assigned_rx = assigned_rx >> swm->offset;
        if ((assigned_tx == (uint32_t)(tx >> PIN_SHIFT)) && (assigned_rx == (uint32_t)(rx >> PIN_SHIFT))) {
            obj->index = ch;
            obj->uart = (LPC_USART0_Type *)(LPC_USART0_BASE + (0x4000 * ch));
            return 1;
        }
    }
    return 0;
}

void serial_init(serial_t *obj, PinName tx, PinName rx)
{
    int is_stdio_uart = 0;

    if (check_duplication(obj, tx, rx) == 1)
        return;

    int uart_n = get_available_uart();
    if (uart_n == -1) {
        error("No available UART");
    }
    obj->index = uart_n;
    obj->uart = (LPC_USART0_Type *)(LPC_USART0_BASE + (0x4000 * uart_n));
    uart_used |= (1 << uart_n);

    const SWM_Map *swm;
    uint32_t regVal;

    swm = &SWM_UART_TX[uart_n];
    regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
    LPC_SWM->PINASSIGN[swm->n] = regVal |  ((tx >> PIN_SHIFT) << swm->offset);

    swm = &SWM_UART_RX[uart_n];
    regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
    LPC_SWM->PINASSIGN[swm->n] = regVal |  ((rx >> PIN_SHIFT) << swm->offset);

    /* uart clock divided by 1 */
    LPC_SYSCON->UARTCLKDIV = 1;

    /* disable uart interrupts */
    NVIC_DisableIRQ((IRQn_Type)(UART0_IRQn + uart_n));

    /* Enable UART clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << (14 + uart_n));

    /* Peripheral reset control to UART, a "1" bring it out of reset. */
    LPC_SYSCON->PRESETCTRL &= ~(0x1 << (3 + uart_n));
    LPC_SYSCON->PRESETCTRL |=  (0x1 << (3 + uart_n));

    UARTSysClk = MainClock / LPC_SYSCON->UARTCLKDIV;

    // set default baud rate and format
    serial_baud  (obj, 9600);
    serial_format(obj, 8, ParityNone, 1);

    /* Clear all status bits. */
    obj->uart->STAT = CTS_DELTA | DELTA_RXBRK;

    /* enable uart interrupts */
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQn + uart_n));

    /* Enable UART */
    obj->uart->CFG |= UART_EN;

    is_stdio_uart = ((tx == USBTX) && (rx == USBRX));

    if (is_stdio_uart) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj)
{
    uart_used &= ~(1 << obj->index);
    serial_irq_ids[obj->index] = 0;
}

void serial_baud(serial_t *obj, int baudrate)
{
    /* Integer divider:
         BRG = UARTSysClk/(Baudrate * 16) - 1
       
       Frational divider:
         FRG = ((UARTSysClk / (Baudrate * 16 * (BRG + 1))) - 1)
       
       where
         FRG = (LPC_SYSCON->UARTFRDADD + 1) / (LPC_SYSCON->UARTFRDSUB + 1)
       
       (1) The easiest way is set SUB value to 256, -1 encoded, thus SUB
           register is 0xFF.
       (2) In ADD register value, depending on the value of UartSysClk,
           baudrate, BRG register value, and SUB register value, be careful
           about the order of multiplier and divider and make sure any
           multiplier doesn't exceed 32-bit boundary and any divider doesn't get
           down below one(integer 0).
       (3) ADD should be always less than SUB.
    */
    obj->uart->BRG = UARTSysClk / 16 / baudrate - 1;

    LPC_SYSCON->UARTFRGDIV = 0xFF;
    LPC_SYSCON->UARTFRGMULT = ( ((UARTSysClk / 16) * (LPC_SYSCON->UARTFRGDIV + 1)) /
                                (baudrate * (obj->uart->BRG + 1))
                              ) - (LPC_SYSCON->UARTFRGDIV + 1);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{
    // 0: 1 stop bits, 1: 2 stop bits
    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2));
    MBED_ASSERT((data_bits > 6) && (data_bits < 10)); // 0: 7 data bits ... 2: 9 data bits
    MBED_ASSERT((parity == ParityNone) || (parity == ParityEven) || (parity == ParityOdd));
    stop_bits -= 1;
    data_bits -= 7;

    int paritysel = 0;
    switch (parity) {
        case ParityNone: paritysel = 0; break;
        case ParityEven: paritysel = 2; break;
        case ParityOdd : paritysel = 3; break;
        default:
            break;
    }

    obj->uart->CFG = (data_bits << 2)
                   | (paritysel << 4)
                   | (stop_bits << 6);
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(SerialIrq irq_type, uint32_t index)
{
    if (serial_irq_ids[index] != 0)
        irq_handler(serial_irq_ids[index], irq_type);
}

void uart0_irq() {uart_irq((LPC_USART0->INTSTAT & RXRDY) ? RxIrq : TxIrq, 0);}
void uart1_irq() {uart_irq((LPC_USART1->INTSTAT & RXRDY) ? RxIrq : TxIrq, 1);}
void uart2_irq() {uart_irq((LPC_USART2->INTSTAT & RXRDY) ? RxIrq : TxIrq, 2);}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    switch ((int)obj->uart) {
        case LPC_USART0_BASE: irq_n=UART0_IRQn; vector = (uint32_t)&uart0_irq; break;
        case LPC_USART1_BASE: irq_n=UART1_IRQn; vector = (uint32_t)&uart1_irq; break;
        case LPC_USART2_BASE: irq_n=UART2_IRQn; vector = (uint32_t)&uart2_irq; break;
    }

    if (enable) {
        NVIC_DisableIRQ(irq_n);
        obj->uart->INTENSET |= (1 << ((irq == RxIrq) ? 0 : 2));
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);
    } else { // disable
        obj->uart->INTENCLR |= (1 << ((irq == RxIrq) ? 0 : 2));
        if ( (obj->uart->INTENSET & (RXRDYEN | TXRDYEN)) == 0) {
            NVIC_DisableIRQ(irq_n);
        }
    }
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj)
{
    while (!serial_readable(obj));
    return obj->uart->RXDAT;
}

void serial_putc(serial_t *obj, int c)
{
    while (!serial_writable(obj));
    obj->uart->TXDAT = c;
}

int serial_readable(serial_t *obj)
{
    return obj->uart->STAT & RXRDY;
}

int serial_writable(serial_t *obj)
{
    return obj->uart->STAT & TXRDY;
}

void serial_clear(serial_t *obj)
{
    // [TODO]
}

void serial_pinout_tx(PinName tx)
{

}

void serial_break_set(serial_t *obj)
{
    obj->uart->CTL |= TXBRKEN;
}

void serial_break_clear(serial_t *obj)
{
    obj->uart->CTL &= ~TXBRKEN;
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow)
{
    const SWM_Map *swm_rts, *swm_cts;
    uint32_t regVal_rts, regVal_cts;

    swm_rts = &SWM_UART_RTS[obj->index];
    swm_cts = &SWM_UART_CTS[obj->index];
    regVal_rts = LPC_SWM->PINASSIGN[swm_rts->n] & ~(0xFF << swm_rts->offset);
    regVal_cts = LPC_SWM->PINASSIGN[swm_cts->n] & ~(0xFF << swm_cts->offset);

    if (FlowControlNone == type) {
        LPC_SWM->PINASSIGN[swm_rts->n] = regVal_rts | (0xFF << swm_rts->offset);
        LPC_SWM->PINASSIGN[swm_cts->n] = regVal_cts | (0xFF << swm_cts->offset);
        obj->uart->CFG &= ~CTSEN;
        return;
    }
    if ((FlowControlRTS == type || FlowControlRTSCTS == type) && (rxflow != NC)) {
        LPC_SWM->PINASSIGN[swm_rts->n] = regVal_rts | ((rxflow >> PIN_SHIFT) << swm_rts->offset);
        if (FlowControlRTS == type) {
            LPC_SWM->PINASSIGN[swm_cts->n] = regVal_cts | (0xFF << swm_cts->offset);
            obj->uart->CFG &= ~CTSEN;
        }
    }
    if ((FlowControlCTS == type || FlowControlRTSCTS == type) && (txflow != NC)) {
        LPC_SWM->PINASSIGN[swm_cts->n] = regVal_cts | ((txflow >> PIN_SHIFT) << swm_cts->offset);
        obj->uart->CFG |= CTSEN;
        if (FlowControlCTS == type) {
            LPC_SWM->PINASSIGN[swm_rts->n] = regVal_rts | (0xFF << swm_rts->offset);
        }
    }
}

#endif
