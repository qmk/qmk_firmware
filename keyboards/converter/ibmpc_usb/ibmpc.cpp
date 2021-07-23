/*
Copyright 2010,2011,2012,2013,2019 Jun WAKO <wakojun@gmail.com>

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

/*
 * IBM PC keyboard protocol
 */

#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "debug.h"
#include "timer.h"
#include "wait.h"
#include "ibmpc.hpp"


#define WAIT(stat, us, err) do { \
    if (!wait_##stat(us)) { \
        error = err; \
        goto ERROR; \
    } \
} while (0)


IBMPC IBMPC::interface0 = IBMPC(IBMPC_CLOCK_BIT, IBMPC_DATA_BIT);
#if defined(IBMPC_CLOCK_BIT1) && defined(IBMPC_DATA_BIT1)
IBMPC IBMPC::interface1 = IBMPC(IBMPC_CLOCK_BIT1, IBMPC_DATA_BIT1);
#endif


void IBMPC::host_init(void)
{
    // initialize reset pin to HiZ
    IBMPC_RST_HIZ();
    inhibit();
    int_init();
    int_off();
    host_isr_clear();
}

void IBMPC::host_enable(void)
{
    int_on();
    idle();
}

void IBMPC::host_disable(void)
{
    int_off();
    inhibit();
}

int16_t IBMPC::host_send(uint8_t data)
{
    bool parity = true;
    error = IBMPC_ERR_NONE;
    uint8_t retry = 0;

    dprintf("w%02X ", data);

    // Not receiving data
    if (isr_state != 0x8000) dprintf("isr:%04X ", isr_state);
    while (isr_state != 0x8000) ;

    // Not clock Lo
    if (!clock_in()) dprintf("c:%u ", wait_clock_hi(1000));

    // Not data Lo
    if (!data_in()) dprintf("d:%u ", wait_data_hi(1000));

    int_off();

RETRY:
    /* terminate a transmission if we have */
    inhibit();
    wait_us(200);    // [5]p.54

    /* 'Request to Send' and Start bit */
    data_lo();
    wait_us(200);
    clock_hi();     // [5]p.54 [clock low]>100us [5]p.50
    WAIT(clock_lo, 10000, 1);   // [5]p.53, -10ms [5]p.50

    /* Data bit[2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        wait_us(15);
        if (data&(1<<i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_hi, 50, 2);
        WAIT(clock_lo, 50, 3);
    }

    /* Parity bit */
    wait_us(15);
    if (parity) { data_hi(); } else { data_lo(); }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);

    /* Stop bit */
    wait_us(15);
    data_hi();

    /* Ack */
    WAIT(data_lo, 300, 6);
    WAIT(data_hi, 300, 7);
    WAIT(clock_hi, 300, 8);

    // clear buffer to get response correctly
    host_isr_clear();

    idle();
    int_on();
    return host_recv_response();
ERROR:
    // Retry for Z-150 AT start bit error
    if (error == 1 && retry++ < 10) {
        error = IBMPC_ERR_NONE;
        dprintf("R ");
        goto RETRY;
    }

    error |= IBMPC_ERR_SEND;
    inhibit();
    wait_ms(2);
    idle();
    int_on();
    return -1;
}

/*
 * Receive data from keyboard
 */
int16_t IBMPC::host_recv(void)
{
    int16_t ret = -1;

    // Enable ISR if buffer was full
    if (ringbuf_is_full()) {
        host_isr_clear();
        int_on();
        idle();
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ret = ringbuf_get();
    }
    if (ret != -1) dprintf("r%02X ", ret&0xFF);
    return ret;
}

int16_t IBMPC::host_recv_response(void)
{
    // Command may take 25ms/20ms at most([5]p.46, [3]p.21)
    uint8_t retry = 25;
    int16_t data = -1;
    while (retry-- && (data = host_recv()) == -1) {
        wait_ms(1);
    }
    return data;
}

void IBMPC::host_isr_clear(void)
{
    isr_debug = 0;
    protocol = 0;
    error = 0;
    isr_state = 0x8000;
    ringbuf_reset();
}

