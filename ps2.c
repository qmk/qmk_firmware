/*
Copyright (c) 2010,2011 Jun WAKO <wakojun@gmail.com>

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
#include "ps2.h"
#include "debug.h"


static uint8_t recv_data(void);
static inline void clock_lo(void);
static inline void clock_hi(void);
static inline bool clock_in(void);
static inline void data_lo(void);
static inline void data_hi(void);
static inline bool data_in(void);
static inline uint16_t wait_clock_lo(uint16_t us);
static inline uint16_t wait_clock_hi(uint16_t us);
static inline uint16_t wait_data_lo(uint16_t us);
static inline uint16_t wait_data_hi(uint16_t us);
static inline void idle(void);
static inline void inhibit(void);


/*
Primitive PS/2 Library for AVR
==============================
Host side is only supported now.


I/O control
-----------
High state is asserted by input with pull up.


PS/2 References
---------------
http://www.computer-engineering.org/ps2protocol/
http://www.mcamafia.de/pdf/ibm_hitrc07.pdf
*/


#define WAIT(stat, us, err) do { \
    if (!wait_##stat(us)) { \
        ps2_error = err; \
        goto ERROR; \
    } \
} while (0)


uint8_t ps2_error = PS2_ERR_NONE;


void ps2_host_init(void)
{
#ifdef PS2_INT_ENABLE
    PS2_INT_ENABLE();
    idle();
#else
    inhibit();
#endif
}

// TODO: send using interrupt if available
uint8_t ps2_host_send(uint8_t data)
{
    uint8_t res = 0;
    bool parity = true;
    ps2_error = PS2_ERR_NONE;
#ifdef PS2_INT_DISABLE
    PS2_INT_DISABLE();
#endif
    /* terminate a transmission if we have */
    inhibit();
    _delay_us(100);

    /* start bit [1] */
    data_lo();
    clock_hi();
    WAIT(clock_lo, 15000, 1);
    /* data [2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        _delay_us(15);
        if (data&(1<<i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_hi, 50, 2);
        WAIT(clock_lo, 50, 3);
    }
    /* parity [10] */
    _delay_us(15);
    if (parity) { data_hi(); } else { data_lo(); }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);
    /* stop bit [11] */
    _delay_us(15);
    data_hi();
    /* ack [12] */
    WAIT(data_lo, 50, 6);
    WAIT(clock_lo, 50, 7);

    /* wait for idle state */
    WAIT(clock_hi, 50, 8);
    WAIT(data_hi, 50, 9);

    res = ps2_host_recv_response();
ERROR:
#ifdef PS2_INT_ENABLE
    PS2_INT_ENABLE();
    idle();
#else
    inhibit();
#endif
    return res;
}

/* receive data when host want else inhibit communication */
uint8_t ps2_host_recv_response(void)
{
    uint8_t data = 0;

    /* terminate a transmission if we have */
    inhibit();
    _delay_us(100);

    /* release lines(idle state) */
    idle();

    /* wait start bit */
    wait_clock_lo(2000);
    data = recv_data();

    inhibit();
    return data;
}

#ifndef PS2_INT_VECT
uint8_t ps2_host_recv(void)
{
    return ps2_host_recv_response();
}
#else
/* ring buffer to store ps/2 key data */
#define PBUF_SIZE 8
static uint8_t pbuf[PBUF_SIZE];
static uint8_t pbuf_head = 0;
static uint8_t pbuf_tail = 0;
static inline void pbuf_enqueue(uint8_t data)
{
    if (!data)
        return;

    uint8_t sreg = SREG;
    cli();
    uint8_t next = (pbuf_head + 1) % PBUF_SIZE;
    if (next != pbuf_tail) {
        pbuf[pbuf_head] = data;
        pbuf_head = next;
    } else {
        debug("pbuf: full\n");
    }
    SREG = sreg;
}
static inline uint8_t pbuf_dequeue(void)
{
    uint8_t val = 0;

    uint8_t sreg = SREG;
    cli();
    if (pbuf_head != pbuf_tail) {
        val = pbuf[pbuf_tail];
        pbuf_tail = (pbuf_tail + 1) % PBUF_SIZE;
    }
    SREG = sreg;

    return val;
}

/* get data received by interrupt */
uint8_t ps2_host_recv(void)
{
    if (ps2_error) {
        print("x");
        phex(ps2_error);
        ps2_host_send(0xFE);    // request to resend
        ps2_error = PS2_ERR_NONE;
    }
    idle();
    return pbuf_dequeue();
}

