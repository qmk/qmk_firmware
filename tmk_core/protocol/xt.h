/*
Copyright 2018 Jun WAKO <wakojun@gmail.com>
Copyright 2016 Ethan Apodaca <papodaca@gmail.com>

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

#pragma once

#define XT_DATA_IN()                        \
    do {                                    \
        XT_DATA_DDR &= ~(1 << XT_DATA_BIT); \
        XT_DATA_PORT |= (1 << XT_DATA_BIT); \
    } while (0)

#define XT_DATA_READ() (XT_DATA_PIN & (1 << XT_DATA_BIT))

#define XT_DATA_LO()                         \
    do {                                     \
        XT_DATA_PORT &= ~(1 << XT_DATA_BIT); \
        XT_DATA_DDR |= (1 << XT_DATA_BIT);   \
    } while (0)

#define XT_CLOCK_IN()                         \
    do {                                      \
        XT_CLOCK_DDR &= ~(1 << XT_CLOCK_BIT); \
        XT_CLOCK_PORT |= (1 << XT_CLOCK_BIT); \
    } while (0)

#define XT_CLOCK_READ() (XT_CLOCK_PIN & (1 << XT_CLOCK_BIT))

#define XT_CLOCK_LO()                          \
    do {                                       \
        XT_CLOCK_PORT &= ~(1 << XT_CLOCK_BIT); \
        XT_CLOCK_DDR |= (1 << XT_CLOCK_BIT);   \
    } while (0)

void    xt_host_init(void);
uint8_t xt_host_recv(void);
