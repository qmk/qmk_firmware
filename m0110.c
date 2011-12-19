/*
Copyright 2011 Jun WAKO <wakojun@gmail.com>

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
#include "m0110.h"
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
static inline void idle(void);
static inline void request(void);


/*
Primitive M0110 Library for AVR
==============================


Signaling
---------
CLOCK is always from KEYBOARD. DATA are sent with MSB first.

1) IDLE: both line is high.
    CLOCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    DATA  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2) KEYBOARD->HOST: HOST reads bit on rising edge.
    CLOCK ~~~~~~~~~~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~~~~~~~~~
    DATA  ~~~~~~~~~~~~X777777X666666X555555X444444X333333X222222X111111X000000X~~~~~~~
                      <--> 160us(clock low)
                         <---> 180us(clock high)

3) HOST->KEYBOARD: HOST asserts bit on falling edge.
    CLOCK ~~~~~~~~~~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~|__|~~~~~~~~~~~
    DATA  ~~~~~~|_____X777777X666666X555555X444444X333333X222222X111111X000000X~~~~~~~
                <----> 840us(request to send by host)                     <-> 80us(hold DATA)
                      <--> 180us(clock low)
                         <---> 220us(clock high)


Protocol
--------
COMMAND:
    Inquiry     0x10    get key event
    Instant     0x12    get key event
    Model       0x14    get model number(M0110 responds with 0x09)
                        bit 7   1 if another device connected(used when keypad exists?)
                        bit4-6  next device model number
                        bit1-3  keyboard model number
                        bit 0   always 1
    Test        0x16    test(ACK:0x7D/NAK:0x77)

KEY EVENT:
    bit 7       key state(0:press 1:release)
    bit 6-1     scan code
    bit 0       always 1
    To get scan code,  use ((bits&(1<<7)) | ((bits&7F))>>1).

SCAN CODE:
    M0110
    ,---------------------------------------------------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs|
    |---------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|
    |---------------------------------------------------------|
    |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return|
    |---------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|        |
    `---------------------------------------------------------'
         |Opt|Mac |         Space               |Enter|Opt|
         `------------------------------------------------'
    ,---------------------------------------------------------.
    | 32| 12| 13| 14| 15| 17| 16| 1A| 1C| 19| 1D| 1B| 18|   33|
    |---------------------------------------------------------|
    |   30| 0C| 0D| 0E| 0F| 10| 11| 20| 22| 1F| 23| 21| 1E| 2A|
    |---------------------------------------------------------|
    |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27|    24|
    |---------------------------------------------------------|
    |      38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C|      38|
    `---------------------------------------------------------'
         | 3A|  37|             31              |   34| 3A|
         `------------------------------------------------'


References
----------
Protocol:
    http://www.mac.linux-m68k.org/devel/plushw.php
Connector:
    http://www.kbdbabel.org/conn/kbd_connector_macplus.png
Signaling:
    http://www.kbdbabel.org/signaling/kbd_signaling_mac.png
    http://typematic.blog.shinobi.jp/Entry/14/
Scan Codes:
    http://m0115.web.fc2.com/m0110.jpg
    http://m0115.web.fc2.com/m0110a.jpg
*/


#define WAIT(stat, us, err) do { \
    if (!wait_##stat(us)) { \
        m0110_error = err; \
        goto ERROR; \
    } \
} while (0)


uint8_t m0110_error = 0;


void m0110_init(void)
{
    uint8_t data;
    idle();
    _delay_ms(255);

    m0110_send(M0110_MODLE);
    data = m0110_recv();
    print("m0110_init model: "); phex(data); print("\n");

    m0110_send(M0110_TEST);
    data = m0110_recv();
    print("m0110_init test: "); phex(data); print("\n");
}

uint8_t m0110_send(uint8_t data)
{
    m0110_error = 0;

    request();
    WAIT(clock_lo, 1000, 0);
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
        WAIT(clock_lo, 250, 3);
        _delay_us(15);
        if (data&bit) {
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_hi, 200, 4);
    }
    _delay_us(100); // hold last bit for 80us
    idle();
    return 1;
ERROR:
    if (m0110_error) {
        print("m0110_send err: "); phex(m0110_error); print("\n");
    }
    idle();
    return 0;
}

uint8_t m0110_recv(void)
{
    uint8_t data = 0;
    m0110_error = 0;

    WAIT(clock_lo, -1, 0); // need 250ms? insted 0xffff(16bit max)us
    for (uint8_t i = 0; i < 8; i++) {
        data <<= 1;
        WAIT(clock_lo, 200, 2);
        WAIT(clock_hi, 200, 3);
        if (data_in()) {
            data |= 1;
        }
    }
    idle();
    if (data != M0110_NULL) {
        print("m0110_recv data: "); phex(data); print("\n");
    }
    return data;
ERROR:
    if (m0110_error) {
        print("m0110_recv err: "); phex(m0110_error); print("\n");
    }
    idle();
    return 0xFF;
}

uint8_t m0110_recv_key(void)
{
    uint8_t key;
    m0110_send(M0110_INQUIRY);
    key = m0110_recv();
    if (key == 0xFF || key == M0110_NULL)
        return M0110_NULL;
    else 
        return ((key&(1<<7)) | ((key&0x7F)>>1));
}


static inline void clock_lo()
{
    M0110_CLOCK_PORT &= ~(1<<M0110_CLOCK_BIT);
    M0110_CLOCK_DDR  |=  (1<<M0110_CLOCK_BIT);
}
static inline void clock_hi()
{
    /* input with pull up */
    M0110_CLOCK_DDR  &= ~(1<<M0110_CLOCK_BIT);
    M0110_CLOCK_PORT |=  (1<<M0110_CLOCK_BIT);
}
static inline bool clock_in()
{
    M0110_CLOCK_DDR  &= ~(1<<M0110_CLOCK_BIT);
    M0110_CLOCK_PORT |=  (1<<M0110_CLOCK_BIT);
    _delay_us(1);
    return M0110_CLOCK_PIN&(1<<M0110_CLOCK_BIT);
}
static inline void data_lo()
{
    M0110_DATA_PORT &= ~(1<<M0110_DATA_BIT);
    M0110_DATA_DDR  |=  (1<<M0110_DATA_BIT);
}
static inline void data_hi()
{
    /* input with pull up */
    M0110_DATA_DDR  &= ~(1<<M0110_DATA_BIT);
    M0110_DATA_PORT |=  (1<<M0110_DATA_BIT);
}
static inline bool data_in()
{
    M0110_DATA_DDR  &= ~(1<<M0110_DATA_BIT);
    M0110_DATA_PORT |=  (1<<M0110_DATA_BIT);
    _delay_us(1);
    return M0110_DATA_PIN&(1<<M0110_DATA_BIT);
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

static inline void idle(void)
{
    clock_hi();
    data_hi();
}

static inline void request(void)
{
    clock_hi();
    data_lo();
}
