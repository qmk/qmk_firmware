// Jane Bernhardt (https://github.com/germ)
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>


extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT 1000

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        (0x20<<1)
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

uint8_t init_mcp23018(void);
