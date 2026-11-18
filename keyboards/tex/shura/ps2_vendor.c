// Copyright 2010-2013 Jun WAKO <wakojun@gmail.com> (drivers/ps2/ps2_busywait.c, Modified BSD License)
// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// QMK's busywait PS/2 host for the Shura's stream-mode TrackPoint.

/*
 * The following terms apply to the portions derived from Jun Wako's PS/2 driver:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdbool.h>
#include QMK_KEYBOARD_H
#include "ps2.h"
#include "ps2_io.h"
#include "wait.h"

#define WAIT(stat, us, err)     \
    do {                        \
        if (!wait_##stat(us)) { \
            ps2_error = err;    \
            goto ERROR;         \
        }                       \
    } while (0)

uint8_t ps2_error = PS2_ERR_NONE;

void ps2_host_init(void) {
    clock_init();
    data_init();
    // Power-on reset plus BAT may take 2.5 s.
    wait_ms(2500);
    inhibit();
}

// After tp_power_on(); its own timer replaces ps2_host_init()'s blocking wait.
void ps2_host_resume(void) {
    clock_init();
    data_init();
    inhibit();
}

uint8_t ps2_host_send(uint8_t data) {
    bool parity = true;
    ps2_error   = PS2_ERR_NONE;

    inhibit();
    wait_us(100);
    // Request to send and start bit
    data_lo();
    clock_hi();
    WAIT(clock_lo, 10000, 10);
    for (uint8_t i = 0; i < 8; i++) {
        wait_us(15);
        if (data & (1 << i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_hi, 50, 2);
        WAIT(clock_lo, 50, 3);
    }
    wait_us(15);
    if (parity) {
        data_hi();
    } else {
        data_lo();
    }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);
    // Stop bit, acknowledge, idle
    wait_us(15);
    data_hi();
    WAIT(data_lo, 50, 6);
    WAIT(clock_lo, 50, 7);
    WAIT(clock_hi, 50, 8);
    WAIT(data_hi, 50, 9);
    inhibit();
    return ps2_host_recv_response();
ERROR:
    inhibit();
    return 0;
}

uint8_t ps2_host_recv(void) {
    uint8_t data   = 0;
    bool    parity = true;
    ps2_error      = PS2_ERR_NONE;

    idle();
    // Start bit
    WAIT(clock_lo, 100, 1);
    WAIT(data_lo, 1, 2);
    WAIT(clock_hi, 50, 3);
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_lo, 50, 4);
        if (data_in()) {
            parity = !parity;
            data |= (1 << i);
        }
        WAIT(clock_hi, 50, 5);
    }
    WAIT(clock_lo, 50, 6);
    if (data_in() != parity) {
        ps2_error = PS2_ERR_PARITY;
        goto ERROR;
    }
    WAIT(clock_hi, 50, 7);
    // Stop bit
    WAIT(clock_lo, 50, 8);
    WAIT(data_hi, 1, 9);
    WAIT(clock_hi, 50, 10);
    inhibit();
    return data;
ERROR:
    inhibit();
    return 0;
}

uint8_t ps2_host_recv_response(void) {
    uint8_t data = 0;
    uint8_t try  = 250;

    // A command may take 25 ms to answer: 250 tries of 100 us each.
    do {
        data = ps2_host_recv();
    } while (try-- && ps2_error);
    return data;
}

void ps2_host_set_led(uint8_t led) {
    ps2_host_send(0xED);
    ps2_host_send(led);
}
