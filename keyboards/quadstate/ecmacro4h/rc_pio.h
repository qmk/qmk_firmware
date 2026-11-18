// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"

// Measures one key electrode at a time with a PIO0 state machine. The GPIO
// charges the electrode, then lets it discharge through its resistor to
// ground, and the time until the GPIO reads low is counted in ticks of
// 16 ns. Pressing a key adds capacitance, so the count rises.
//
// Measurements run one after another: rc_pio_start(), then rc_pio_poll()
// until it returns true, then rc_pio_start() for the next key.

// The highest count; a GPIO still high after this many ticks is a failure.
#define RC_MAX_TICKS 16383

void rc_pio_init(void);
void rc_pio_start(pin_t gpio);

// False while the measurement runs. True once it has ended, with *ticks
// set to the count (1 to RC_MAX_TICKS), or to 0 if the measurement failed.
bool rc_pio_poll(uint16_t *ticks);
