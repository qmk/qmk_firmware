// Copyright 2023 @frobiac
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include "wait.h"

extern uint8_t expander_status;
extern uint8_t expander_input_pin_mask;
extern bool    i2c_initialized;

void init_blackbowl(void);
void init_expander(void);

// clang-format off
#define I2C_TIMEOUT     100
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

#define xxx KC_NO

// clang-format on
