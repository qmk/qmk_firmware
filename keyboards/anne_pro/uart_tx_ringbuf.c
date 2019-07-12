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

#include "uart_tx_ringbuf.h"
#include "hal.h"

int uart_tx_ringbuf_elements(uart_tx_ringbuf_t *ringbuf) {
    return ringbuf->head - ringbuf->tail;
}

int uart_tx_ringbuf_space(uart_tx_ringbuf_t *ringbuf) {
    return ringbuf->size - uart_tx_ringbuf_elements(ringbuf);
}

bool uart_tx_ringbuf_empty(uart_tx_ringbuf_t *ringbuf) {
    return uart_tx_ringbuf_elements(ringbuf) == 0;
}

bool uart_tx_ringbuf_full(uart_tx_ringbuf_t *ringbuf) {
    return uart_tx_ringbuf_elements(ringbuf) == ringbuf->size;
}

void uart_tx_ringbuf_start_transmission(uart_tx_ringbuf_t *ringbuf) {
    /* Do not start transmission when one is already in progress */
    if (ringbuf->sending_elements != 0) return;

    size_t elements = uart_tx_ringbuf_elements(ringbuf);
    /* Do not start transmission when ringbuffer is empty */
    if (elements == 0) return;

    /* Get the offset of the first and last item */
    size_t first_offset = (ringbuf->tail & (ringbuf->size - 1));

    /* Determine if this wraps around the end of the buffer */
    if (first_offset + elements >= ringbuf->size) {
        /* If so only send until the end of the buffer */
        elements = ringbuf->size - first_offset;
    }

    /* Send the selected elements */
    ringbuf->sending_elements = elements;
    uartStartSend(ringbuf->uart, elements, ringbuf->buf + first_offset);
}

void uart_tx_ringbuf_finish_transmission(uart_tx_ringbuf_t *ringbuf) {
    /* Update the tail of the ringbuffer */
    ringbuf->tail += ringbuf->sending_elements;
    /* Clear the sending elements */
    ringbuf->sending_elements = 0;
}

bool uart_tx_ringbuf_put(uart_tx_ringbuf_t *ringbuf, uint8_t c) {
    /* If the ringbuffer is full, ignore the request */
    if (uart_tx_ringbuf_full(ringbuf)) return false;

    /* Put the character into the ringbuffer */
    size_t head_offset = (ringbuf->head & (ringbuf->size - 1));
    ringbuf->buf[head_offset] = c;
    ringbuf->head++;

    return true;
}

bool uart_tx_ringbuf_write(uart_tx_ringbuf_t *ringbuf, size_t count, void *data) {
    /* If there is not enough space, ignore the request */
    if (uart_tx_ringbuf_space(ringbuf) < count) return false;

    for (int i = 0; i < count; i++) {
        /* Put the character into the ringbuffer */
        size_t head_offset = (ringbuf->head & (ringbuf->size - 1));
        ringbuf->buf[head_offset] = ((uint8_t *) data)[i];
        ringbuf->head++;
    }

    return true;
}
