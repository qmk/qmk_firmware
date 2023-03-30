/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_UART_H
#define _HARDWARE_UART_H

#include "pico.h"
#include "hardware/structs/uart.h"
#include "hardware/regs/dreq.h"

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_UART, Enable/disable assertions in the UART module, type=bool, default=0, group=hardware_uart
#ifndef PARAM_ASSERTIONS_ENABLED_UART
#define PARAM_ASSERTIONS_ENABLED_UART 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

// PICO_CONFIG: PICO_UART_ENABLE_CRLF_SUPPORT, Enable/disable CR/LF translation support, type=bool, default=1, group=hardware_uart
#ifndef PICO_UART_ENABLE_CRLF_SUPPORT
#define PICO_UART_ENABLE_CRLF_SUPPORT 1
#endif

// PICO_CONFIG: PICO_UART_DEFAULT_CRLF, Enable/disable CR/LF translation on UART, type=bool, default=0, depends=PICO_UART_ENABLE_CRLF_SUPPORT, group=hardware_uart
#ifndef PICO_UART_DEFAULT_CRLF
#define PICO_UART_DEFAULT_CRLF 0
#endif

// PICO_CONFIG: PICO_DEFAULT_UART, Define the default UART used for printf etc, min=0, max=1, group=hardware_uart
// PICO_CONFIG: PICO_DEFAULT_UART_TX_PIN, Define the default UART TX pin, min=0, max=29, group=hardware_uart
// PICO_CONFIG: PICO_DEFAULT_UART_RX_PIN, Define the default UART RX pin, min=0, max=29, group=hardware_uart

// PICO_CONFIG: PICO_DEFAULT_UART_BAUD_RATE, Define the default UART baudrate, max=921600, default=115200, group=hardware_uart
#ifndef PICO_DEFAULT_UART_BAUD_RATE
#define PICO_DEFAULT_UART_BAUD_RATE 115200   ///< Default baud rate
#endif

/** \file hardware/uart.h
 *  \defgroup hardware_uart hardware_uart
 *
 * Hardware UART API
 *
 * RP2040 has 2 identical instances of a UART peripheral, based on the ARM PL011. Each UART can be connected to a number
 * of GPIO pins as defined in the GPIO muxing.
 *
 * Only the TX, RX, RTS, and CTS signals are
 * connected, meaning that the modem mode and IrDA mode of the PL011 are not supported.
 *
 * \subsection uart_example Example
 * \addtogroup hardware_uart
 *
 *  \code
 *  int main() {
 *
 *     // Initialise UART 0
 *     uart_init(uart0, 115200);
 *
 *     // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
 *     gpio_set_function(0, GPIO_FUNC_UART);
 *     gpio_set_function(1, GPIO_FUNC_UART);
 *
 *     uart_puts(uart0, "Hello world!");
 * }
 * \endcode
 */

// Currently always a pointer to hw but it might not be in the future
typedef struct uart_inst uart_inst_t;

/** The UART identifiers for use in UART functions.
 *
 * e.g. uart_init(uart1, 48000)
 *
 *  \ingroup hardware_uart
 * @{
 */
#define uart0 ((uart_inst_t *)uart0_hw) ///< Identifier for UART instance 0
#define uart1 ((uart_inst_t *)uart1_hw) ///< Identifier for UART instance 1

/** @} */

#if !defined(PICO_DEFAULT_UART_INSTANCE) && defined(PICO_DEFAULT_UART)
#define PICO_DEFAULT_UART_INSTANCE (__CONCAT(uart,PICO_DEFAULT_UART))
#endif

#ifdef PICO_DEFAULT_UART_INSTANCE
#define uart_default PICO_DEFAULT_UART_INSTANCE
#endif

/*! \brief Convert UART instance to hardware instance number
 *  \ingroup hardware_uart
 *
 * \param uart UART instance
 * \return Number of UART, 0 or 1.
 */
static inline uint uart_get_index(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    return uart == uart1 ? 1 : 0;
}

