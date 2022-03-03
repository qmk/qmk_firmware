// Copyright 2020 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
            PCA9555
         ,----------.
   SDA --| SDA  P00 |-- P00
   SCL --| SCL  P01 |-- P01
   INT --| INT  P02 |-- P02
         |      P03 |-- P03
   A0  --| A0   P04 |-- P04
   A1  --| A1   P05 |-- P05
   A2  --| A2   P06 |-- P06
         |      P07 |-- P07
         |          |
         |      P10 |-- P10
         |      P11 |-- P11
         |      P12 |-- P12
         |      P13 |-- P13
         |      P14 |-- P14
         |      P15 |-- P15
         |      P16 |-- P16
         |      P17 |-- P17
         `----------'
*/

/**
 * Port ID
 */
typedef enum {
    PCA9555_PORT0,
    PCA9555_PORT1,
} pca9555_port_t;

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
void pca9555_init(uint8_t slave_addr);

/**
 * Configure input/output to a given port
 */
bool pca9555_set_config(uint8_t slave_addr, pca9555_port_t port, uint8_t conf);

/**
 * Write high/low to a given port
 */
bool pca9555_set_output(uint8_t slave_addr, pca9555_port_t port, uint8_t conf);

/**
 * Write high/low to both ports sequentially
 *
 *  - slightly faster than multiple set_output
 */
bool pca9555_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB);

/**
 * Read state of a given port
 */
bool pca9555_readPins(uint8_t slave_addr, pca9555_port_t port, uint8_t* ret);

/**
 * Read state of both ports sequentially
 *
 *  - slightly faster than multiple readPins
 */
bool pca9555_readPins_all(uint8_t slave_addr, uint16_t* ret);
