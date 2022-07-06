// Copyright 2022 nirim000
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Port ID
 */
typedef enum {
    PCA9505_PORT0,
    PCA9505_PORT1,
    PCA9505_PORT2,
    PCA9505_PORT3,
    PCA9505_PORT4,
} pca9505_port_t;

/**
 * Helpers for set_config
 */
enum {
    ALL_NORMAL   = 0,
    ALL_INVERTED = 0xFF,
};

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
void pca9505_init(uint8_t slave_addr);

/**
 * Configure input/output to a given port
 */
bool pca9505_set_config(uint8_t slave_addr, pca9505_port_t port, uint8_t conf);

/**
 * Configure polarity to a given port
 */
bool pca9505_set_polarity(uint8_t slave_addr, pca9505_port_t port, uint8_t conf);

/**
 * Write high/low to a given port
 */
bool pca9505_set_output(uint8_t slave_addr, pca9505_port_t port, uint8_t conf);

/**
 * Read state of a given port
 */
bool pca9505_readPins(uint8_t slave_addr, pca9505_port_t port, uint8_t* ret);