static inline uart_inst_t *uart_get_instance(uint instance) {
    static_assert(NUM_UARTS == 2, "");
    invalid_params_if(UART, instance >= NUM_UARTS);
    return instance ? uart1 : uart0;
}

static inline uart_hw_t *uart_get_hw(uart_inst_t *uart) {
    uart_get_index(uart); // check it is a hw uart
    return (uart_hw_t *)uart;
}

/** \brief UART Parity enumeration
 *  \ingroup hardware_uart
 */
typedef enum {
    UART_PARITY_NONE,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} uart_parity_t;

// ----------------------------------------------------------------------------
// Setup

/*! \brief Initialise a UART
 *  \ingroup hardware_uart
 *
 * Put the UART into a known state, and enable it. Must be called before other
 * functions.
 *
 * \note There is no guarantee that the baudrate requested will be possible, the nearest will be chosen,
 * and this function will return the configured baud rate.
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param baudrate Baudrate of UART in Hz
 * \return Actual set baudrate
 */
uint uart_init(uart_inst_t *uart, uint baudrate);

/*! \brief DeInitialise a UART
 *  \ingroup hardware_uart
 *
 * Disable the UART if it is no longer used. Must be reinitialised before
 * being used again.
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 */
void uart_deinit(uart_inst_t *uart);

/*! \brief Set UART baud rate
 *  \ingroup hardware_uart
 *
 * Set baud rate as close as possible to requested, and return actual rate selected.
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param baudrate Baudrate in Hz
 * \return Actual set baudrate
 */
uint uart_set_baudrate(uart_inst_t *uart, uint baudrate);

/*! \brief Set UART flow control CTS/RTS
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param cts If true enable flow control of TX  by clear-to-send input
 * \param rts If true enable assertion of request-to-send output by RX flow control
 */
static inline void uart_set_hw_flow(uart_inst_t *uart, bool cts, bool rts) {
    hw_write_masked(&uart_get_hw(uart)->cr,
                   (bool_to_bit(cts) << UART_UARTCR_CTSEN_LSB) | (bool_to_bit(rts) << UART_UARTCR_RTSEN_LSB),
                   UART_UARTCR_RTSEN_BITS | UART_UARTCR_CTSEN_BITS);
}

/*! \brief Set UART data format
 *  \ingroup hardware_uart
 *
 * Configure the data format (bits etc() for the UART
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param data_bits Number of bits of data. 5..8
 * \param stop_bits Number of stop bits 1..2
 * \param parity Parity option.
 */
static inline void uart_set_format(uart_inst_t *uart, uint data_bits, uint stop_bits, uart_parity_t parity) {
    invalid_params_if(UART, data_bits < 5 || data_bits > 8);
    invalid_params_if(UART, stop_bits != 1 && stop_bits != 2);
    invalid_params_if(UART, parity != UART_PARITY_NONE && parity != UART_PARITY_EVEN && parity != UART_PARITY_ODD);
    hw_write_masked(&uart_get_hw(uart)->lcr_h,
                   ((data_bits - 5u) << UART_UARTLCR_H_WLEN_LSB) |
                   ((stop_bits - 1u) << UART_UARTLCR_H_STP2_LSB) |
                   (bool_to_bit(parity != UART_PARITY_NONE) << UART_UARTLCR_H_PEN_LSB) |
                   (bool_to_bit(parity == UART_PARITY_EVEN) << UART_UARTLCR_H_EPS_LSB),
                   UART_UARTLCR_H_WLEN_BITS |
                   UART_UARTLCR_H_STP2_BITS |
                   UART_UARTLCR_H_PEN_BITS |
                   UART_UARTLCR_H_EPS_BITS);
}

/*! \brief Setup UART interrupts
 *  \ingroup hardware_uart
 *
 * Enable the UART's interrupt output. An interrupt handler will need to be installed prior to calling
 * this function.
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param rx_has_data If true an interrupt will be fired when the RX FIFO contains data.
 * \param tx_needs_data If true an interrupt will be fired when the TX FIFO needs data.
 */
