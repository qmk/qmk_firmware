// Copyright 2022 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Port ID
 */
typedef enum {
    mcp23018_PORTA,
    mcp23018_PORTB,
} mcp23018_port_t;

/**
 * Helpers for set_config
 */
enum {
    ALL_OUTPUT = 0,
    ALL_INPUT  = 0xFF,
};

/**
 * Helpers for set_output
 */
enum {
    ALL_LOW  = 0,
    ALL_HIGH = 0xFF,
};

/**
 * Init expander and any other dependent drivers
 */
void mcp23018_init(uint8_t slave_addr);

/**
 * Configure input/output to a given port
 */
bool mcp23018_set_config(uint8_t slave_addr, mcp23018_port_t port, uint8_t conf);

/**
 * Write high/low to a given port
 */
bool mcp23018_set_output(uint8_t slave_addr, mcp23018_port_t port, uint8_t conf);

/**
 * Write high/low to both ports sequentially
 *
 *  - slightly faster than multiple set_output
 */
bool mcp23018_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB);

/**
 * Read state of a given port
 */
bool mcp23018_read_pins(uint8_t slave_addr, mcp23018_port_t port, uint8_t* ret);

/**
 * Read state of both ports sequentially
 *
 *  - slightly faster than multiple readPins
 */
bool mcp23018_read_pins_all(uint8_t slave_addr, uint16_t* ret);

// DEPRECATED - DO NOT USE

#define mcp23018_readPins mcp23018_read_pins
#define mcp23018_readPins_all mcp23018_read_pins_all
