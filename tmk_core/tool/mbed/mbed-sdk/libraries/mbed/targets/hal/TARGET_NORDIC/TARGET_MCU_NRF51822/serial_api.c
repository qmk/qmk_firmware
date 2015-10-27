/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
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
//#include <math.h>
#include <string.h>
#include "mbed_assert.h"

#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/
#define UART_NUM    1

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;
static uint32_t acceptedSpeeds[17][2] = {{1200, UART_BAUDRATE_BAUDRATE_Baud1200},
                                         {2400, UART_BAUDRATE_BAUDRATE_Baud2400},
                                         {4800, UART_BAUDRATE_BAUDRATE_Baud4800},
                                         {9600, UART_BAUDRATE_BAUDRATE_Baud9600},
                                         {14400, UART_BAUDRATE_BAUDRATE_Baud14400},
                                         {19200, UART_BAUDRATE_BAUDRATE_Baud19200},
                                         {28800, UART_BAUDRATE_BAUDRATE_Baud28800},
                                         {31250, (0x00800000UL) /* 31250 baud */},
                                         {38400, UART_BAUDRATE_BAUDRATE_Baud38400},
                                         {57600, UART_BAUDRATE_BAUDRATE_Baud57600},
                                         {76800, UART_BAUDRATE_BAUDRATE_Baud76800},
                                         {115200, UART_BAUDRATE_BAUDRATE_Baud115200},
                                         {230400, UART_BAUDRATE_BAUDRATE_Baud230400},
                                         {250000, UART_BAUDRATE_BAUDRATE_Baud250000},
                                         {460800, UART_BAUDRATE_BAUDRATE_Baud460800},
                                         {921600, UART_BAUDRATE_BAUDRATE_Baud921600},
                                         {1000000, UART_BAUDRATE_BAUDRATE_Baud1M}};

int stdio_uart_inited = 0;
serial_t stdio_uart;