static inline void uart_set_irq_enables(uart_inst_t *uart, bool rx_has_data, bool tx_needs_data) {
    // Both UARTRXINTR (RX) and UARTRTINTR (RX timeout) interrupts are
    // required for rx_has_data. RX asserts when >=4 characters are in the RX
    // FIFO (for RXIFLSEL=0). RT asserts when there are >=1 characters and no
    // more have been received for 32 bit periods.
    uart_get_hw(uart)->imsc = (bool_to_bit(tx_needs_data) << UART_UARTIMSC_TXIM_LSB) |
                              (bool_to_bit(rx_has_data) << UART_UARTIMSC_RXIM_LSB) |
                              (bool_to_bit(rx_has_data) << UART_UARTIMSC_RTIM_LSB);
    if (rx_has_data) {
        // Set minimum threshold
        hw_write_masked(&uart_get_hw(uart)->ifls, 0 << UART_UARTIFLS_RXIFLSEL_LSB,
                        UART_UARTIFLS_RXIFLSEL_BITS);
    }
    if (tx_needs_data) {
        // Set maximum threshold
        hw_write_masked(&uart_get_hw(uart)->ifls, 0 << UART_UARTIFLS_TXIFLSEL_LSB,
                        UART_UARTIFLS_TXIFLSEL_BITS);
    }
}

/*! \brief Test if specific UART is enabled
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \return true if the UART is enabled
 */
static inline bool uart_is_enabled(uart_inst_t *uart) {
    return !!(uart_get_hw(uart)->cr & UART_UARTCR_UARTEN_BITS);
}

/*! \brief Enable/Disable the FIFOs on specified UART
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param enabled true to enable FIFO (default), false to disable
 */
static inline void uart_set_fifo_enabled(uart_inst_t *uart, bool enabled) {
    hw_write_masked(&uart_get_hw(uart)->lcr_h,
                   (bool_to_bit(enabled) << UART_UARTLCR_H_FEN_LSB),
                   UART_UARTLCR_H_FEN_BITS);
}


// ----------------------------------------------------------------------------
// Generic input/output

/*! \brief Determine if space is available in the TX FIFO
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \return false if no space available, true otherwise
 */
static inline bool uart_is_writable(uart_inst_t *uart) {
    return !(uart_get_hw(uart)->fr & UART_UARTFR_TXFF_BITS);
}

/*! \brief Wait for the UART TX fifo to be drained
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 */
static inline void uart_tx_wait_blocking(uart_inst_t *uart) {
    while (uart_get_hw(uart)->fr & UART_UARTFR_BUSY_BITS) tight_loop_contents();
}

/*! \brief Determine whether data is waiting in the RX FIFO
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \return true if the RX FIFO is not empty, otherwise false.
 *
 */
static inline bool uart_is_readable(uart_inst_t *uart) {
    // PL011 doesn't expose levels directly, so return values are only 0 or 1
    return !(uart_get_hw(uart)->fr & UART_UARTFR_RXFE_BITS);
}

/*! \brief  Write to the UART for transmission.
 *  \ingroup hardware_uart
 *
 * This function will block until all the data has been sent to the UART
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param src The bytes to send
 * \param len The number of bytes to send
 */
static inline void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        while (!uart_is_writable(uart))
            tight_loop_contents();
        uart_get_hw(uart)->dr = *src++;
    }
}

/*! \brief  Read from the UART
 *  \ingroup hardware_uart
 *
 * This function blocks until len characters have been read from the UART
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param dst Buffer to accept received bytes
 * \param len The number of bytes to receive.
 */
static inline void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        while (!uart_is_readable(uart))
            tight_loop_contents();
        *dst++ = (uint8_t) uart_get_hw(uart)->dr;
    }
}

// ----------------------------------------------------------------------------
// UART-specific operations and aliases

