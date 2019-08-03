#pragma once

#include "ch.h"
#include <hal.h>
#include "i2c_defs.h"

#define I2C_SLAVE_REG_COUNT 30

extern volatile uint8_t i2c_slave_reg[I2C_SLAVE_REG_COUNT];

void i2c_slave_init(uint8_t address);
void i2c_slave_stop(void);
