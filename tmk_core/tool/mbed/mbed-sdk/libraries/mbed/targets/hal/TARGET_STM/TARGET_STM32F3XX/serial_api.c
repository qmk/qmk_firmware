/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "mbed_assert.h"
#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include <string.h>

static const PinMap PinMap_UART_TX[] = {
    {PA_2,  UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PA_9,  UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PA_14, UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_3,  UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_6,  UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_9,  UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_10, UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PC_4,  UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PC_10, UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {NC,    NC,     0}
};

static const PinMap PinMap_UART_RX[] = {
    {PA_3,  UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PA_10, UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PA_15, UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_4,  UART_2, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_7,  UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_8,  UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PB_11, UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PC_5,  UART_1, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {PC_11, UART_3, STM_PIN_DATA(GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_7)},
    {NC,    NC,     0}
};

#define UART_NUM (2)

static uint32_t serial_irq_ids[UART_NUM] = {0};

static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

static void init_usart(serial_t *obj) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    USART_InitTypeDef USART_InitStructure;

    USART_Cmd(usart, DISABLE);

    USART_InitStructure.USART_BaudRate            = obj->baudrate;
    USART_InitStructure.USART_WordLength          = obj->databits;
    USART_InitStructure.USART_StopBits            = obj->stopbits;
    USART_InitStructure.USART_Parity              = obj->parity;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(usart, &USART_InitStructure);

    USART_Cmd(usart, ENABLE);
}

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    // Determine the UART to use
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);

    // Get the peripheral name from the pin and assign it to the object
    obj->uart = (UARTName)pinmap_merge(uart_tx, uart_rx);
    MBED_ASSERT(obj->uart != (UARTName)NC);

    // Enable USART clock
    if (obj->uart == UART_1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    }
    if (obj->uart == UART_2) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    }
    if (obj->uart == UART_3) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    }

    // Configure the UART pins
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);
    if (tx != NC) {
        pin_mode(tx, PullUp);
    }
    if (rx != NC) {
        pin_mode(rx, PullUp);
    }

    // Configure UART
    obj->baudrate = 9600;
    obj->databits = USART_WordLength_8b;
    obj->stopbits = USART_StopBits_1;
    obj->parity = USART_Parity_No;

    init_usart(obj);

    // The index is used by irq
    if (obj->uart == UART_1) obj->index = 0;
    if (obj->uart == UART_2) obj->index = 1;
    if (obj->uart == UART_3) obj->index = 2;

    // For stdio management
    if (obj->uart == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }

}

void serial_free(serial_t *obj) {
    serial_irq_ids[obj->index] = 0;
}

void serial_baud(serial_t *obj, int baudrate) {
    obj->baudrate = baudrate;
    init_usart(obj);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    if (data_bits == 8) {
        obj->databits = USART_WordLength_8b;
    } else {
        obj->databits = USART_WordLength_9b;
    }

    switch (parity) {
        case ParityOdd:
        case ParityForced0:
            obj->parity = USART_Parity_Odd;
            break;
        case ParityEven:
        case ParityForced1:
            obj->parity = USART_Parity_Even;
            break;
        default: // ParityNone
            obj->parity = USART_Parity_No;
            break;
    }

    if (stop_bits == 2) {
        obj->stopbits = USART_StopBits_2;
    } else {
        obj->stopbits = USART_StopBits_1;
    }

    init_usart(obj);
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/

// not api
static void uart_irq(USART_TypeDef* usart, int id) {
    if (serial_irq_ids[id] != 0) {
        if (USART_GetITStatus(usart, USART_IT_TC) != RESET) {
            irq_handler(serial_irq_ids[id], TxIrq);
            USART_ClearITPendingBit(usart, USART_IT_TC);
        }
        if (USART_GetITStatus(usart, USART_IT_RXNE) != RESET) {
            irq_handler(serial_irq_ids[id], RxIrq);
            USART_ClearITPendingBit(usart, USART_IT_RXNE);
        }
    }
}

static void uart1_irq(void) {
    uart_irq((USART_TypeDef*)UART_1, 0);
}
static void uart2_irq(void) {
    uart_irq((USART_TypeDef*)UART_2, 1);
}
static void uart3_irq(void) {
    uart_irq((USART_TypeDef*)UART_3, 2);
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);

    if (obj->uart == UART_1) {
        irq_n = USART1_IRQn;
        vector = (uint32_t)&uart1_irq;
    }

    if (obj->uart == UART_2) {
        irq_n = USART2_IRQn;
        vector = (uint32_t)&uart2_irq;
    }

    if (obj->uart == UART_3) {
        irq_n = USART3_IRQn;
        vector = (uint32_t)&uart3_irq;
    }

    if (enable) {

        if (irq == RxIrq) {
            USART_ITConfig(usart, USART_IT_RXNE, ENABLE);
        } else { // TxIrq
            USART_ITConfig(usart, USART_IT_TC, ENABLE);
        }

        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);

    } else { // disable

        int all_disabled = 0;

        if (irq == RxIrq) {
            USART_ITConfig(usart, USART_IT_RXNE, DISABLE);
            // Check if TxIrq is disabled too
            if ((usart->CR1 & USART_CR1_TXEIE) == 0) all_disabled = 1;
        } else { // TxIrq
            USART_ITConfig(usart, USART_IT_TXE, DISABLE);
            // Check if RxIrq is disabled too
            if ((usart->CR1 & USART_CR1_RXNEIE) == 0) all_disabled = 1;
        }

        if (all_disabled) NVIC_DisableIRQ(irq_n);

    }
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/

int serial_getc(serial_t *obj) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    while (!serial_readable(obj));
    return (int)(USART_ReceiveData(usart));
}

void serial_putc(serial_t *obj, int c) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    while (!serial_writable(obj));
    USART_SendData(usart, (uint16_t)c);
}

int serial_readable(serial_t *obj) {
    int status;
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    // Check if data is received
    status = ((USART_GetFlagStatus(usart, USART_FLAG_RXNE) != RESET) ? 1 : 0);
    return status;
}

int serial_writable(serial_t *obj) {
    int status;
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    // Check if data is transmitted
    status = ((USART_GetFlagStatus(usart, USART_FLAG_TXE) != RESET) ? 1 : 0);
    return status;
}

void serial_clear(serial_t *obj) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    USART_ClearFlag(usart, USART_FLAG_TXE);
    USART_ClearFlag(usart, USART_FLAG_RXNE);
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    USART_RequestCmd(usart, USART_Request_SBKRQ, ENABLE);
}

void serial_break_clear(serial_t *obj) {
    USART_TypeDef *usart = (USART_TypeDef *)(obj->uart);
    USART_RequestCmd(usart, USART_Request_SBKRQ, DISABLE);
    USART_ClearFlag(usart, USART_FLAG_SBK);
}
