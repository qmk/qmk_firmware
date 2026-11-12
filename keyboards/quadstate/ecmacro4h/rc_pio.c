// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rc_pio.h"
#include "hardware/pio.h"
#include "timer.h"
#include "util.h"

// The state machine runs at clk_sys, 125 MHz. A tick of the count is two
// single-cycle instructions, 16 ns, so the longest count takes 262 us and a
// whole measurement, with its 8 us charge, under 272 us. A measurement with
// no result after RC_DEADLINE_MS has failed; 2 ms guarantees at least 1 ms
// of real time, as the timer counts whole milliseconds.
#define RC_DEADLINE_MS 2

// The PIO program, assembled with pioasm:
//
//     pull block          ; load the start count (RC_MAX_TICKS) into osr
//     mov x, osr          ; copy it to x
//     set pins, 1         ; set the output level high first
//     set pindirs, 1      ; then drive the GPIO: the charge starts
//     set y, 31
// charge:
//     jmp y-- charge [31] ; keep driving for 32 x 32 cycles (8 us)
//     set pindirs, 0      ; release it, and count down while it reads high
// measure:
//     jmp pin high
//     jmp done            ; it reads low
// high:
//     jmp x-- measure     ; two instructions per tick
// done:
//     mov isr, x          ; copy what is left (~0 if the count ran out)
//     push noblock        ; send it to the CPU (RX FIFO)
// stopped:
//     jmp stopped         ; one result per start
static const uint16_t rc_program_instructions[] = {
    0x80a0, //  0: pull   block
    0xa027, //  1: mov    x, osr
    0xe001, //  2: set    pins, 1
    0xe081, //  3: set    pindirs, 1
    0xe05f, //  4: set    y, 31
    0x1f85, //  5: jmp    y--, 5                 [31]
    0xe080, //  6: set    pindirs, 0
    0x00c9, //  7: jmp    pin, 9
    0x000a, //  8: jmp    10
    0x0047, //  9: jmp    x--, 7
    0xa0c1, // 10: mov    isr, x
    0x8000, // 11: push   noblock
    0x000c, // 12: jmp    12
};

static const pio_program_t rc_program = {
    .instructions = rc_program_instructions,
    .length       = ARRAY_SIZE(rc_program_instructions),
    .origin       = -1,
};

static uint          state_machine;
static uint          program_offset;
static pio_sm_config program_config;
static pin_t         pin;
static uint32_t      started;

void rc_pio_init(void) {
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO0);
    state_machine  = pio_claim_unused_sm(pio0, true);
    program_offset = pio_add_program(pio0, &rc_program);

    program_config = pio_get_default_sm_config();
    sm_config_set_wrap(&program_config, program_offset, program_offset + rc_program.length - 1);
}

void rc_pio_start(pin_t gpio) {
    pio_sm_config config = program_config;

    pin = gpio;
    sm_config_set_set_pins(&config, pin, 1);
    sm_config_set_jmp_pin(&config, pin);
    pio_sm_init(pio0, state_machine, program_offset, &config);
    pio_sm_set_consecutive_pindirs(pio0, state_machine, pin, 1, false);
    // Hand the GPIO to PIO0: a Schmitt-trigger input with no pulls, and an
    // output with 2 mA drive and a slow slew rate for the charge.
    palSetLineMode(pin, PAL_MODE_ALTERNATE_PIO0 | PAL_RP_PAD_DRIVE2);
    pio_sm_put(pio0, state_machine, RC_MAX_TICKS);
    started = timer_read32();
    pio_sm_set_enabled(pio0, state_machine, true);
}

// Stops the state machine and hands the GPIO back to the CPU as an input.
static void stop(void) {
    pio_sm_set_enabled(pio0, state_machine, false);
    gpio_set_pin_input(pin);
}

bool rc_pio_poll(uint16_t *ticks) {
    // Read the time first: a FIFO still empty after the deadline has passed
    // means the measurement failed.
    const bool expired = timer_elapsed32(started) >= RC_DEADLINE_MS;

    if (!pio_sm_is_rx_fifo_empty(pio0, state_machine)) {
        // The state machine pushes what is left of the count. RC_MAX_TICKS
        // left means the GPIO read low immediately (it could not be
        // charged); ~0 means it never read low. Both are failures,
        // reported as 0 ticks.
        const uint32_t left = pio_sm_get(pio0, state_machine);
        *ticks              = left < RC_MAX_TICKS ? RC_MAX_TICKS - left : 0;
    } else if (expired) {
        *ticks = 0;
    } else {
        return false;
    }
    stop();
    return true;
}
