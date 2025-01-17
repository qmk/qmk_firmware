// Created/amended by OleVoip 2025.
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <avr/builtins.h>

// clion doesn't like __flash
#define FCONST const __attribute__((__progmem__))

#define DDR(p)  CONCAT_MACRONAME(DDR,p)
#define PINP(p) CONCAT_MACRONAME(PIN,p)
#define PORT(p) CONCAT_MACRONAME(PORT,p)

static inline void wait_for_bus(void) {
    __builtin_avr_delay_cycles(BUS_WAIT_CYCLES);
}

static inline uint8_t read_bus(void) {
    return PINP(BUS_PORT);
}

static inline void write_bus(uint8_t value) {
    PORT(BUS_PORT) = value;
}

static inline void set_bus_idle(void) {
    DDR(BUS_PORT) = 0;
    wait_for_bus();
    PORT(BUS_PORT) = 0xFF;
}

static inline void set_bus_input(void) {
    DDR(BUS_PORT) = 0;
    PORT(BUS_PORT) = 0;
}

static inline void set_bus_output(void) {
    DDR(BUS_PORT) = 0;
}

static inline uint8_t timer_read8(void) {
    return (uint8_t) timer_count;
}
// .