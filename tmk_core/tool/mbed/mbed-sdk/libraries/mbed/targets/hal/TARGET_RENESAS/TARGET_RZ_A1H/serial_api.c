/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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
#include "gpio_api.h"

#include "scif_iodefine.h"
#include "cpg_iodefine.h"

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/
#define PCLK (66666666)     // Define the peripheral clock P1 frequency.

#define UART_NUM    8
#define IRQ_NUM     2

static void uart0_tx_irq(void);
static void uart1_tx_irq(void);
static void uart2_tx_irq(void);
static void uart3_tx_irq(void);
static void uart4_tx_irq(void);
static void uart5_tx_irq(void);
static void uart6_tx_irq(void);
static void uart7_tx_irq(void);
static void uart0_rx_irq(void);
static void uart1_rx_irq(void);
static void uart2_rx_irq(void);
static void uart3_rx_irq(void);
static void uart4_rx_irq(void);
static void uart5_rx_irq(void);
static void uart6_rx_irq(void);
static void uart7_rx_irq(void);


static const PinMap PinMap_UART_TX[] = {
    {P2_14 , UART0, 6},
    {P2_5  , UART1, 6},
    {P4_12 , UART1, 7},
    {P6_3  , UART2, 7},
    {P4_14 , UART2, 7},
    {P5_3  , UART3, 5},
    {P8_8  , UART3, 7},
    {P5_0  , UART4, 5},
    {P8_14 , UART4, 7},
    {P8_13 , UART5, 5},
    {P11_10, UART5, 3},
    {P6_6  , UART5, 5},
    {P5_6  , UART6, 5},
    {P11_1 , UART6, 4},
    {P7_4  , UART7, 4},
    {NC    , NC   , 0}
};

static const PinMap PinMap_UART_RX[] = {
    {P2_15 , UART0, 6},
    {P2_6  , UART1, 6},
    {P4_13 , UART1, 7},
    {P6_2  , UART2, 7},
    {P4_15 , UART2, 7},
    {P5_4  , UART3, 5},
    {P8_9  , UART3, 7},
    {P5_1  , UART4, 5},
    {P8_15 , UART4, 7},
    {P8_11 , UART5, 5},
    {P11_11, UART5, 3},
    {P6_7  , UART5, 5},
    {P5_7  , UART6, 5},
    {P11_2 , UART6, 4},
    {P7_5  , UART7, 4},
    {NC    , NC   , 0}
};

static const PinMap PinMap_UART_CTS[] = {
    {P2_3  , UART1, 6},
    {P11_7 , UART5, 3},
    {P7_6  , UART7, 4},
    {NC    , NC   , 0}
};
static const PinMap PinMap_UART_RTS[] = {
    {P2_7  , UART1, 6},
    {P11_8 , UART5, 3},
    {P7_7  , UART7, 4},
    {NC    , NC   , 0}
};



static const struct st_scif *SCIF[] = SCIF_ADDRESS_LIST;
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

struct serial_global_data_s {
    uint32_t serial_irq_id;
    gpio_t sw_rts, sw_cts;
    uint8_t count, rx_irq_set_flow, rx_irq_set_api;
};

static struct serial_global_data_s uart_data[UART_NUM];

static const IRQn_Type irq_set_tbl[UART_NUM][IRQ_NUM] = {
    {SCIFRXI0_IRQn, SCIFTXI0_IRQn},
    {SCIFRXI1_IRQn, SCIFTXI1_IRQn},
    {SCIFRXI2_IRQn, SCIFTXI2_IRQn},
    {SCIFRXI3_IRQn, SCIFTXI3_IRQn},
    {SCIFRXI4_IRQn, SCIFTXI4_IRQn},
    {SCIFRXI5_IRQn, SCIFTXI5_IRQn},
    {SCIFRXI6_IRQn, SCIFTXI6_IRQn},
    {SCIFRXI7_IRQn, SCIFTXI7_IRQn}
};

