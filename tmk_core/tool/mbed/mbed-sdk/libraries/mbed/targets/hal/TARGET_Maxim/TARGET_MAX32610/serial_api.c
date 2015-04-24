/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#include <string.h>
#include "mbed_assert.h"
#include "cmsis.h"
#include "serial_api.h"
#include "uart_regs.h"
#include "PeripheralPins.h"

#define UART_NUM 2
#define DEFAULT_BAUD 9600
#define DEFAULT_STOP 1
#define DEFAULT_PARITY ParityNone

#define UART_ERRORS (MXC_F_UART_INTFL_RX_FRAME_ERROR | \
                     MXC_F_UART_INTFL_RX_PARITY_ERROR | \
                     MXC_F_UART_INTFL_RX_OVERRUN)

// Variables for managing the stdio UART
int stdio_uart_inited;
serial_t stdio_uart;

// Variables for interrupt driven
static uart_irq_handler irq_handler;
static uint32_t serial_irq_ids[UART_NUM];

//******************************************************************************
void serial_init(serial_t *obj, PinName tx, PinName rx)
{
    // Determine which uart is associated with each pin
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);
    UARTName uart = (UARTName)pinmap_merge(uart_tx, uart_rx);

    // Make sure that both pins are pointing to the same uart
    MBED_ASSERT(uart != (UARTName)NC);

    // Set the obj pointer to the proper uart
    obj->uart = (mxc_uart_regs_t*)uart;

    // Set the uart index
    obj->index = MXC_UART_BASE_TO_INSTANCE(obj->uart);

    // Configure the pins
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);

    // Flush the RX and TX FIFOs, clear the settings
    obj->uart->ctrl = ( MXC_F_UART_CTRL_TX_FIFO_FLUSH |  MXC_F_UART_CTRL_RX_FIFO_FLUSH);

    // Disable interrupts
    obj->uart->inten = 0;
    obj->uart->intfl = 0;

    // Configure to default settings
    serial_baud(obj, DEFAULT_BAUD);
    serial_format(obj, 8, ParityNone, 1);

    // Manage stdio UART
    if(uart == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

//******************************************************************************
void serial_baud(serial_t *obj, int baudrate)
{
    uint32_t idiv = 0, ddiv = 0, div = 0;

    // Calculate the integer and decimal portions
    div = SystemCoreClock / ((baudrate / 100) * 128);
    idiv = (div / 100);
    ddiv = (div - idiv * 100) * 128 / 100;

    obj->uart->baud_int = idiv;
    obj->uart->baud_div_128 = ddiv;

    // Enable the baud clock
    obj->uart->ctrl |= MXC_F_UART_CTRL_BAUD_CLK_EN;
}

//******************************************************************************
void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{

    // Check the validity of the inputs
    MBED_ASSERT((data_bits > 4) && (data_bits < 9));
    MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) ||
                (parity == ParityEven) || (parity == ParityForced1) ||
                (parity == ParityForced0));
    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2));

    // Adjust the stop and data bits
    stop_bits -= 1;
    data_bits -= 5;

    // Adjust the parity setting
    int paren = 0, mode = 0;
    switch (parity) {
        case ParityNone:
            paren = 0;
            mode = 0;
            break;
        case ParityOdd :
            paren = 1;
            mode = 0;
            break;
        case ParityEven:
            paren = 1;
            mode = 1;
            break;
        case ParityForced1:
            // Hardware does not support forced parity
            MBED_ASSERT(0);
            break;
        case ParityForced0:
            // Hardware does not support forced parity
            MBED_ASSERT(0);
            break;
        default:
            paren = 1;
            mode = 0;
            break;
    }

    obj->uart->ctrl |= ((data_bits << MXC_F_UART_CTRL_CHAR_LENGTH_POS) |
                        (stop_bits << MXC_F_UART_CTRL_STOP_BIT_MODE_POS) |
                        (paren << MXC_F_UART_CTRL_PARITY_ENABLE_POS) |
                        (mode << MXC_F_UART_CTRL_PARITY_MODE_POS));
}

//******************************************************************************
void uart_handler(mxc_uart_regs_t* uart, int id)
{
    // Check for errors or RX Threshold
    if(uart->intfl & (MXC_F_UART_INTFL_RX_OVER_THRESHOLD | UART_ERRORS)) {
        irq_handler(serial_irq_ids[id], RxIrq);
        uart->intfl &= ~(MXC_F_UART_INTFL_RX_OVER_THRESHOLD | UART_ERRORS);
    }

    // Check for TX Threshold
    if(uart->intfl & MXC_F_UART_INTFL_TX_ALMOST_EMPTY) {
        irq_handler(serial_irq_ids[id], TxIrq);
        uart->intfl &= ~(MXC_F_UART_INTFL_TX_ALMOST_EMPTY);
    }
}

void uart0_handler(void)
{
    uart_handler(MXC_UART0, 0);
}
void uart1_handler(void)
{
    uart_handler(MXC_UART1, 1);
}

//******************************************************************************
void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