/*! \brief  Write single character to UART for transmission.
 *  \ingroup hardware_uart
 *
 * This function will block until the entire character has been sent
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param c The character  to send
 */
static inline void uart_putc_raw(uart_inst_t *uart, char c) {
    uart_write_blocking(uart, (const uint8_t *) &c, 1);
}

/*! \brief  Write single character to UART for transmission, with optional CR/LF conversions
 *  \ingroup hardware_uart
 *
 * This function will block until the character has been sent
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param c The character  to send
 */
static inline void uart_putc(uart_inst_t *uart, char c) {
#if PICO_UART_ENABLE_CRLF_SUPPORT
    extern short uart_char_to_line_feed[NUM_UARTS];
    if (uart_char_to_line_feed[uart_get_index(uart)] == c)
        uart_putc_raw(uart, '\r');
#endif
    uart_putc_raw(uart, c);
}

/*! \brief  Write string to UART for transmission, doing any CR/LF conversions
 *  \ingroup hardware_uart
 *
 * This function will block until the entire string has been sent
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param s The null terminated string to send
 */
static inline void uart_puts(uart_inst_t *uart, const char *s) {
#if PICO_UART_ENABLE_CRLF_SUPPORT
    bool last_was_cr = false;
    while (*s) {
        // Don't add extra carriage returns if one is present
        if (last_was_cr)
            uart_putc_raw(uart, *s);
        else
            uart_putc(uart, *s);
        last_was_cr = *s++ == '\r';
    }
#else
    while (*s)
        uart_putc(uart, *s++);
#endif
}

/*! \brief  Read a single character from the UART
 *  \ingroup hardware_uart
 *
 * This function will block until a character has been read
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \return The character read.
 */
static inline char uart_getc(uart_inst_t *uart) {
    char c;
    uart_read_blocking(uart, (uint8_t *) &c, 1);
    return c;
}

/*! \brief Assert a break condition on the UART transmission.
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param en Assert break condition (TX held low) if true. Clear break condition if false.
 */
static inline void uart_set_break(uart_inst_t *uart, bool en) {
    if (en)
        hw_set_bits(&uart_get_hw(uart)->lcr_h, UART_UARTLCR_H_BRK_BITS);
    else
        hw_clear_bits(&uart_get_hw(uart)->lcr_h, UART_UARTLCR_H_BRK_BITS);
}

/*! \brief Set CR/LF conversion on UART
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param translate If true, convert line feeds to carriage return on transmissions
 */
void uart_set_translate_crlf(uart_inst_t *uart, bool translate);

/*! \brief Wait for the default UART's TX FIFO to be drained
 *  \ingroup hardware_uart
 */
static inline void uart_default_tx_wait_blocking(void) {
#ifdef uart_default
    uart_tx_wait_blocking(uart_default);
#else
    assert(false);
#endif
}

/*! \brief Wait for up to a certain number of microseconds for the RX FIFO to be non empty
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param us the number of microseconds to wait at most (may be 0 for an instantaneous check)
 * \return true if the RX FIFO became non empty before the timeout, false otherwise
 */
bool uart_is_readable_within_us(uart_inst_t *uart, uint32_t us);

/*! \brief Return the DREQ to use for pacing transfers to/from a particular UART instance
 *  \ingroup hardware_uart
 *
 * \param uart UART instance. \ref uart0 or \ref uart1
 * \param is_tx true for sending data to the UART instance, false for receiving data from the UART instance
 */
static inline uint uart_get_dreq(uart_inst_t *uart, bool is_tx) {
    static_assert(DREQ_UART0_RX == DREQ_UART0_TX + 1, "");
    static_assert(DREQ_UART1_RX == DREQ_UART1_TX + 1, "");
    static_assert(DREQ_UART1_TX == DREQ_UART0_TX + 2, "");
    return DREQ_UART0_TX + uart_get_index(uart) * 2 + !is_tx;
}

#ifdef __cplusplus
}
#endif

#endif
