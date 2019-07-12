/* Copyright 2019 Michiel Visser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "hal.h"

typedef struct {
    uint8_t *buf;
    UARTDriver *uart;
    size_t size;
    volatile size_t sending_elements;
    volatile size_t head;
    volatile size_t tail;
} uart_tx_ringbuf_t;

int uart_tx_ringbuf_elements(uart_tx_ringbuf_t *ringbuf);
int uart_tx_ringbuf_space(uart_tx_ringbuf_t *ringbuf);
bool uart_tx_ringbuf_empty(uart_tx_ringbuf_t *ringbuf);
bool uart_tx_ringbuf_full(uart_tx_ringbuf_t *ringbuf);
void uart_tx_ringbuf_start_transmission(uart_tx_ringbuf_t *ringbuf);
void uart_tx_ringbuf_finish_transmission(uart_tx_ringbuf_t *ringbuf);
bool uart_tx_ringbuf_put(uart_tx_ringbuf_t *ringbuf, uint8_t c);
bool uart_tx_ringbuf_write(uart_tx_ringbuf_t *ringbuf, size_t count, void *data);