//******************************************************************************
void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    if(obj->index == 0) {
        NVIC_SetVector(UART0_IRQn, (uint32_t)uart0_handler);
        NVIC_EnableIRQ(UART0_IRQn);
    } else {
        NVIC_SetVector(UART1_IRQn, (uint32_t)uart1_handler);
        NVIC_EnableIRQ(UART1_IRQn);
    }

    if(irq == RxIrq) {
        // Set the RX FIFO Threshold to 1
        obj->uart->ctrl &= ~MXC_F_UART_CTRL_RX_THRESHOLD;
        obj->uart->ctrl |= 0x1;
        // Enable RX FIFO Threshold Interrupt
        if(enable) {
            // Clear pending interrupts
            obj->uart->intfl = 0;
            obj->uart->inten |= (MXC_F_UART_INTFL_RX_OVER_THRESHOLD |
                                 UART_ERRORS);
        } else {
            // Clear pending interrupts
            obj->uart->intfl = 0;
            obj->uart->inten &= ~(MXC_F_UART_INTFL_RX_OVER_THRESHOLD |
                                  UART_ERRORS);
        }

    } else if (irq == TxIrq) {
        // Enable TX Almost empty Interrupt
        if(enable) {
            // Clear pending interrupts
            obj->uart->intfl = 0;
            obj->uart->inten |= MXC_F_UART_INTFL_TX_ALMOST_EMPTY;
        } else {
            // Clear pending interrupts
            obj->uart->intfl = 0;
            obj->uart->inten &= ~MXC_F_UART_INTFL_TX_ALMOST_EMPTY;
        }

    } else {
        MBED_ASSERT(0);
    }
}


//******************************************************************************
int serial_getc(serial_t *obj)
{
    int c;

    // Wait for data to be available
    while(obj->uart->status & MXC_F_UART_STATUS_RX_FIFO_EMPTY) {}
    c = obj->uart->tx_rx_fifo & 0xFF;

    // Echo characters for stdio
    if (obj->uart == (mxc_uart_regs_t*)STDIO_UART) {
        obj->uart->tx_rx_fifo = c;
    }
    
    return c;
}

//******************************************************************************
void serial_putc(serial_t *obj, int c)
{
    // Append a carriage return for stdio
    if ((c == (int)'\n') && (obj->uart == (mxc_uart_regs_t*)STDIO_UART)) {
        while(obj->uart->status & MXC_F_UART_STATUS_TX_FIFO_FULL) {}
        obj->uart->tx_rx_fifo = '\r';
    }

    // Wait for TXFIFO to not be full
    while(obj->uart->status & MXC_F_UART_STATUS_TX_FIFO_FULL) {}
    obj->uart->tx_rx_fifo = c;

}

//******************************************************************************
int serial_readable(serial_t *obj)
{
    return (!(obj->uart->status & MXC_F_UART_STATUS_RX_FIFO_EMPTY));
}

//******************************************************************************
int serial_writable(serial_t *obj)
{
    return (!(obj->uart->status & MXC_F_UART_STATUS_TX_FIFO_FULL));
}

//******************************************************************************
void serial_clear(serial_t *obj)
{
    // Clear the rx and tx fifos
    obj->uart->ctrl |= (MXC_F_UART_CTRL_TX_FIFO_FLUSH  | MXC_F_UART_CTRL_RX_FIFO_FLUSH );
}


//******************************************************************************
void serial_break_set(serial_t *obj)
{
    // Make sure that nothing is being sent
    while(obj->uart->status & MXC_F_UART_STATUS_RX_BUSY) {}

    // Disable the clock to pause any transmission
    obj->uart->ctrl &= ~MXC_F_UART_CTRL_BAUD_CLK_EN ;
}

//******************************************************************************
void serial_break_clear(serial_t *obj)
{
    obj->uart->ctrl |= MXC_F_UART_CTRL_BAUD_CLK_EN;
}


//******************************************************************************
void serial_pinout_tx(PinName tx)
{
    pinmap_pinout(tx, PinMap_UART_TX);
}


//******************************************************************************
void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow)
{
    if(FlowControlNone == type) {
        // Disable hardware flow control
        obj->uart->ctrl &= ~(MXC_F_UART_CTRL_HW_FLOW_CTRL_EN);
        return;
    }

    // Check to see if we can use HW flow control
    UARTName uart_cts = (UARTName)pinmap_peripheral(txflow, PinMap_UART_CTS);
    UARTName uart_rts = (UARTName)pinmap_peripheral(rxflow, PinMap_UART_RTS);
    UARTName uart = (UARTName)pinmap_merge(uart_cts, uart_rts);

    if((FlowControlCTS == type) || (FlowControlRTSCTS== type)) {
        // Make sure pin is in the PinMap
        MBED_ASSERT(uart_cts != (UARTName)NC);

        // Enable the pin for CTS function
        pinmap_pinout(txflow, PinMap_UART_CTS);
    }

    if((FlowControlRTS == type) || (FlowControlRTSCTS== type))  {
        // Make sure pin is in the PinMap
        MBED_ASSERT(uart_rts != (UARTName)NC);

        // Enable the pin for RTS function
        pinmap_pinout(rxflow, PinMap_UART_RTS);
    }

    if(FlowControlRTSCTS == type){ 
        // Make sure that the pins are pointing to the same UART
        MBED_ASSERT(uart != (UARTName)NC);
    }

    // Enable hardware flow control
    obj->uart->ctrl |= MXC_F_UART_CTRL_HW_FLOW_CTRL_EN;
}