#if 0
#define DEBUGP_INIT() do { DDRC = 0xFF; } while (0)
#define DEBUGP(x) do { PORTC = x; } while (0)
#else
#define DEBUGP_INIT()
#define DEBUGP(x)
#endif
ISR(PS2_INT_VECT)
{
    static enum {
        INIT,
        START,
        BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7,
        PARITY,
        STOP,
    } state = INIT;
    static uint8_t data = 0;
    static uint8_t parity = 1;

    // TODO: abort if elapse 100us from previous interrupt

    // return unless falling edge
    if (clock_in()) {
        goto RETURN;
    }

    state++;
    DEBUGP(state);
    switch (state) {
        case START:
            if (data_in())
                goto ERROR;
            break;
        case BIT0:
        case BIT1:
        case BIT2:
        case BIT3:
        case BIT4:
        case BIT5:
        case BIT6:
        case BIT7:
            data >>= 1;
            if (data_in()) {
                data |= 0x80;
                parity++;
            }
            break;
        case PARITY:
            if (data_in()) {
                if (!(parity & 0x01))
                    goto ERROR;
            } else {
                if (parity & 0x01)
                    goto ERROR;
            }
            break;
        case STOP:
            if (!data_in())
                goto ERROR;
            pbuf_enqueue(data);
            goto DONE;
            break;
        default:
            goto ERROR;
    }
    goto RETURN;
ERROR:
    DEBUGP(0x0F);
    inhibit();
    ps2_error = state;
DONE:
    state = INIT;
    data = 0;
    parity = 1;
RETURN:
    return;
}
#endif


static void ps2_reset(void)
{
    ps2_host_send(0xFF);
}

/* send LED state to keyboard */
void ps2_host_set_led(uint8_t led)
{
    ps2_host_send(0xED);
    ps2_host_send(led);
}


/* called after start bit comes */
static uint8_t recv_data(void)
{
    uint8_t data = 0;
    bool parity = true;
    ps2_error = PS2_ERR_NONE;

    /* start bit [1] */
    WAIT(clock_lo, 1, 1);
    WAIT(data_lo, 1, 2);
    WAIT(clock_hi, 50, 3);

    /* data [2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_lo, 50, 4);
        if (data_in()) {
            parity = !parity;
            data |= (1<<i);
        }
        WAIT(clock_hi, 50, 5);
    }

    /* parity [10] */
    WAIT(clock_lo, 50, 6);
    if (data_in() != parity) {
        ps2_error = PS2_ERR_PARITY;
        goto ERROR;
    }
    WAIT(clock_hi, 50, 7);

    /* stop bit [11] */
    WAIT(clock_lo, 50, 8);
    WAIT(data_hi, 1, 9);
    WAIT(clock_hi, 50, 10);

    return data;
ERROR:
    return 0;
}

static inline void clock_lo()
{
    PS2_CLOCK_PORT &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_DDR  |=  (1<<PS2_CLOCK_BIT);
}
static inline void clock_hi()
{
    /* input with pull up */
    PS2_CLOCK_DDR  &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_PORT |=  (1<<PS2_CLOCK_BIT);
}
static inline bool clock_in()
{
    PS2_CLOCK_DDR  &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_PORT |=  (1<<PS2_CLOCK_BIT);
    _delay_us(1);
    return PS2_CLOCK_PIN&(1<<PS2_CLOCK_BIT);
}
static inline void data_lo()
{
    PS2_DATA_PORT &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_DDR  |=  (1<<PS2_DATA_BIT);
}
static inline void data_hi()
{
    /* input with pull up */
    PS2_DATA_DDR  &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_PORT |=  (1<<PS2_DATA_BIT);
}
static inline bool data_in()
{
    PS2_DATA_DDR  &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_PORT |=  (1<<PS2_DATA_BIT);
    _delay_us(1);
    return PS2_DATA_PIN&(1<<PS2_DATA_BIT);
}

static inline uint16_t wait_clock_lo(uint16_t us)
{
    while (clock_in()  && us) { asm(""); _delay_us(1); us--; }
    return us;
}
static inline uint16_t wait_clock_hi(uint16_t us)
{
    while (!clock_in() && us) { asm(""); _delay_us(1); us--; }
    return us;
}
static inline uint16_t wait_data_lo(uint16_t us)
{
    while (data_in() && us)  { asm(""); _delay_us(1); us--; }
    return us;
}
static inline uint16_t wait_data_hi(uint16_t us)
{
    while (!data_in() && us)  { asm(""); _delay_us(1); us--; }
    return us;
}

/* idle state that device can send */
static inline void idle(void)
{
    clock_hi();
    data_hi();
}

/* inhibit device to send */
static inline void inhibit(void)
{
    clock_lo();
    data_hi();
}