static const IRQHandler hander_set_tbl[UART_NUM][IRQ_NUM] = {
    {uart0_rx_irq, uart0_tx_irq},
    {uart1_rx_irq, uart1_tx_irq},
    {uart2_rx_irq, uart2_tx_irq},
    {uart3_rx_irq, uart3_tx_irq},
    {uart4_rx_irq, uart4_tx_irq},
    {uart5_rx_irq, uart5_tx_irq},
    {uart6_rx_irq, uart6_tx_irq},
    {uart7_rx_irq, uart7_tx_irq}
};

static __IO uint16_t *SCSCR_MATCH[] = {
    &SCSCR_0,
    &SCSCR_1,
    &SCSCR_2,
    &SCSCR_3,
    &SCSCR_4,
    &SCSCR_5,
    &SCSCR_6,
    &SCSCR_7,
};

static __IO uint16_t *SCFSR_MATCH[] = {
    &SCFSR_0,
    &SCFSR_1,
    &SCFSR_2,
    &SCFSR_3,
    &SCFSR_4,
    &SCFSR_5,
    &SCFSR_6,
    &SCFSR_7,
};


void serial_init(serial_t *obj, PinName tx, PinName rx) {
    volatile uint8_t dummy ;
    int is_stdio_uart = 0;
    // determine the UART to use
    uint32_t uart_tx = pinmap_peripheral(tx, PinMap_UART_TX);
    uint32_t uart_rx = pinmap_peripheral(rx, PinMap_UART_RX);
    uint32_t uart = pinmap_merge(uart_tx, uart_rx);

    MBED_ASSERT((int)uart != NC);

    obj->uart = (struct st_scif *)SCIF[uart];
    // enable power
    switch (uart) {
    case UART0:
        CPG.STBCR4 &= ~(1 <<  7);
        break;
    case UART1:
        CPG.STBCR4 &= ~(1 <<  6);
        break;
    case UART2:
        CPG.STBCR4 &= ~(1 <<  5);
        break;
    case UART3:
        CPG.STBCR4 &= ~(1 <<  4);
        break;
    case UART4:
        CPG.STBCR4 &= ~(1 <<  3);
        break;
    case UART5:
        CPG.STBCR4 &= ~(1 <<  2);
        break;
    case UART6:
        CPG.STBCR4 &= ~(1 <<  1);
        break;
    case UART7:
        CPG.STBCR4 &= ~(1 <<  0);
        break;
    }
    dummy = CPG.STBCR4;

    /* ==== SCIF initial setting ==== */
    /* ---- Serial control register (SCSCR) setting ---- */
    /* B'00 : Internal CLK */
    obj->uart->SCSCR = 0x0000u;          /* SCIF transmitting and receiving operations stop */

    /* ---- FIFO control register (SCFCR) setting ---- */
    /* Transmit FIFO reset & Receive FIFO data register reset */
    obj->uart->SCFCR = 0x0006;

    /* ---- Serial status register (SCFSR) setting ---- */
    dummy = obj->uart->SCFSR;
    obj->uart->SCFSR = (dummy & 0xFF6Cu);         /* ER,BRK,DR bit clear */

    /* ---- Line status register (SCLSR) setting ---- */
    /* ORER bit clear */
    obj->uart->SCLSR = 0;

    /* ---- Serial extension mode register (SCEMR) setting ----
    b7 BGDM - Baud rate generator double-speed mode  : Normal mode
    b0 ABCS - Base clock select in asynchronous mode : Base clock is 16 times the bit rate */
    obj->uart->SCEMR = 0x0000u;

    /* ---- Bit rate register (SCBRR) setting ---- */
    serial_baud  (obj, 9600);
    serial_format(obj, 8, ParityNone, 1);

    /* ---- FIFO control register (SCFCR) setting ---- */
    obj->uart->SCFCR = 0x0030u;

    /* ---- Serial port register (SCSPTR) setting ----
    b1 SPB2IO - Serial port break output : disabled
    b0 SPB2DT - Serial port break data   : High-level */
    obj->uart->SCSPTR = 0x0003u;    // SPB2IO = 1, SPB2DT = 1

    /* ---- Line status register (SCLSR) setting ----
    b0 ORER - Overrun error detect : clear */

    if (obj->uart->SCLSR & 0x0001) {
        obj->uart->SCLSR = 0u;      // ORER clear
    }

    // pinout the chosen uart
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);

    switch (uart) {
    case UART0:
        obj->index = 0;
        break;
    case UART1:
        obj->index = 1;
        break;
    case UART2:
        obj->index = 2;
        break;
    case UART3:
        obj->index = 3;
        break;
    case UART4:
        obj->index = 4;
        break;
    case UART5:
        obj->index = 5;
        break;
    case UART6:
        obj->index = 6;
        break;
    case UART7:
        obj->index = 7;
        break;
    }
    uart_data[obj->index].sw_rts.pin = NC;
    uart_data[obj->index].sw_cts.pin = NC;

    /* ---- Serial control register (SCSCR) setting ---- */
    /* Setting the TE and RE bits enables the TxD and RxD pins to be used. */
    obj->uart->SCSCR = 0x00F0;

    is_stdio_uart = (uart == STDIO_UART) ? (1) : (0);

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
    uint16_t DL;

    obj->uart->SCSMR &= ~0x0003;

    if (baudrate > 32552) {
        obj->uart->SCEMR = 0x0081;  // BGDM = 1, ABCS = 1
        DL = PCLK / (8 * baudrate);
        if (DL > 0) {
            DL--;
        }
        obj->uart->SCBRR = (uint8_t)DL;
    } else if (baudrate > 16276) {
        obj->uart->SCEMR = 0x0080;  // BGDM = 1
        obj->uart->SCBRR = PCLK / (16 * baudrate) - 1;
    } else if (baudrate > 8138) {
        obj->uart->SCEMR = 0x0000;
        obj->uart->SCBRR = PCLK / (32 * baudrate) - 1;
    } else if (baudrate > 4169) {
        obj->uart->SCSMR |= 0x0001;
        obj->uart->SCEMR = 0x0080;  // BGDM = 1
        obj->uart->SCBRR = PCLK / (64 * baudrate) - 1;
    } else if (baudrate > 2034) {
        obj->uart->SCSMR |= 0x0001;
        obj->uart->SCEMR = 0x0000;
        obj->uart->SCBRR = PCLK / (128 * baudrate) - 1;
    } else if (baudrate > 1017) {
        obj->uart->SCSMR |= 0x0002;
        obj->uart->SCEMR = 0x0080;  // BGDM = 1
        obj->uart->SCBRR = PCLK / (256 * baudrate) - 1;
    } else if (baudrate > 508) {
        obj->uart->SCSMR |= 0x0002;
        obj->uart->SCEMR = 0x0000;
        obj->uart->SCBRR = PCLK / (512 * baudrate) - 1;
    } else if (baudrate > 254) {
        obj->uart->SCSMR |= 0x0003;
        obj->uart->SCEMR = 0x0080;  // BGDM = 1
        obj->uart->SCBRR = PCLK / (1024 * baudrate) - 1;
    } else if (baudrate > 127) {
        obj->uart->SCSMR |= 0x0003;
        obj->uart->SCEMR = 0x0000;
        obj->uart->SCBRR = PCLK / (2048 * baudrate) - 1;
    } else {
        obj->uart->SCSMR |= 0x0003;
        obj->uart->SCEMR = 0x0000;
        obj->uart->SCBRR = 0xFFu;
    }
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    int parity_enable;
    int parity_select;

    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2)); // 0: 1 stop bits, 1: 2 stop bits
    MBED_ASSERT((data_bits > 4) && (data_bits < 9)); // 5: 5 data bits ... 3: 8 data bits
    MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) || (parity == ParityEven) ||
                (parity == ParityForced1) || (parity == ParityForced0));

    stop_bits = (stop_bits == 1)? 0:
                (stop_bits == 2)? 1:
                0; // must not to be

    data_bits = (data_bits == 8)? 0:
                (data_bits == 7)? 1:
                0; // must not to be

    switch (parity) {
    case ParityNone:
        parity_enable = 0;
        parity_select = 0;
        break;
    case ParityOdd:
        parity_enable = 1;
        parity_select = 1;
        break;
    case ParityEven:
        parity_enable = 1;
        parity_select = 0;
        break;
    case ParityForced1:
    case ParityForced0:
    default:
        parity_enable = 0;
        parity_select = 0;
        break;
    }

    obj->uart->SCSMR = data_bits          << 6
                       | parity_enable    << 5
                       | parity_select    << 4
                       | stop_bits        << 3;
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/

