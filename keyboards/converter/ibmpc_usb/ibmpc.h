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

#ifndef IBMPC_H
#define IBMPC_H

#include <stdbool.h>
#include "wait.h"
#include "print.h"

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


extern volatile uint16_t ibmpc_isr_debug;
extern volatile uint8_t ibmpc_protocol;
extern volatile uint8_t ibmpc_error;

void ibmpc_host_init(void);
void ibmpc_host_enable(void);
void ibmpc_host_disable(void);
int16_t ibmpc_host_send(uint8_t data);
int16_t ibmpc_host_recv_response(void);
int16_t ibmpc_host_recv(void);
void ibmpc_host_isr_clear(void);
void ibmpc_host_set_led(uint8_t usb_led);


/*--------------------------------------------------------------------
 * static functions
 *------------------------------------------------------------------*/
#if defined(__AVR__)
/*
 * Clock
 */
static inline void clock_lo(void)
{
    IBMPC_CLOCK_PORT &= ~(1<<IBMPC_CLOCK_BIT);
    IBMPC_CLOCK_DDR  |=  (1<<IBMPC_CLOCK_BIT);
}

static inline void clock_hi(void)
{
    /* input with pull up */
    IBMPC_CLOCK_DDR  &= ~(1<<IBMPC_CLOCK_BIT);
    IBMPC_CLOCK_PORT |=  (1<<IBMPC_CLOCK_BIT);
}

static inline bool clock_in(void)
{
    IBMPC_CLOCK_DDR  &= ~(1<<IBMPC_CLOCK_BIT);
    IBMPC_CLOCK_PORT |=  (1<<IBMPC_CLOCK_BIT);
    wait_us(1);
    return IBMPC_CLOCK_PIN&(1<<IBMPC_CLOCK_BIT);
}

/*
 * Data
 */
static inline void data_lo(void)
{
    IBMPC_DATA_PORT &= ~(1<<IBMPC_DATA_BIT);
    IBMPC_DATA_DDR  |=  (1<<IBMPC_DATA_BIT);
}

static inline void data_hi(void)
{
    /* input with pull up */
    IBMPC_DATA_DDR  &= ~(1<<IBMPC_DATA_BIT);
    IBMPC_DATA_PORT |=  (1<<IBMPC_DATA_BIT);
}

static inline bool data_in(void)
{
    IBMPC_DATA_DDR  &= ~(1<<IBMPC_DATA_BIT);
    IBMPC_DATA_PORT |=  (1<<IBMPC_DATA_BIT);
    wait_us(1);
    return IBMPC_DATA_PIN&(1<<IBMPC_DATA_BIT);
}
#endif


static inline uint16_t wait_clock_lo(uint16_t us)
{
    while (clock_in()  && us) { asm(""); wait_us(1); us--; }
    return us;
}
static inline uint16_t wait_clock_hi(uint16_t us)
{
    while (!clock_in() && us) { asm(""); wait_us(1); us--; }
    return us;
}
static inline uint16_t wait_data_lo(uint16_t us)
{
    while (data_in() && us)  { asm(""); wait_us(1); us--; }
    return us;
}
static inline uint16_t wait_data_hi(uint16_t us)
{
    while (!data_in() && us)  { asm(""); wait_us(1); us--; }
    return us;
}

/* idle state that device can send */
static inline void idle(void)
{
    clock_hi();
    data_hi();
}

/* inhibit device to send(AT), soft reset(XT) */
static inline void inhibit(void)
{
    clock_lo();
    data_hi();
}

/* inhibit device to send(XT) */
static inline void inhibit_xt(void)
{
    clock_hi();
    data_lo();
}
#endif
