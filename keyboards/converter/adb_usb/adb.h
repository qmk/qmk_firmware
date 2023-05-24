/*
Copyright 2011-19 Jun WAKO <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>

#if !(defined(ADB_PORT) && defined(ADB_PIN) && defined(ADB_DDR) && defined(ADB_DATA_BIT))
#    error "ADB port setting is required in config.h"
#endif

#define ADB_POWER 0x7F
#define ADB_CAPS 0x39

/* ADB commands */
// Default Address
#define ADB_ADDR_0 0
#define ADB_ADDR_DONGLE 1
#define ADB_ADDR_KEYBOARD 2
#define ADB_ADDR_MOUSE 3
#define ADB_ADDR_TABLET 4
#define ADB_ADDR_APPLIANCE 7
#define ADB_ADDR_8 8
#define ADB_ADDR_9 9
#define ADB_ADDR_10 10
#define ADB_ADDR_11 11
#define ADB_ADDR_12 12
#define ADB_ADDR_13 13
#define ADB_ADDR_14 14
#define ADB_ADDR_15 15
// for temporary purpose, do not use for polling
#define ADB_ADDR_TMP 15
#define ADB_ADDR_MOUSE_POLL 10
// Command Type
#define ADB_CMD_RESET 0
#define ADB_CMD_FLUSH 1
#define ADB_CMD_LISTEN 8
#define ADB_CMD_TALK 12
// Register
#define ADB_REG_0 0
#define ADB_REG_1 1
#define ADB_REG_2 2
#define ADB_REG_3 3

/* ADB keyboard handler id */
#define ADB_HANDLER_STD 0x01        /* IIGS, M0116 */
#define ADB_HANDLER_AEK 0x02        /* M0115, M3501 */
#define ADB_HANDLER_AEK_RMOD 0x03   /* M0115, M3501, alternate mode enableing right modifiers */
#define ADB_HANDLER_STD_ISO 0x04    /* M0118, ISO swapping keys */
#define ADB_HANDLER_AEK_ISO 0x05    /* M0115, M3501, ISO swapping keys */
#define ADB_HANDLER_M1242_ANSI 0x10 /* Adjustable keyboard */
#define ADB_HANDLER_CLASSIC1_MOUSE 0x01
#define ADB_HANDLER_CLASSIC2_MOUSE 0x02
#define ADB_HANDLER_EXTENDED_MOUSE 0x04
#define ADB_HANDLER_TURBO_MOUSE 0x32

// ADB host
void     adb_host_init(void);
bool     adb_host_psw(void);
uint16_t adb_host_talk(uint8_t addr, uint8_t reg);
uint8_t  adb_host_talk_buf(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);
void     adb_host_listen(uint8_t addr, uint8_t reg, uint8_t data_h, uint8_t data_l);
void     adb_host_listen_buf(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);
void     adb_host_flush(uint8_t addr);
void     adb_host_kbd_led(uint8_t led);
uint16_t adb_host_kbd_recv(void);
uint16_t adb_host_mouse_recv(void);

// ADB Mouse
void adb_mouse_task(void);
void adb_mouse_init(void);