static void uart_tx_irq(IRQn_Type irq_num, uint32_t index) {
    __IO uint16_t *dmy_rd_scscr;
    __IO uint16_t *dmy_rd_scfsr;

    dmy_rd_scscr = SCSCR_MATCH[index];
    *dmy_rd_scscr &= 0x007B;                    // Clear TIE and Write to bit15~8,2 is always 0
    dmy_rd_scfsr = SCFSR_MATCH[index];
    *dmy_rd_scfsr = (*dmy_rd_scfsr & ~0x0020);  // Clear TDFE

    irq_handler(uart_data[index].serial_irq_id, TxIrq);
}

static void uart_rx_irq(IRQn_Type irq_num, uint32_t index) {
    __IO uint16_t *dmy_rd_scscr;
    __IO uint16_t *dmy_rd_scfsr;

    dmy_rd_scscr = SCSCR_MATCH[index];
    *dmy_rd_scscr &= 0x00B3;                    // Clear RIE,REIE and Write to bit15~8,2 is always 0
    dmy_rd_scfsr = SCFSR_MATCH[index];
    *dmy_rd_scfsr = (*dmy_rd_scfsr & ~0x0003);  // Clear RDF,DR

    irq_handler(uart_data[index].serial_irq_id, RxIrq);
}

/* TX handler */
static void uart0_tx_irq(void)  {
    uart_tx_irq(SCIFTXI0_IRQn, 0);
}
static void uart1_tx_irq(void)  {
    uart_tx_irq(SCIFTXI1_IRQn, 1);
}
static void uart2_tx_irq(void)  {
    uart_tx_irq(SCIFTXI2_IRQn, 2);
}
static void uart3_tx_irq(void)  {
    uart_tx_irq(SCIFTXI3_IRQn, 3);
}
static void uart4_tx_irq(void)  {
    uart_tx_irq(SCIFTXI4_IRQn, 4);
}
static void uart5_tx_irq(void)  {
    uart_tx_irq(SCIFTXI5_IRQn, 5);
}
static void uart6_tx_irq(void)  {
    uart_tx_irq(SCIFTXI6_IRQn, 6);
}
static void uart7_tx_irq(void)  {
    uart_tx_irq(SCIFTXI7_IRQn, 7);
}
/* RX handler */
static void uart0_rx_irq(void)  {
    uart_rx_irq(SCIFRXI0_IRQn, 0);
}
static void uart1_rx_irq(void)  {
    uart_rx_irq(SCIFRXI1_IRQn, 1);
}
static void uart2_rx_irq(void)  {
    uart_rx_irq(SCIFRXI2_IRQn, 2);
}
static void uart3_rx_irq(void)  {
    uart_rx_irq(SCIFRXI3_IRQn, 3);
}
static void uart4_rx_irq(void)  {
    uart_rx_irq(SCIFRXI4_IRQn, 4);
}
static void uart5_rx_irq(void)  {
    uart_rx_irq(SCIFRXI5_IRQn, 5);
}
static void uart6_rx_irq(void)  {
    uart_rx_irq(SCIFRXI6_IRQn, 6);
}
static void uart7_rx_irq(void)  {
    uart_rx_irq(SCIFRXI7_IRQn, 7);
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    uart_data[obj->index].serial_irq_id = id;
}

