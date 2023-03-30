/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/uart.h"

#include "hardware/structs/uart.h"
#include "hardware/resets.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#include "pico/assert.h"
#include "pico.h"

check_hw_layout(uart_hw_t, fr, UART_UARTFR_OFFSET);
check_hw_layout(uart_hw_t, dmacr, UART_UARTDMACR_OFFSET);

#if PICO_UART_ENABLE_CRLF_SUPPORT
short uart_char_to_line_feed[NUM_UARTS];
#endif

/// \tag::uart_reset[]
static inline void uart_reset(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    reset_block(uart_get_index(uart) ? RESETS_RESET_UART1_BITS : RESETS_RESET_UART0_BITS);
}

static inline void uart_unreset(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    unreset_block_wait(uart_get_index(uart) ? RESETS_RESET_UART1_BITS : RESETS_RESET_UART0_BITS);
}
/// \end::uart_reset[]

/// \tag::uart_init[]
uint uart_init(uart_inst_t *uart, uint baudrate) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);

    if (clock_get_hz(clk_peri) == 0)
        return 0;

    uart_reset(uart);
    uart_unreset(uart);

#if PICO_UART_ENABLE_CRLF_SUPPORT
    uart_set_translate_crlf(uart, PICO_UART_DEFAULT_CRLF);
#endif

    // Any LCR writes need to take place before enabling the UART
    uint baud = uart_set_baudrate(uart, baudrate);
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);

    // Enable the UART, both TX and RX
    uart_get_hw(uart)->cr = UART_UARTCR_UARTEN_BITS | UART_UARTCR_TXE_BITS | UART_UARTCR_RXE_BITS;
    // Enable FIFOs
    hw_set_bits(&uart_get_hw(uart)->lcr_h, UART_UARTLCR_H_FEN_BITS);
    // Always enable DREQ signals -- no harm in this if DMA is not listening
    uart_get_hw(uart)->dmacr = UART_UARTDMACR_TXDMAE_BITS | UART_UARTDMACR_RXDMAE_BITS;

    return baud;
}
/// \end::uart_init[]

void uart_deinit(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    uart_reset(uart);
}

/// \tag::uart_set_baudrate[]
uint uart_set_baudrate(uart_inst_t *uart, uint baudrate) {
    invalid_params_if(UART, baudrate == 0);
    uint32_t baud_rate_div = (8 * clock_get_hz(clk_peri) / baudrate);
    uint32_t baud_ibrd = baud_rate_div >> 7;
    uint32_t baud_fbrd;

    if (baud_ibrd == 0) {
        baud_ibrd = 1;
        baud_fbrd = 0;
    } else if (baud_ibrd >= 65535) {
        baud_ibrd = 65535;
        baud_fbrd = 0;
    }  else {
        baud_fbrd = ((baud_rate_div & 0x7f) + 1) / 2;
    }

    // Load PL011's baud divisor registers
    uart_get_hw(uart)->ibrd = baud_ibrd;
    uart_get_hw(uart)->fbrd = baud_fbrd;

    // PL011 needs a (dummy) line control register write to latch in the
    // divisors. We don't want to actually change LCR contents here.
    hw_set_bits(&uart_get_hw(uart)->lcr_h, 0);

    // See datasheet
    return (4 * clock_get_hz(clk_peri)) / (64 * baud_ibrd + baud_fbrd);
}
/// \end::uart_set_baudrate[]

void uart_set_translate_crlf(uart_inst_t *uart, bool crlf) {
#if PICO_UART_ENABLE_CRLF_SUPPORT
    uart_char_to_line_feed[uart_get_index(uart)] = crlf ? '\n' : 0x100;
#else
    panic_unsupported();
#endif
}

bool uart_is_readable_within_us(uart_inst_t *uart, uint32_t us) {
    uint32_t t = time_us_32();
    do {
        if (uart_is_readable(uart)) return true;
    } while ((time_us_32() - t) <= us);
    return false;
}
