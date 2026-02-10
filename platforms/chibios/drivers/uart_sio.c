// Copyright 2024 Stefan Kerkmann (@KarlK90)
// Copyright 2021 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "uart.h"
#include "gpio.h"
#include "chibios_config.h"
#include <hal.h>

#ifndef UART_DRIVER
#    define UART_DRIVER SIOD1
#endif

#ifndef UART_TX_PIN
#    define UART_TX_PIN A9
#endif

#ifndef UART_TX_PAL_MODE
#    ifdef USE_GPIOV1
#        define UART_TX_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define UART_TX_PAL_MODE 7
#    endif
#endif

#ifndef UART_RX_PIN
#    define UART_RX_PIN A10
#endif

#ifndef UART_RX_PAL_MODE
#    ifdef USE_GPIOV1
#        define UART_RX_PAL_MODE PAL_MODE_INPUT
#    else
#        define UART_RX_PAL_MODE 7
#    endif
#endif

#ifndef UART_CTS_PIN
#    define UART_CTS_PIN A11
#endif

#ifndef UART_CTS_PAL_MODE
#    ifdef USE_GPIOV1
#        define UART_CTS_PAL_MODE PAL_MODE_INPUT
#    else
#        define UART_CTS_PAL_MODE 7
#    endif
#endif

#ifndef UART_RTS_PIN
#    define UART_RTS_PIN A12
#endif

#ifndef UART_RTS_PAL_MODE
#    ifdef USE_GPIOV1
#        define UART_RTS_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define UART_RTS_PAL_MODE 7
#    endif
#endif

#ifndef UART_CR1
#    define UART_CR1 0
#endif

#ifndef UART_CR2
#    define UART_CR2 0
#endif

#ifndef UART_CR3
#    define UART_CR3 0
#endif

#if defined(MCU_RP)
// 38400 baud, 8 data bits, 1 stop bit, no parity, no flow control
static SIOConfig sioConfig = {
    .baud      = SIO_DEFAULT_BITRATE,
    .UARTLCR_H = (UART_UARTLCR_H_WLEN_8BITS | UART_UARTLCR_H_FEN),
    .UARTCR    = 0U,
    .UARTIFLS  = (UART_UARTIFLS_RXIFLSEL_1_8F | UART_UARTIFLS_TXIFLSEL_1_8E),
    .UARTDMACR = 0U,
};
#else
static SIOConfig sioConfig = {
    .baud = SIO_DEFAULT_BITRATE,
#    if defined(MCU_STM32) && defined(USE_USARTV3)
    .presc = USART_PRESC1,
#    endif
    .cr1 = UART_CR1,
    .cr2 = UART_CR2,
    .cr3 = UART_CR3,
};
#endif

void uart_init(uint32_t baud) {
    static bool is_initialised = false;

    if (is_initialised) {
        return;
    }
    is_initialised = true;

    sioConfig.baud = baud;

#if defined(USE_GPIOV1)
    palSetLineMode(UART_TX_PIN, UART_TX_PAL_MODE);
    palSetLineMode(UART_RX_PIN, UART_RX_PAL_MODE);
#else
    palSetLineMode(UART_TX_PIN, PAL_MODE_ALTERNATE(UART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(UART_RX_PIN, PAL_MODE_ALTERNATE(UART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif

    sioStart(&UART_DRIVER, &sioConfig);
}

void uart_write(uint8_t data) {
    chnPutTimeout(&UART_DRIVER, data, TIME_INFINITE);
}

uint8_t uart_read(void) {
    msg_t result = chnGetTimeout(&UART_DRIVER, TIME_INFINITE);

    if (sioHasRXErrorsX(&UART_DRIVER)) {
        sioGetAndClearErrors(&UART_DRIVER);
    }

    return (uint8_t)result;
}

void uart_transmit(const uint8_t *data, uint16_t length) {
    chnWrite(&UART_DRIVER, data, length);
}

void uart_receive(uint8_t *data, uint16_t length) {
    chnRead(&UART_DRIVER, data, length);

    if (sioHasRXErrorsX(&UART_DRIVER)) {
        sioGetAndClearErrors(&UART_DRIVER);
    }
}

bool uart_available() {
    return !sioIsRXEmptyX(&UART_DRIVER);
}
