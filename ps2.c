/*
Copyright (c) 2010 Jun WAKO <wakojun@gmail.com>

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
#include <util/delay.h>
#include "ps2.h"
#include "print.h"
#include "debug.h"


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

#define WAIT_NORETRY(stat, us, err) do { \
    if (!wait_##stat(us)) { \
        ps2_error = err; \
        return 0; \
    } \
} while (0)


uint8_t ps2_error = PS2_ERR_NONE;


void ps2_host_init(void)
{
    /* inhibit */
    clock_lo();
    data_hi();
}

uint8_t ps2_host_send(uint8_t data)
{
    bool parity = true;
    ps2_error = 0;

    /* request to send */
    clock_lo();
    _delay_us(100);
    /* start bit [1] */
    data_lo();
    clock_hi();
    WAIT(clock_lo, 15000, 1);
    /* data [2-9] */
    for (uint8_t i = 0; i < 8; i++) {
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
    if (parity) { data_hi(); } else { data_lo(); }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);
    /* stop bit [11] */
    data_hi();
    /* ack [12] */
    WAIT(data_lo, 50, 6);
    WAIT(clock_lo, 50, 7);
    WAIT(clock_hi, 50, 8);
    WAIT(data_hi, 50, 9);

    /* inhibit device to send */
    clock_lo();

    return 1;
ERROR:
    /* inhibit device to send */
    data_hi();
    clock_lo();
    return 0;
}

uint8_t ps2_host_recv(void)
{
    uint8_t data = 0;
    bool parity = true;
    ps2_error = 0;

    /* cancel to sync */
    clock_lo();
    _delay_us(100);

    /* release lines(idle state) */
    clock_hi();
    data_hi();

    /* start bit [1] */
    WAIT(clock_lo, 20000, 1);
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

    /* inhibit device to send */
    clock_lo();

    return data;
ERROR:
    /* inhibit device to send */
    data_hi();
    clock_lo();
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
