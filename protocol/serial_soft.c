/*
Copyright 2012 Jun WAKO <wakojun@gmail.com>

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "serial.h"

/*
 *  Stupid Inefficient Busy-wait Software Serial
 *  is still useful for negative logic signal like Sun protocol not supported by hardware USART.
 */

#define WAIT_US     (1000000/SERIAL_BAUD)

/* debug for signal timing, see debug pin with oscilloscope */
#ifdef SERIAL_SOFT_DEBUG
    #define SERIAL_SOFT_DEBUG_INIT()    (DDRD |= 1<<7)
    #define SERIAL_SOFT_DEBUG_TGL()     (PORTD ^= 1<<7)
#else
    #define SERIAL_SOFT_DEBUG_INIT()
    #define SERIAL_SOFT_DEBUG_TGL()
#endif


void serial_init(void)
{
    SERIAL_SOFT_DEBUG_INIT();

    SERIAL_RXD_INIT();
    SERIAL_TXD_INIT();
}

/* RX ring buffer */
#define RBUF_SIZE   8
static uint8_t rbuf[RBUF_SIZE];
static uint8_t rbuf_head = 0;
static uint8_t rbuf_tail = 0;


uint8_t serial_recv(void)
{
    uint8_t data = 0;
    if (rbuf_head == rbuf_tail) {
        return 0;
    }

    data = rbuf[rbuf_tail];
    rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    return data;
}

int16_t serial_recv2(void)
{
    uint8_t data = 0;
    if (rbuf_head == rbuf_tail) {
        return -1;
    }

    data = rbuf[rbuf_tail];
    rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    return data;
}

void serial_send(uint8_t data)
{
    /* signal state: IDLE: ON, START: OFF, STOP: ON, DATA0: OFF, DATA1: ON */
    /* start bit */
    SERIAL_TXD_OFF();
    _delay_us(WAIT_US);

#ifdef SERIAL_BIT_ORDER_MSB
    uint8_t mask = 0x80;
#else
    uint8_t mask = 0x01;
#endif
    while (mask) {
        if (data&mask) { SERIAL_TXD_ON(); } else { SERIAL_TXD_OFF(); }
        _delay_us(WAIT_US);

#ifdef SERIAL_BIT_ORDER_MSB
        mask >>= 1;
#else
        mask <<= 1;
#endif
    }

    /* stop bit */
    SERIAL_TXD_ON();
    _delay_us(WAIT_US);
}

/* detect edge of start bit */
ISR(SERIAL_RXD_VECT)
{
    SERIAL_SOFT_DEBUG_TGL()
    SERIAL_RXD_INT_ENTER()

    uint8_t data = 0;

#ifdef SERIAL_BIT_ORDER_MSB
    uint8_t mask = 0x80;
#else
    uint8_t mask = 0x01;
#endif

#ifdef SERIAL_PARITY_ODD
    uint8_t parity = 0;
#elif defined(SERIAL_PARITY_EVEN)
    uint8_t parity = 1;
#endif

    /* to center of start bit */
    _delay_us(WAIT_US/2);
    SERIAL_SOFT_DEBUG_TGL()
    do {
        /* to center of next bit */
        _delay_us(WAIT_US);

    SERIAL_SOFT_DEBUG_TGL()
        if (SERIAL_RXD_READ()) {
            data |= mask;
#if defined(SERIAL_PARITY_EVEN) || defined(SERIAL_PARITY_ODD)
            parity ^= 1;
#endif
        }
#ifdef SERIAL_BIT_ORDER_MSB
        mask >>= 1;
#else
        mask <<= 1;
#endif
    } while (mask);

#if defined(SERIAL_PARITY_EVEN) || defined(SERIAL_PARITY_ODD)
    /* to center of parity bit */
    _delay_us(WAIT_US);
    if (SERIAL_RXD_READ()) { parity ^= 1; }
    SERIAL_SOFT_DEBUG_TGL()
#endif

    /* to center of stop bit */
    _delay_us(WAIT_US);

    uint8_t next = (rbuf_head + 1) % RBUF_SIZE;
#if defined(SERIAL_PARITY_EVEN) || defined(SERIAL_PARITY_ODD)
    if (parity && next != rbuf_tail) {
#else
    if (next != rbuf_tail) {
#endif
        rbuf[rbuf_head] = data;
        rbuf_head = next;
    }

    SERIAL_RXD_INT_EXIT();
    SERIAL_SOFT_DEBUG_TGL()
}
