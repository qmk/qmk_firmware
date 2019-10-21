/*
Copyright 2010,2011,2012,2013 Jun WAKO <wakojun@gmail.com>

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
 * PS/2 protocol Pin interrupt version
 */

#include <stdbool.h>

#if defined(__AVR__)
#include <avr/interrupt.h>
#include <util/delay.h>
#elif defined(PROTOCOL_CHIBIOS) //TODO: or STM32 ?
// chibiOS headers
#include "ch.h"
#include "hal.h"
#endif

#include "ps2.h"
#include "ps2_io.h"
#include "print.h"

#define WAIT(stat, us, err)     \
    do {                        \
        if (!wait_##stat(us)) { \
            ps2_error = err;    \
            goto ERROR;         \
        }                       \
    } while (0)

uint8_t ps2_error = PS2_ERR_NONE;

static inline uint8_t pbuf_dequeue(void);
static inline void    pbuf_enqueue(uint8_t data);
static inline bool    pbuf_has_data(void);
static inline void    pbuf_clear(void);

#if defined(PROTOCOL_CHIBIOS)
//------------------------------------------------
// LEGACY EXT driver, for external interrupts
// (with newer chibios we could use palLineEnableEvent and so forth...)
// see: http://www.chibios.com/forum/viewtopic.php?t=3355#p25518 https://www.playembedded.org/blog/buttons-stm32/ 3.2.3 event/callback
//
void ps2_interrupt_service_routine(void);
void extcb(EXTDriver *extp, expchannel_t channel) {
    ps2_interrupt_service_routine();
}

/*
  16 slots, one for each pin...
  currently configured to listen on external changes on pad A8
 */
static EXTConfig extcfg = {
    {
        {EXT_CH_MODE_DISABLED, NULL}, //0
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL}, //5
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL}, //10
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL},
        {EXT_CH_MODE_DISABLED, NULL}
    }
};
#define ExtModePort(pin) (((uint32_t)PAL_PORT(pin) & 0x0000FF00U) >> 6)
static EXTChannelConfig ext_clock_channel_config = {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | ExtModePort(PS2_CLOCK) , extcb};
#define PS2_INT_INIT() { \
        extStart(&EXTD1, &extcfg); /*activate config, to be able to select the appropriate channel */ \
        extSetChannelModeI(&EXTD1, PAL_PAD(PS2_CLOCK), &ext_clock_channel_config); \
    } while(0)
#define PS2_INT_ON() { \
        extStart(&EXTD1, &extcfg);              \
    } while(0)
#define PS2_INT_OFF() { \
        extStop(&EXTD1);                        \
    } while(0)
#endif




void ps2_host_init(void) {
    idle();
    PS2_INT_INIT();
    PS2_INT_ON();
    // POR(150-2000ms) plus BAT(300-500ms) may take 2.5sec([3]p.20)
    //wait_ms(2500);
}

uint8_t ps2_host_send(uint8_t data) {
    bool parity = true;
    ps2_error   = PS2_ERR_NONE;

    PS2_INT_OFF();

    /* terminate a transmission if we have */
    inhibit();
    wait_us(100); // 100us [4]p.13, [5]p.50

    /* 'Request to Send' and Start bit */
    data_lo();
    clock_hi();
    WAIT(clock_lo, 10000, 10);  // 10ms [5]p.50

    /* Data bit[2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << i)) {
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
    if (parity) {
        data_hi();
    } else {
        data_lo();
    }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);

    /* Stop bit */
    wait_us(15);
    data_hi();

    /* Ack */
    WAIT(data_lo, 50, 6);
    WAIT(clock_lo, 50, 7);

    /* wait for idle state */
    WAIT(clock_hi, 50, 8);
    WAIT(data_hi, 50, 9);

    idle();
    PS2_INT_ON();
    return ps2_host_recv_response();
ERROR:
    idle();
    PS2_INT_ON();
    return 0;
}

uint8_t ps2_host_recv_response(void) {
    // Command may take 25ms/20ms at most([5]p.46, [3]p.21)
    uint8_t retry = 25;
    while (retry-- && !pbuf_has_data()) {
        wait_ms(1);
    }
    return pbuf_dequeue();
}

/* get data received by interrupt */
uint8_t ps2_host_recv(void) {
    if (pbuf_has_data()) {
        ps2_error = PS2_ERR_NONE;
        return pbuf_dequeue();
    } else {
        ps2_error = PS2_ERR_NODATA;
        return 0;
    }
}

void ps2_interrupt_service_routine(void)
{
    static enum {
        INIT,
        START,
        BIT0,
        BIT1,
        BIT2,
        BIT3,
        BIT4,
        BIT5,
        BIT6,
        BIT7,
        PARITY,
        STOP,
    } state               = INIT;
    static uint8_t data   = 0;
    static uint8_t parity = 1;

    // TODO: abort if elapse 100us from previous interrupt

    // return unless falling edge
    if (clock_in()) {
        goto RETURN;
    }

    state++;
    switch (state) {
        case START:
            if (data_in()) goto ERROR;
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
                if (!(parity & 0x01)) goto ERROR;
            } else {
                if (parity & 0x01) goto ERROR;
            }
            break;
        case STOP:
            if (!data_in()) goto ERROR;
            pbuf_enqueue(data);
            goto DONE;
            break;
        default:
            goto ERROR;
    }
    goto RETURN;
ERROR:
    ps2_error = state;
DONE:
    state  = INIT;
    data   = 0;
    parity = 1;
RETURN:
    return;
}


#if defined(__AVR__)
ISR(PS2_INT_VECT)
{
    ps2_interrupt_service_routine();
}
#endif



/* send LED state to keyboard */
void ps2_host_set_led(uint8_t led) {
    ps2_host_send(0xED);
    ps2_host_send(led);
}

/*--------------------------------------------------------------------
 * Ring buffer to store scan codes from keyboard
 *------------------------------------------------------------------*/
#define PBUF_SIZE 32
static uint8_t     pbuf[PBUF_SIZE];
static uint8_t     pbuf_head = 0;
static uint8_t     pbuf_tail = 0;
static inline void pbuf_enqueue(uint8_t data) {
#if defined(__AVR__)
    uint8_t sreg = SREG;
    cli();
#endif

    uint8_t next = (pbuf_head + 1) % PBUF_SIZE;
    if (next != pbuf_tail) {
        pbuf[pbuf_head] = data;
        pbuf_head       = next;
    } else {
        print("pbuf: full\n");
    }

#if defined(__AVR__)
    SREG = sreg;
#endif
}
static inline uint8_t pbuf_dequeue(void) {
    uint8_t val = 0;

#if defined(__AVR__)
    uint8_t sreg = SREG;
    cli();
#endif

    if (pbuf_head != pbuf_tail) {
        val       = pbuf[pbuf_tail];
        pbuf_tail = (pbuf_tail + 1) % PBUF_SIZE;
    }

#if defined(__AVR__)
    SREG = sreg;
#endif

    return val;
}
static inline bool pbuf_has_data(void) {
#if defined(__AVR__)
    uint8_t sreg = SREG;
    cli();
#endif

    bool has_data = (pbuf_head != pbuf_tail);
#if defined(__AVR__)
    SREG          = sreg;
#endif
    return has_data;
}
static inline void pbuf_clear(void) {
#if defined(__AVR__)
    uint8_t sreg = SREG;
    cli();
#endif

    pbuf_head = pbuf_tail = 0;
#if defined(__AVR__)
    SREG                  = sreg;
#endif
}
