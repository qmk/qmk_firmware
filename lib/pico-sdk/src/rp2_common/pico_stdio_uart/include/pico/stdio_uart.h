/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_STDIO_UART_H
#define _PICO_STDIO_UART_H

#include "pico/stdio.h"
#include "hardware/uart.h"

/** \brief Support for stdin/stdout using UART
 *  \defgroup pico_stdio_uart pico_stdio_uart
 *  \ingroup pico_stdio
 *
 *  Linking this library or calling `pico_enable_stdio_uart(TARGET ENABLED)` in the CMake (which
 *  achieves the same thing) will add UART to the drivers used for standard input/output
 */

// PICO_CONFIG: PICO_STDIO_UART_DEFAULT_CRLF, Default state of CR/LF translation for UART output, type=bool, default=PICO_STDIO_DEFAULT_CRLF, group=pico_stdio_uart
#ifndef PICO_STDIO_UART_DEFAULT_CRLF
#define PICO_STDIO_UART_DEFAULT_CRLF PICO_STDIO_DEFAULT_CRLF
#endif

// PICO_CONFIG: PICO_STDIO_UART_SUPPORT_CHARS_AVAILABLE_CALLBACK, Enable UART STDIO support for stdio_set_chars_available_callback. Can be disabled to make use of the uart elsewhere, type=bool default=1, group=pico_stdio_uart
#ifndef PICO_STDIO_UART_SUPPORT_CHARS_AVAILABLE_CALLBACK
#define PICO_STDIO_UART_SUPPORT_CHARS_AVAILABLE_CALLBACK 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern stdio_driver_t stdio_uart;

/*! \brief Explicitly initialize stdin/stdout over UART and add it to the current set of stdin/stdout drivers
 *  \ingroup pico_stdio_uart
 *
 * This method sets up PICO_DEFAULT_UART_TX_PIN for UART output (if defined), PICO_DEFAULT_UART_RX_PIN for input (if defined)
 * and configures the baud rate as PICO_DEFAULT_UART_BAUD_RATE.
 *
 * \note this method is automatically called by \ref stdio_init_all() if `pico_stdio_uart` is included in the build
 */
void stdio_uart_init(void);

/*! \brief Explicitly initialize stdout only (no stdin) over UART and add it to the current set of stdout drivers
 *  \ingroup pico_stdio_uart
 *
 * This method sets up PICO_DEFAULT_UART_TX_PIN for UART output (if defined) , and configures the baud rate as PICO_DEFAULT_UART_BAUD_RATE
 */
void stdout_uart_init(void);

/*! \brief Explicitly initialize stdin only (no stdout) over UART and add it to the current set of stdin drivers
 *  \ingroup pico_stdio_uart
 *
 * This method sets up PICO_DEFAULT_UART_RX_PIN for UART input (if defined) , and configures the baud rate as PICO_DEFAULT_UART_BAUD_RATE
 */
void stdin_uart_init(void);

/*! \brief Perform custom initialization initialize stdin/stdout over UART and add it to the current set of stdin/stdout drivers
 *  \ingroup pico_stdio_uart
 *
 * \param uart the uart instance to use, \ref uart0 or \ref uart1
 * \param baud_rate the baud rate in Hz
 * \param tx_pin the UART pin to use for stdout (or -1 for no stdout)
 * \param rx_pin the UART pin to use for stdin (or -1 for no stdin)
 */
void stdio_uart_init_full(uart_inst_t *uart, uint baud_rate, int tx_pin, int rx_pin);

#ifdef __cplusplus
}
#endif

#endif
