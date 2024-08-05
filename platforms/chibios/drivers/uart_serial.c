// Copyright 2024 Stefan Kerkmann (@KarlK90)
// Copyright 2021 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "uart.h"

#if defined(MCU_KINETIS)
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE};
#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
static SerialConfig serialConfig = {
    SERIAL_DEFAULT_BITRATE, UART_WRDLEN, UART_STPBIT, UART_PARITY, UART_ATFLCT,
};
#else
static SerialConfig serialConfig = {
    SERIAL_DEFAULT_BITRATE,
    UART_CR1,
    UART_CR2,
    UART_CR3,
};
#endif

void uart_init(uint32_t baud) {
    static bool is_initialised = false;

    if (is_initialised) {
        return;
    }
    is_initialised = true;

#if defined(MCU_KINETIS)
    serialConfig.sc_speed = baud;
#else
    serialConfig.speed = baud;
#endif

#if defined(USE_GPIOV1)
    palSetLineMode(UART_TX_PIN, UART_TX_PAL_MODE);
    palSetLineMode(UART_RX_PIN, UART_RX_PAL_MODE);
#else
    palSetLineMode(UART_TX_PIN, PAL_MODE_ALTERNATE(UART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(UART_RX_PIN, PAL_MODE_ALTERNATE(UART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif

    sdStart(&UART_DRIVER, &serialConfig);
}

void uart_write(uint8_t data) {
    sdPut(&UART_DRIVER, data);
}

uint8_t uart_read(void) {
    return (uint8_t)sdGet(&UART_DRIVER);
}

void uart_transmit(const uint8_t *data, uint16_t length) {
    sdWrite(&UART_DRIVER, data, length);
}

void uart_receive(uint8_t *data, uint16_t length) {
    sdRead(&UART_DRIVER, data, length);
}

bool uart_available(void) {
    return !sdGetWouldBlock(&UART_DRIVER);
}