void serial_init(serial_t *obj, PinName tx, PinName rx) {
    UARTName uart = UART_0;
    obj->uart = (NRF_UART_Type *)uart;

    //pin configurations --
    NRF_GPIO->DIR |= (1 << tx); //TX_PIN_NUMBER);
    NRF_GPIO->DIR |= (1 << RTS_PIN_NUMBER);

    NRF_GPIO->DIR &= ~(1 << rx); //RX_PIN_NUMBER);
    NRF_GPIO->DIR &= ~(1 << CTS_PIN_NUMBER);


    // set default baud rate and format
    serial_baud  (obj, 9600);
    serial_format(obj, 8, ParityNone, 1);

    obj->uart->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
    obj->uart->TASKS_STARTTX = 1;
    obj->uart->TASKS_STARTRX = 1;
    obj->uart->EVENTS_RXDRDY = 0;
    // dummy write needed or TXDRDY trails write rather than leads write.
    //  pins are disconnected so nothing is physically transmitted on the wire
    obj->uart->TXD = 0;

    obj->index = 0;
    
    obj->uart->PSELRTS = RTS_PIN_NUMBER;
    obj->uart->PSELTXD = tx; //TX_PIN_NUMBER;
    obj->uart->PSELCTS = CTS_PIN_NUMBER;
    obj->uart->PSELRXD = rx; //RX_PIN_NUMBER;

    // set rx/tx pins in PullUp mode
    if (tx != NC) {
        pin_mode(tx, PullUp);
    }
    if (rx != NC) {
        pin_mode(rx, PullUp);
    }

    if (uart == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj)
{
    serial_irq_ids[obj->index] = 0;
}

// serial_baud
// set the baud rate, taking in to account the current SystemFrequency
void serial_baud(serial_t *obj, int baudrate)
{
    if (baudrate<=1200) {
        obj->uart->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud1200;
        return;
    }

    for (int i = 1; i<17; i++) {
        if (baudrate<acceptedSpeeds[i][0]) {
            obj->uart->BAUDRATE = acceptedSpeeds[i - 1][1];
            return;
        }
    }
    obj->uart->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud1M;
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{
    // 0: 1 stop bits, 1: 2 stop bits
    // int parity_enable, parity_select;
    switch (parity) {
        case ParityNone:
            obj->uart->CONFIG = 0;
            break;
        default:
            obj->uart->CONFIG = (UART_CONFIG_PARITY_Included << UART_CONFIG_PARITY_Pos);
            return;
    }
    //no Flow Control
}

//******************************************************************************
// * INTERRUPT HANDLING
//******************************************************************************
static inline void uart_irq(uint32_t iir, uint32_t index)
{
    SerialIrq irq_type;
    switch (iir) {
        case 1:
            irq_type = TxIrq;
            break;
        case 2:
            irq_type = RxIrq;
            break;

        default:
            return;
    }

    if (serial_irq_ids[index] != 0) {
        irq_handler(serial_irq_ids[index], irq_type);
    }
}

#ifdef __cplusplus
extern "C" {
#endif
void UART0_IRQHandler()
{
    uint32_t irtype = 0;

    if((NRF_UART0->INTENSET & 0x80) && NRF_UART0->EVENTS_TXDRDY) {
        irtype = 1;
    } else if((NRF_UART0->INTENSET & 0x04) && NRF_UART0->EVENTS_RXDRDY) {
        irtype = 2;
    }
    uart_irq(irtype, 0);
}

#ifdef __cplusplus
}
#endif
void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
    irq_handler                = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    IRQn_Type irq_n = (IRQn_Type)0;

    switch ((int)obj->uart) {
        case UART_0:
            irq_n = UART0_IRQn;
            break;
    }

    if (enable) {
        switch (irq) {
            case RxIrq:
                obj->uart->INTENSET = (UART_INTENSET_RXDRDY_Msk);
                break;
            case TxIrq:
                obj->uart->INTENSET = (UART_INTENSET_TXDRDY_Msk);
                break;
        }
        NVIC_SetPriority(irq_n, 3);
        NVIC_EnableIRQ(irq_n);
    } else { // disable
        // maseked writes to INTENSET dont disable and masked writes to
        //  INTENCLR seemed to clear the entire register, not bits.
        //  Added INTEN to memory map and seems to allow set and clearing of specific bits as desired
        int all_disabled = 0;
        switch (irq) {
            case RxIrq:
                obj->uart->INTENCLR = (UART_INTENCLR_RXDRDY_Msk);
                all_disabled        =  (obj->uart->INTENCLR & (UART_INTENCLR_TXDRDY_Msk)) == 0;
                break;
            case TxIrq:
                obj->uart->INTENCLR = (UART_INTENCLR_TXDRDY_Msk);
                all_disabled        =  (obj->uart->INTENCLR & (UART_INTENCLR_RXDRDY_Msk)) == 0;
                break;
        }

        if (all_disabled) {
            NVIC_DisableIRQ(irq_n);
        }
    }
}

//******************************************************************************
//* READ/WRITE
//******************************************************************************
int serial_getc(serial_t *obj)
{
    while (!serial_readable(obj)) {
    }

    obj->uart->EVENTS_RXDRDY = 0;

    return (uint8_t)obj->uart->RXD;
}

void serial_putc(serial_t *obj, int c)
{
    while (!serial_writable(obj)) {
    }

    obj->uart->EVENTS_TXDRDY = 0;
    obj->uart->TXD = (uint8_t)c;
}

int serial_readable(serial_t *obj)
{
    return (obj->uart->EVENTS_RXDRDY == 1);
}

int serial_writable(serial_t *obj)
{
    return (obj->uart->EVENTS_TXDRDY == 1);
}

void serial_break_set(serial_t *obj)
{
    obj->uart->TASKS_SUSPEND = 1;
}

void serial_break_clear(serial_t *obj)
{
    obj->uart->TASKS_STARTTX = 1;
    obj->uart->TASKS_STARTRX = 1;
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow)
{

    if (type == FlowControlRTSCTS || type == FlowControlRTS) {
        NRF_GPIO->DIR |= (1<<rxflow);
        pin_mode(rxflow, PullUp);
        obj->uart->PSELRTS = rxflow;

        obj->uart->CONFIG |= 0x01; // Enable HWFC
    }

    if (type == FlowControlRTSCTS || type == FlowControlCTS) {
        NRF_GPIO->DIR &= ~(1<<txflow);
        pin_mode(txflow, PullUp);
        obj->uart->PSELCTS = txflow;

        obj->uart->CONFIG |= 0x01; // Enable HWFC;
    }

    if (type == FlowControlNone) {
        obj->uart->PSELRTS = 0xFFFFFFFF; // Disable RTS
        obj->uart->PSELCTS = 0xFFFFFFFF; // Disable CTS

        obj->uart->CONFIG &= ~0x01; // Enable HWFC;
    }
}

void serial_clear(serial_t *obj) {
}