static void serial_irq_set_internal(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type IRQn;
    IRQHandler handler;

    IRQn = irq_set_tbl[obj->index][irq];
    handler = hander_set_tbl[obj->index][irq];

    if ((obj->index >= 0) && (obj->index <= 7)) {
        if (enable) {
            InterruptHandlerRegister(IRQn, (void (*)(uint32_t))handler);
            GIC_SetPriority(IRQn, 5);
            GIC_EnableIRQ(IRQn);
        } else {
            GIC_DisableIRQ(IRQn);
        }
    }
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    if (RxIrq == irq) {
        uart_data[obj->index].rx_irq_set_api = enable;
    }
    serial_irq_set_internal(obj, irq, enable);
}

static void serial_flow_irq_set(serial_t *obj, uint32_t enable) {
    uart_data[obj->index].rx_irq_set_flow = enable;
    serial_irq_set_internal(obj, RxIrq, enable);
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj) {
    uint16_t err_read;
    int data;
    int was_masked;

    was_masked = __disable_irq();
    if (obj->uart->SCFSR & 0x93) {
        err_read = obj->uart->SCFSR;
        obj->uart->SCFSR = (err_read & ~0x93);
    }
    obj->uart->SCSCR |= 0x0040;     // Set RIE
    if (!was_masked) {
        __enable_irq();
    }

    if (obj->uart->SCLSR & 0x0001) {
        obj->uart->SCLSR = 0u;      // ORER clear
    }

    while (!serial_readable(obj));
    data = obj->uart->SCFRDR & 0xff;

    was_masked = __disable_irq();
    err_read = obj->uart->SCFSR;
    obj->uart->SCFSR = (err_read & 0xfffD);     // Clear RDF
    if (!was_masked) {
        __enable_irq();
    }

    if (err_read & 0x80) {
        data = -1;  //err
    }
    return data;
}

