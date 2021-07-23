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

#ifndef IBMPC_HPP
#define IBMPC_HPP

#include <stdbool.h>
#include "wait.h"

/*
 * IBM PC keyboard protocol
 *
 * PS/2 Resources
 * --------------
 * [1] The PS/2 Mouse/Keyboard Protocol
 * http://www.computer-engineering.org/ps2protocol/
 * Concise and thorough primer of PS/2 protocol.
 *
 * [2] Keyboard and Auxiliary Device Controller
 * http://www.mcamafia.de/pdf/ibm_hitrc07.pdf
 * Signal Timing and Format
 *
 * [3] Keyboards(101- and 102-key)
 * http://www.mcamafia.de/pdf/ibm_hitrc11.pdf
 * Keyboard Layout, Scan Code Set, POR, and Commands.
 *
 * [4] PS/2 Reference Manuals
 * http://www.mcamafia.de/pdf/ibm_hitrc07.pdf
 * Collection of IBM Personal System/2 documents.
 *
 * [5] TrackPoint Engineering Specifications for version 3E
 * https://web.archive.org/web/20100526161812/http://wwwcssrv.almaden.ibm.com/trackpoint/download.html
 */
#define IBMPC_ACK         0xFA
#define IBMPC_RESEND      0xFE
#define IBMPC_SET_LED     0xED

#define IBMPC_PROTOCOL_NO       0
#define IBMPC_PROTOCOL_AT       0x10
#define IBMPC_PROTOCOL_AT_Z150  0x11
#define IBMPC_PROTOCOL_XT       0x20
#define IBMPC_PROTOCOL_XT_IBM   0x21
#define IBMPC_PROTOCOL_XT_CLONE 0x22
#define IBMPC_PROTOCOL_XT_ERROR 0x23

// Error numbers
#define IBMPC_ERR_NONE        0
#define IBMPC_ERR_RECV        0x00
#define IBMPC_ERR_SEND        0x10
#define IBMPC_ERR_TIMEOUT     0x20
#define IBMPC_ERR_FULL        0x40
#define IBMPC_ERR_ILLEGAL     0x80
#define IBMPC_ERR_FF          0xF0

#define IBMPC_LED_SCROLL_LOCK 0
#define IBMPC_LED_NUM_LOCK    1
#define IBMPC_LED_CAPS_LOCK   2


class IBMPC
{
    public:
    static IBMPC interface0;
#if defined(IBMPC_CLOCK_BIT1) && defined(IBMPC_DATA_BIT1)
    static IBMPC interface1;
#endif

    volatile uint16_t isr_debug;
    volatile uint8_t protocol;
    volatile uint8_t error;

    void host_init(void);
    void host_enable(void);
    void host_disable(void);
    int16_t host_send(uint8_t data);
    int16_t host_recv_response(void);
    int16_t host_recv(void);
    void host_isr_clear(void);
    void host_set_led(uint8_t led);

    IBMPC(uint8_t clock, uint8_t data) :
            isr_debug(IBMPC_ERR_NONE), protocol(IBMPC_PROTOCOL_NO), error(IBMPC_ERR_NONE),
            isr_state(0x8000), timer_start(0), clock_bit(clock), data_bit(data),
            clock_mask(1 << clock), data_mask(1 << data) {
    };

    inline void isr(void) __attribute__((__always_inline__));


    private:
    volatile uint16_t isr_state;
    uint8_t timer_start;

    /* ring buffer */
    // Size should be power of 2
    #define RINGBUF_SIZE    16
    uint8_t rb_head;
    uint8_t rb_tail;
    uint8_t rb_buffer[RINGBUF_SIZE];

    const uint8_t clock_bit, data_bit;
    const uint8_t clock_mask, data_mask;


    inline void clock_lo(void) __attribute__((__always_inline__)) // needed for ISR optimization
    {
        IBMPC_CLOCK_PORT &= ~clock_mask;
        IBMPC_CLOCK_DDR  |=  clock_mask;
    }

    inline void clock_hi(void)
    {
        /* input with pull up */
        IBMPC_CLOCK_DDR  &= ~clock_mask;
        IBMPC_CLOCK_PORT |=  clock_mask;
    }

    inline bool clock_in(void)
    {
        IBMPC_CLOCK_DDR  &= ~clock_mask;
        IBMPC_CLOCK_PORT |=  clock_mask;
        wait_us(1);
        return IBMPC_CLOCK_PIN & clock_mask;
    }

    inline void data_lo(void)
    {
        IBMPC_DATA_PORT &= ~data_mask;
        IBMPC_DATA_DDR  |=  data_mask;
    }

    inline void data_hi(void)
    {
        /* input with pull up */
        IBMPC_DATA_DDR  &= ~data_mask;
        IBMPC_DATA_PORT |=  data_mask;
    }

    inline bool data_in(void)
    {
        IBMPC_DATA_DDR  &= ~data_mask;
        IBMPC_DATA_PORT |=  data_mask;
        wait_us(1);
        return IBMPC_DATA_PIN & data_mask;
    }

    inline uint16_t wait_clock_lo(uint16_t us)
    {
        while (clock_in()  && us) { asm(""); wait_us(1); us--; }
        return us;
    }
    inline uint16_t wait_clock_hi(uint16_t us)
    {
        while (!clock_in() && us) { asm(""); wait_us(1); us--; }
        return us;
    }
    inline uint16_t wait_data_lo(uint16_t us)
    {
        while (data_in() && us)  { asm(""); wait_us(1); us--; }
        return us;
    }
    inline uint16_t wait_data_hi(uint16_t us)
    {
        while (!data_in() && us)  { asm(""); wait_us(1); us--; }
        return us;
    }

    /* idle state that device can send */
    inline void idle(void)
    {
        clock_hi();
        data_hi();
    }

    /* inhibit device to send(AT), soft reset(XT) */
    inline void inhibit(void)
    {
        clock_lo();
        data_hi();
    }

    /* inhibit device to send(XT) */
    inline void inhibit_xt(void)
    {
        clock_hi();
        data_lo();
    }

    void int_init(void)
    {
        // interrupt at falling edge
        if (clock_bit < 4) {
            EICRA |= (0x2 << ((clock_bit&0x3)*2));
        } else {
            EICRB |= (0x2 << ((clock_bit&0x3)*2));
        }
    }

    void int_on(void)
    {
        EIFR  |= clock_mask;
        EIMSK |= clock_mask;
    }

    inline void int_off(void) __attribute__((__always_inline__)) // needed for ISR optimization
    {
        EIMSK &= ~clock_mask;
    }

    /*
     * ring buffer
     */
    inline int16_t ringbuf_get(void) __attribute__((__always_inline__))
    {
        if (ringbuf_is_empty()) return -1;
        uint8_t data = rb_buffer[rb_tail];
        rb_tail++;
        rb_tail &= (RINGBUF_SIZE - 1);
        return  data;
    }
    inline void ringbuf_put(uint8_t data) __attribute__((__always_inline__))
    {
        rb_buffer[rb_head] = data;
        rb_head++;
        rb_head &= (RINGBUF_SIZE - 1);
    }
    inline bool ringbuf_is_empty(void) __attribute__((__always_inline__))
    {
        return (rb_head == rb_tail);
    }
    inline bool ringbuf_is_full(void) __attribute__((__always_inline__))
    {
        return (((rb_head + 1) & (RINGBUF_SIZE - 1)) == rb_tail);
    }
    inline void ringbuf_reset(void) __attribute__((__always_inline__))
    {
        rb_head = 0;
        rb_tail = 0;
    }
};

#endif
