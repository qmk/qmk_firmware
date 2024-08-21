/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quantum.h"
#include "multiplexer.h"

const pin_t mux_pins[MUXES]                      = MUX_PINS;
const pin_t mux_selector_pins[MUX_SELECTOR_BITS] = MUX_SELECTOR_PINS;

void multiplexer_init(void) {
    for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
        pin_t pin = mux_selector_pins[i];
        setPinOutput(pin);
    }
}

bool select_mux(uint8_t channel) {
    if (channel > MUX_CHANNELS) return 0;
    for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
        writePin(mux_selector_pins[i], channel & (1 << i));
    }
    current_channel = channel;
    return 1;
}

const mux_t NC                             = {255, 255}; // A coord with a Null pin (from JSON)
const mux_t mux_index[MUXES][MUX_CHANNELS] =
{
    {{2, 0}, {3, 0}, {1, 0}, {4, 0}, {2, 2}, {4, 1}, {3, 1}, {4, 2}, {0, 3}, {0, 2}, {1, 2}, {2, 1}, {1, 3}, {1, 1}, {0, 0}, {0, 1}},
    {NC, NC, {3, 2}, {2, 3}, {3, 4}, {2, 4}, {3, 3}, {3, 5}, {1, 6}, {0, 5}, {2, 6}, {1, 5}, {0, 6}, {2, 6}, {1, 4}, {0, 4}},
    {NC, {3, 7}, {3, 6}, {2, 7}, {4, 3}, {3, 9}, {4, 4}, {3, 8}, {2, 9}, {0, 9}, {1, 9}, {0, 8}, {1, 7}, {2, 8}, {0, 7}, {1, 8}},
    {{4, 5}, {3, 10}, {4, 6}, {0, 10}, {4, 7}, {1, 13}, {3, 11}, {2, 12}, {0, 13}, {0, 12}, {1, 12}, {0, 11}, {2, 10}, {2, 11}, {1, 10}, {1, 11}}
};