void serial_putc(serial_t *obj, int c) {
    uint16_t dummy_read;
    int was_masked;

    was_masked = __disable_irq();
    obj->uart->SCSCR |= 0x0080;     // Set TIE
    if (!was_masked) {
        __enable_irq();
    }
    while (!serial_writable(obj));
    obj->uart->SCFTDR = c;
    was_masked = __disable_irq();
    dummy_read = obj->uart->SCFSR;
    obj->uart->SCFSR = (dummy_read & 0xff9f);  // Clear TEND/TDFE
    if (!was_masked) {
        __enable_irq();
    }
    uart_data[obj->index].count++;
}

int serial_readable(serial_t *obj) {
    return ((obj->uart->SCFSR & 0x02) != 0);  // RDF
}

int serial_writable(serial_t *obj) {
    return ((obj->uart->SCFSR & 0x20) != 0);  // TDFE
}

void serial_clear(serial_t *obj) {
    int was_masked;
    was_masked = __disable_irq();

    obj->uart->SCFCR |=  0x06;          // TFRST = 1, RFRST = 1
    obj->uart->SCFCR &= ~0x06;          // TFRST = 0, RFRST = 0
    obj->uart->SCFSR &= ~0x0093u;       // ER, BRK, RDF, DR = 0

    if (!was_masked) {
        __enable_irq();
    }
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    int was_masked;
    was_masked = __disable_irq();
    // TxD Output(L)
    obj->uart->SCSPTR &= ~0x0001u;  // SPB2DT = 0
    obj->uart->SCSCR &= ~0x0020u;   // TE = 0 (Output disable)
    if (!was_masked) {
        __enable_irq();
    }
}

void serial_break_clear(serial_t *obj) {
    int was_masked;
    was_masked = __disable_irq();
    obj->uart->SCSCR |= 0x0020u; // TE = 1 (Output enable)
    obj->uart->SCSPTR |= 0x0001u; // SPB2DT = 1
    if (!was_masked) {
        __enable_irq();
    }
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow) {
    // determine the UART to use
    int was_masked;

    serial_flow_irq_set(obj, 0);

    if (type == FlowControlRTSCTS) {
        was_masked = __disable_irq();
        obj->uart->SCFCR = 0x0008u;   // CTS/RTS enable
        if (!was_masked) {
            __enable_irq();
        }
        pinmap_pinout(rxflow, PinMap_UART_RTS);
        pinmap_pinout(txflow, PinMap_UART_CTS);
    } else {
        was_masked = __disable_irq();
        obj->uart->SCFCR = 0x0000u; // CTS/RTS diable
        if (!was_masked) {
            __enable_irq();
        }
    }
}




