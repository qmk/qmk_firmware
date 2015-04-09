/*
Copyright 2013 Jun WAKO <wakojun@gmail.com>

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
#include "serial.h"


#if defined(SERIAL_UART_RTS_LO) && defined(SERIAL_UART_RTS_HI)
    // Buffer state
    //   Empty:           RBUF_SPACE == RBUF_SIZE(head==tail)
    //   Last 1 space:    RBUF_SPACE == 2
    //   Full:            RBUF_SPACE == 1(last cell of rbuf be never used.)
    #define RBUF_SPACE()   (rbuf_head < rbuf_tail ?  (rbuf_tail - rbuf_head) : (RBUF_SIZE - rbuf_head + rbuf_tail))
    // allow to send
    #define rbuf_check_rts_lo() do { if (RBUF_SPACE() > 2) SERIAL_UART_RTS_LO(); } while (0)
    // prohibit to send
    #define rbuf_check_rts_hi() do { if (RBUF_SPACE() <= 2) SERIAL_UART_RTS_HI(); } while (0)
#else
    #define rbuf_check_rts_lo()
    #define rbuf_check_rts_hi()
#endif


void serial_init(void)
{
    SERIAL_UART_INIT();
}

// RX ring buffer
#define RBUF_SIZE   256
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
    rbuf_check_rts_lo();
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
    rbuf_check_rts_lo();
    return data;
}

void serial_send(uint8_t data)
{
    while (!SERIAL_UART_TXD_READY) ;
    SERIAL_UART_DATA = data;
}

// USART RX complete interrupt
ISR(SERIAL_UART_RXD_VECT)
{
    uint8_t next = (rbuf_head + 1) % RBUF_SIZE;
    if (next != rbuf_tail) {
        rbuf[rbuf_head] = SERIAL_UART_DATA;
        rbuf_head = next;
    }
    rbuf_check_rts_hi();
}
