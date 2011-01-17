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
#ifndef PS2_H
#define PS2_H
/*
 * Primitive PS/2 Library for AVR
 */


/* port settings for clock and data line */
#if !(defined(PS2_CLOCK_PORT) && \
      defined(PS2_CLOCK_PIN) && \
      defined(PS2_CLOCK_DDR) && \
      defined(PS2_CLOCK_BIT))
#   error "PS/2 clock port setting is required in config.h"
#endif

#if !(defined(PS2_DATA_PORT) && \
      defined(PS2_DATA_PIN) && \
      defined(PS2_DATA_DDR) && \
      defined(PS2_DATA_BIT))
#   error "PS/2 data port setting is required in config.h"
#endif

#define PS2_ERR_NONE    0
#define PS2_ERR_PARITY  0x10

#define PS2_LED_SCROLL_LOCK 0
#define PS2_LED_NUM_LOCK    1
#define PS2_LED_CAPS_LOCK   2


extern uint8_t ps2_error;

/* host side */
void ps2_host_init(void);
uint8_t ps2_host_send(uint8_t);
uint8_t ps2_host_recv(void);

/* TODO: device side */

#endif
