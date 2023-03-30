/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_UART_H
#define _HARDWARE_UART_H

#include "pico.h"

#ifndef PARAM_ASSERTIONS_ENABLED_UART
#define PARAM_ASSERTIONS_ENABLED_UART 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct uart_inst uart_inst_t;

extern uart_inst_t * const uart0;
extern uart_inst_t * const uart1;
#define uart_default uart0

typedef enum {
    UART_PARITY_NONE,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} uart_parity_t;

// ----------------------------------------------------------------------------
// Setup

// Put the UART into a known state, and enable it. Must be called before other
// functions.
uint uart_init(uart_inst_t *uart, uint baudrate);

// Disable the UART if it is no longer used. Must be reinitialised before
// being used again.
void uart_deinit(uart_inst_t *uart);

// Set baud rate as close as possible to requested, and return actual rate.
uint uart_set_baudrate(uart_inst_t *uart, uint baudrate);

// cts: enable flow control of TX by clear-to-send input
// rts: enable assertion of request-to-send output by RX flow control
void uart_set_hw_flow(uart_inst_t *uart, bool cts, bool rts);

// Configure how the UART serialises and deserialises data on the wire
void uart_set_format(uart_inst_t *uart, uint data_bits, uint stop_bits, uart_parity_t parity);

// Enable the UART's interrupt output. Need to install an interrupt handler first.
void uart_set_irq_enables(uart_inst_t *uart, bool rx_has_data, bool tx_needs_data);

// ----------------------------------------------------------------------------
// Generic input/output

// If returns 0, no space is available in the UART to write more data.
// If returns nonzero, at least that many bytes can be written without blocking.
size_t uart_is_writable(uart_inst_t *uart);

// If returns 0, no data is available to be read from UART.
// If returns nonzero, at least that many bytes can be written without blocking.
size_t uart_is_readable(uart_inst_t *uart);

// Write len bytes directly from src to the UART
void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len);

// Read len bytes directly from the UART to dst
void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len);

// ----------------------------------------------------------------------------
// UART-specific operations and aliases

void uart_putc(uart_inst_t *uart, char c);

void uart_puts(uart_inst_t *uart, const char *s);

char uart_getc(uart_inst_t *uart);

// en: assert break condition (TX held low) if true. Clear break condition if false.
void uart_set_break(uart_inst_t *uart, bool en);

void uart_default_tx_wait_blocking();

#ifdef __cplusplus
}
#endif

#endif