inline void IBMPC::isr(void)
{
    uint8_t dbit;
    dbit = IBMPC_DATA_PIN&(1<<data_bit);

    // Timeout check
    uint8_t t;
    // use only the least byte of millisecond timer
    asm("lds %0, %1" : "=r" (t) : "p" (&timer_count));
    //t = (uint8_t)timer_count;    // compiler uses four registers instead of one
    if (isr_state == 0x8000) {
        timer_start = t;
    } else {
        // This gives 2.0ms at least before timeout
        if ((uint8_t)(t - timer_start) >= 3) {
            isr_debug = isr_state;
            error = IBMPC_ERR_TIMEOUT;
            goto ERROR;

            // timeout error recovery - start receiving new data
            // it seems to work somehow but may not under unstable situation
            //timer_start = t;
            //isr_state = 0x8000;
        }
    }

    isr_state = isr_state>>1;
    if (dbit) isr_state |= 0x8000;

    // isr_state: state of receiving data from keyboard
    //
    // This should be initialized with 0x8000 before receiving data and
    // the MSB '*1' works as marker to discrimitate between protocols.
    // It stores sampled bit at MSB after right shift on each clock falling edge.
    //
    // XT protocol has two variants of signaling; XT_IBM and XT_Clone.
    // XT_IBM uses two start bits 0 and 1 while XT_Clone uses just start bit 1.
    // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol
    //
    //      15 14 13 12   11 10  9  8    7  6  5  4    3  2  1  0
    //      -----------------------------------------------------
    //      *1  0  0  0    0  0  0  0 |  0  0  0  0    0  0  0  0     Initial state(0x8000)
    //
    //       x  x  x  x    x  x  x  x |  0  0  0  0    0  0  0  0     midway(0-7 bits received)
    //       x  x  x  x    x  x  x  x | *1  0  0  0    0  0  0  0     midway(8 bits received)
    //      b6 b5 b4 b3   b2 b1 b0  1 |  0 *1  0  0    0  0  0  0     XT_IBM-midway ^1
    //      b7 b6 b5 b4   b3 b2 b1 b0 |  0 *1  0  0    0  0  0  0     AT-midway ^1
    //      b7 b6 b5 b4   b3 b2 b1 b0 |  1 *1  0  0    0  0  0  0     XT_Clone-done ^3
    //      b6 b5 b4 b3   b2 b1 b0  1 |  1 *1  0  0    0  0  0  0     XT_IBM-error ^3
    //      pr b7 b6 b5   b4 b3 b2 b1 |  0  0 *1  0    0  0  0  0     AT-midway[b0=0]
    //      b7 b6 b5 b4   b3 b2 b1 b0 |  1  0 *1  0    0  0  0  0     XT_IBM-done ^2
    //      pr b7 b6 b5   b4 b3 b2 b1 |  1  0 *1  0    0  0  0  0     AT-midway[b0=1] ^2
    //      b7 b6 b5 b4   b3 b2 b1 b0 |  1  1 *1  0    0  0  0  0     XT_IBM-error-done
    //       x  x  x  x    x  x  x  x |  0  1 *1  0    0  0  0  0     illegal
    //      st pr b7 b6   b5 b4 b3 b2 | b1 b0  0 *1    0  0  0  0     AT-done
    //       x  x  x  x    x  x  x  x |  x  x  1 *1    0  0  0  0     illegal
    //                                all other states than above     illegal
    //
    // ^1: AT and XT_IBM takes same state.
    // ^2: AT and XT_IBM takes same state in case that AT b0 is 1,
    // we have to check AT stop bit to discriminate between the two protocol.
    switch (isr_state & 0xFF) {
        case 0b00000000:
        case 0b10000000:
        case 0b01000000:    // ^1
        case 0b00100000:
            // midway
            goto NEXT;
            break;
        case 0b11000000:    // ^3
            {
                uint8_t us = 100;
                // wait for rising and falling edge of b7 of XT_IBM
                if (!protocol) {
                    while (!(IBMPC_CLOCK_PIN & clock_mask) && us) { wait_us(1); us--; }
                    while ( (IBMPC_CLOCK_PIN & clock_mask) && us) { wait_us(1); us--; }
                } else if (protocol == IBMPC_PROTOCOL_XT_CLONE) {
                    us = 0;
                }

                if (us) {
                    // XT_IBM-error: read start(0) as 1
                    goto NEXT;
                } else {
                    // XT_Clone-done
                    isr_debug = isr_state;
                    isr_state = isr_state>>8;
                    protocol = IBMPC_PROTOCOL_XT_CLONE;
                    goto DONE;
                }
            }
            break;
        case 0b11100000:
            // XT_IBM-error-done
            isr_debug = isr_state;
            isr_state = isr_state>>8;
            protocol = IBMPC_PROTOCOL_XT_ERROR;
            goto DONE;
            break;
        case 0b10100000:    // ^2
            {
                uint8_t us = 100;
                // wait for rising and falling edge of AT stop bit to discriminate between XT and AT
                if (!protocol) {
                    while (!(IBMPC_CLOCK_PIN & clock_mask) && us) { wait_us(1); us--; }
                    while ( (IBMPC_CLOCK_PIN & clock_mask) && us) { wait_us(1); us--; }
                } else if (protocol == IBMPC_PROTOCOL_XT_IBM) {
                    us = 0;
                }

                if (us) {
                    // found stop bit: AT-midway - process the stop bit in next ISR
                    goto NEXT;
                } else {
                    // no stop bit: XT_IBM-done
                    isr_debug = isr_state;
                    isr_state = isr_state>>8;
                    protocol = IBMPC_PROTOCOL_XT_IBM;
                    goto DONE;
                }
             }
            break;
        case 0b00010000:
        case 0b10010000:
        case 0b01010000:
        case 0b11010000:
            // AT-done
            // TODO: parity check?
            isr_debug = isr_state;
            // stop bit check
            if (isr_state & 0x8000) {
                protocol = IBMPC_PROTOCOL_AT;
            } else {
                // Zenith Z-150 AT(beige/white lable) asserts stop bit as low
                // https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-AT-Keyboard-Protocol#zenith-z-150-beige
                protocol = IBMPC_PROTOCOL_AT_Z150;
            }
            isr_state = isr_state>>6;
            goto DONE;
            break;
        case 0b01100000:
        case 0b00110000:
        case 0b10110000:
        case 0b01110000:
        case 0b11110000:
        default:            // xxxx_oooo(any 1 in low nibble)
            // Illegal
            protocol = 0;
            isr_debug = isr_state;
            error = IBMPC_ERR_ILLEGAL;
            goto ERROR;
            break;
    }

DONE:
    // store data
    ringbuf_put(isr_state & 0xFF);
    if (ringbuf_is_full()) {
        // Disable ISR if buffer is full
        int_off();
        // inhibit: clock_lo() instead of inhibit() for ISR optimization
        clock_lo();
    }
    if (ringbuf_is_empty()) {
        // buffer overflow
        error = IBMPC_ERR_FULL;
    }
ERROR:
    // clear for next data
    isr_state = 0x8000;
NEXT:
    return;
}

/* send LED state to keyboard */
void IBMPC::host_set_led(uint8_t led)
{
    if (0xFA == host_send(0xED)) {
        host_send(led);
    }
}


// NOTE: With this ISR data line should be read within 5us after clock falling edge.
// Confirmed that ATmega32u4 can read data line in 2.5us from interrupt after
// ISR prologue pushs r18, r19, r20, r21, r24, r25 r30 and r31 with GCC 5.4.0
ISR(IBMPC_INT_VECT)
{
    IBMPC::interface0.isr();
}

#if defined(IBMPC_CLOCK_BIT1) && defined(IBMPC_DATA_BIT1) && defined(IBMPC_INT_VECT1)
ISR(IBMPC_INT_VECT1)
{
    IBMPC::interface1.isr();
}
#endif
