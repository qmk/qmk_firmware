/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "hardware/uart.h"

#if defined(__unix) || defined(__APPLE__)
#define _XOPEN_SOURCE 600 /* for ONLCR */
#define __BSD_VISIBLE 1 /* for ONLCR in *BSD */

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef FNONBLOCK
#define FNONBLOCK O_NONBLOCK
#endif

struct termios _tty;
static tcflag_t _res_oflg = 0;
static tcflag_t _res_lflg = 0;

void _resettty(void) {
    if (!isatty(STDIN_FILENO))
        return;

    /* reset tty: */
    _tty.c_oflag = _res_oflg;
    _tty.c_lflag = _res_lflg;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &_tty);
}

void _inittty(void) {
    if (!isatty(STDIN_FILENO))
        return;

    /* save tty: */
    tcgetattr(STDIN_FILENO, &_tty);
    _res_oflg = _tty.c_oflag;
    _res_lflg = _tty.c_lflag;

    /* set raw: */
    _tty.c_lflag &= ~(ICANON | ICRNL);// | ISIG);
    //_tty.c_oflag &= ~ONLCR;
    tcsetattr(STDIN_FILENO, TCSANOW, &_tty);

    fcntl(STDIN_FILENO, F_SETFL, FNONBLOCK);
    atexit(_resettty);
}

#else
void _inittty() {}
#endif

typedef struct {
    bool dummy;
} uart_hw_t;

uart_inst_t *const uart0;
uart_inst_t *const uart1;

static int _nextchar = EOF;

static bool _peekchar() {
    if (_nextchar == EOF) {
        _nextchar = getchar();
    }
    return _nextchar != EOF;
}

uint uart_init(uart_inst_t *uart, uint baud_rate) {
    _inittty();
    return baud_rate;
}

size_t uart_is_writable(uart_inst_t *uart) {
    return 1;
}

// If returns 0, no data is available to be read from UART.
// If returns nonzero, at least that many bytes can be written without blocking.
size_t uart_is_readable(uart_inst_t *uart) {
    return _peekchar() ? 1 : 0;
}

// Write len bytes directly from src to the UART
void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        uart_putc(uart, src[i]);
    }
}

// Read len bytes directly from the UART to dst
void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len) {
    for (size_t i = 0; i < len; i++) {
        dst[i] = uart_getc(uart);
    }
}

// ----------------------------------------------------------------------------
// UART-specific operations and aliases

void uart_putc(uart_inst_t *uart, char c) {
    putchar(c);
}

void uart_puts(uart_inst_t *uart, const char *s) {
    puts(s);
}

char uart_getc(uart_inst_t *uart) {
    while (!_peekchar()) {
        tight_loop_contents();
    }
    char rc = (char) _nextchar;
    _nextchar = EOF;
    return rc;
}

void uart_default_tx_wait_blocking() {

}
