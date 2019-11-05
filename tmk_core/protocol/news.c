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
#include "news.h"

void news_init(void) { NEWS_KBD_RX_INIT(); }

// RX ring buffer
#define RBUF_SIZE 8
static uint8_t rbuf[RBUF_SIZE];
static uint8_t rbuf_head = 0;
static uint8_t rbuf_tail = 0;

uint8_t news_recv(void) {
    uint8_t data = 0;
    if (rbuf_head == rbuf_tail) {
        return 0;
    }

    data      = rbuf[rbuf_tail];
    rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    return data;
}

// USART RX complete interrupt
ISR(NEWS_KBD_RX_VECT) {
    uint8_t next = (rbuf_head + 1) % RBUF_SIZE;
    if (next != rbuf_tail) {
        rbuf[rbuf_head] = NEWS_KBD_RX_DATA;
        rbuf_head       = next;
    }
}

/*
SONY NEWS Keyboard Protocol
===========================

Resources
---------
    Mouse protocol of NWA-5461(Japanese)
    http://groups.google.com/group/fj.sys.news/browse_thread/thread/a01b3e3ac6ae5b2d

    SONY NEWS Info(Japanese)
    http://katsu.watanabe.name/doc/sonynews/


Pinouts
-------
    EIA 232 male connector from NWP-5461
    -------------
    \ 1 2 3 4 5 /
     \ 6 7 8 9 /
      ---------
    1 VCC
    2 BZ(Speaker)
    3 Keyboard Data(from keyboard MCU TxD)
    4 NC
    5 GND
    6 Unknown Input(to keyboard MCU RxD via schmitt trigger)
    7 Mouse Data(from Mouse Ext connector)
    8 Unknown Input(to Keyboard MCU Input via diode and buffer)
    9 FG
    NOTE: Two LED on keyboard are controlled by pin 6,8?

    EIA 232 male connector from NWP-411A
    -------------
    \ 1 2 3 4 5 /
     \ 6 7 8 9 /
      ---------
    1 VCC
    2 BZ(Speaker)
    3 Keyboard Data(from keyboard MCU TxD)
    4 NC
    5 GND
    6 NC
    7 Mouse Data(from Mouse Ext connector)
    8 NC
    9 FG
    NOTE: These are just from my guess and not confirmed.


Signaling
---------
    ~~~~~~~~~~ ____XOO0X111X222X333X444X555X666X777~~~~ ~~~~~~~
    Idle    Start  LSB                         MSB Stop Idle

    Idle:       High
    Start bit:  Low
    Stop bit:   High
    Bit order:  LSB first

    Baud rate:  9600
    Interface:  TTL level(5V) UART

    NOTE: This is observed on NWP-5461 with its DIP switch all OFF.


Format
------
    MSB         LSB
    7 6 5 4 3 2 1 0   bit
    | | | | | | | |
    | +-+-+-+-+-+-+-- scan code(00-7F)
    +---------------- break flag: sets when released


Scan Codes
----------
    SONY NEWS NWP-5461
    ,---.   ,------------------------, ,------------------------. ,---------.
    | 7A|   | 01 | 02 | 03 | 04 | 05 | | 06 | 07 | 08 | 09 | 0A | | 68 | 69 | ,-----------.
    `---'   `------------------------' `------------------------' `---------' | 64| 65| 52|
    ,-------------------------------------------------------------. ,---. ,---------------|
    | 0B| 0C| 0D| 0E| 0F| 10| 11| 12| 13| 14| 15| 16| 17| 18|  19 | | 6A| | 4B| 4C| 4D| 4E|
    |-------------------------------------------------------------| |---| |---------------|
    |  1A | 1B| 1C| 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27|   | | 6B| | 4F| 50| 51| 56|
    |---------------------------------------------------------'   | |---| |---------------|
    |  28  | 29| 2A| 2B| 2C| 2D| 2E| 2F| 30| 31| 32| 33| 34|  35  | | 6C| | 53| 54| 55|   |
    |-------------------------------------------------------------| |---| |-----------| 5A|
    |  36    | 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41|   42   | | 6D| | 57| 59| 58|   |
    |-------------------------------------------------------------| |---| |---------------|
    | 43  | 44 | 45 |       46          |    47    | 48| 49|  4A  | | 6E| | 66| 5B| 5C| 5D|
    `-------------------------------------------------------------' `---' `---------------'
*/
